/*
Author:ZhouLiyan*
Date:2016.08.01
Loc:Haerbin Institute Of Technology
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <token_analyze.h>
#include <operator.h>
#include <data_struct.h>
#include <FourElemFormula.h>
#include <table.h>
#include <queue.h>
#include <symboltable.h>
#include <stack.h>
#include <linkedlist.h>
#include <debug.h>

symtbl *initst;

FILE *fp;   //获取文件的指针

int newflag = 0;        //标志是否新读入一个token
int tempcount = 0;

stack s1;
symstack s2;
stack off;
sstack tbl;
queue idli;
queue actualpali;
intqueue indexli;

pstack state = &s1;
psymstack symbol = &s2;
pstack offset = &off;
psstack tblptr = &tbl;
pqueue idlist = &idli;
pqueue actualpalist = &actualpali;
pintqueue indexlist = &indexli;
Identifier *templink;           //存放临时变量的链表

pFour fmlay[300]={NULL};           //typedef FourElemFormula* pFour
int fmlap = 1;

Token ReadToken();    /*make(返回结构体)从文件中读取一行，返回Token*/
void Reduction_Goto(int k);     /*按第k个产生式规约*/
Identifier* lookup(char *name,symtbl* nowsym);       /*返回name节点在符号表中的指针，如不存在返回null*/

void gencode(int op,char *arg1,char *arg2,char* ret);
void backpatch(LabelNode* lis,int labelnum);

int main()
{
    Token token = (Token)malloc(sizeof(To));
    int index;
    int statenum;

    MakeNull(state);
    MakeNullsym(symbol);
    MakeNull(offset);
    MakeNulls(tblptr);
    MakeNULLQueue(idlist);
    MakeNULLQueue(actualpalist);
    IntMakeNULLQueue(indexlist);
    initList(&templink);

    if(token_analyze() == 1)        //词法分析失败
    {
        return 0;
    }


    fp = fopen("lex.txt","r");

    token->symbolnum = 0;
    push(state,0);
    pushsym(symbol,token);
    //printf("stack\t\t\t\tproduction");

    while(1)
    {
        //printf("\n");
        //PrintStack(state);
        //printf("%c",'&');
        //PrintSymStack(symbol);

        if(newflag == 0)
        {
            token = ReadToken();
        }
        statenum = state->elem[state->top];

        if(yypact[statenum] == YYPACT_NINF)     /*按默认产生式规约*/
        {
            if(yydefact[statenum] == 0)
            {
                printf("grammar error!\n");
                break;
            }
            else if(yydefact[statenum] == 1)
            {
                printf("accept!\n");
                PrintSymTable(initst);
                PrintFmla(fmlay,fmlap);
                break;
            }
            else
            {
                Reduction_Goto(yydefact[statenum]);
                newflag = 1;
            }
        }
        else
        {
            index = yypact[statenum] + token->symbolnum;
            if((index >= LCHECK) || (yycheck[index] != token->symbolnum)) /*按默认产生式规约*/
            {
                if(yydefact[statenum] == 0)
                {
                    printf("grammar error!\n");
                    break;
                }
                else if(yydefact[statenum] == 1)
                {
                    printf("accept!\n");
                    PrintSymTable(initst);
                    PrintFmla(fmlay,fmlap);
                    break;
                }
                else
                {
                    Reduction_Goto(yydefact[statenum]);
                    newflag = 1;
                }
            }
            else
            {
                if(yytable[index] == YYTABLE_NINF)
                {
                    printf("grammar error\n");
                    break;
                }
                else if(yytable[index] == 0)
                {
                    if(yydefact[statenum] == 0)
                    {
                        printf("grammar error!\n");
                        break;
                    }
                    else if(yydefact[statenum] == 1)
                    {
                        printf("accept!\n");
                        PrintSymTable(initst);
                        PrintFmla(fmlay,fmlap);
                        break;
                    }
                    else
                    {
                        Reduction_Goto(yydefact[statenum]);
                        newflag = 1;
                    }
                }
                else if(yytable[index] < 0)
                {
                    Reduction_Goto(-yytable[index]);    /*按产生式规约，变负*/
                    newflag = 1;
                }
                else
                {
                    push(state,yytable[index]);
                    pushsym(symbol,token);
                    newflag = 0;
                }
            }
        }
    }


    clearFmlay(fmlay,fmlap);
    clearList(templink);
    fclose(fp);
    return 0;
}


void Reduction_Goto(int k)      /*按第k个产生式规约，k为正数，output文件编号加1才是k*/
{
    int len = yyr2[k];
    int array[len];         /*array放产生式的右部各个元素*/
    int i,index;
    int symbolnum,statenum;
    Token t = (Token)malloc(sizeof(To));    //申请的空间不会被释放
    t->addr = NULL;
    t->offset = NULL;
    t->truelist = NULL;
    t->falselist = NULL;
    t->nextlist = NULL;

    symtbl *st;     /*翻译用的变量*/
    char id100[64];    //case 100
    char type47[64];

    int m;
    Identifier *temp = NULL;

    switch(k)
    {
    case 3:         //program: program_heading semicolon muldec_m1 block DOT
        {
            addwidth(tblptr->elem[tblptr->top],offset->elem[offset->top]);
            pops(tblptr);
            pop(offset);
            break;
        }
    case 4:         //muldec_m1: /* empty */
        {
            st = mktable(NULL);
            initst = st;
            pushs(tblptr,st);
            push(offset,0);
            break;
        }
    case 6:     //identifier_list: identifier_list comma identifier
        {
            Enqueue(idlist,symbol->elem[symbol->top]->name);
            break;
        }
    case 7:     //identifier_list:identifier
        {
            Enqueue(idlist,symbol->elem[symbol->top]->name);
            break;
        }
    case 9:    //constant: non_string
        {
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 10:    //constant: sign non_string
        {
            if(symbol->elem[symbol->top+1]->type == 0)
            {
                t->i = symbol->elem[symbol->top]->i;
            }
            else    //==1
            {
                t->i = -symbol->elem[symbol->top]->i;
            }
            break;
        }
    case 11:    //sign: PLUS
        {
            t->type = 0;
            break;
        }
    case 12:    //sign:MINUS
        {
            t->type = 1;
            break;
        }
    case 13:   // non_string: DIGSEQ
        {
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 14:        //type_denoter: identifier
        {
            strcpy(type47,symbol->elem[symbol->top]->name);
            if(strcmp(type47,"integer") == 0)
            {
                t->type = 0;
                t->i = 4;
            }
            else if(strcmp(type47,"real") == 0)
            {
                t->type = 1;
                t->i = 8;
            }
            break;
        }
    case 15:    //type_denoter:  new_type
        {
            t->type = symbol->elem[symbol->top]->type;
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 16:        //new_type:new_structured_type
        {
            t->type = symbol->elem[symbol->top]->type;
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 17:        //new_ordinal_type: subrange_type
        {
            t->i = symbol->elem[symbol->top]->i;
            t->type = symbol->elem[symbol->top]->type;
            break;
        }
    case 18:    //subrange_type: constant DOTDOT constant
        {
            t->i = symbol->elem[symbol->top]->i;
            t->type = symbol->elem[symbol->top+2]->i;
            break;
        }
    case 19:    //new_structured_type: structured_type
        {
            t->type = symbol->elem[symbol->top]->type;
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 20:    //structured_type: array_type
        {
            t->type = symbol->elem[symbol->top]->type;
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 21:        //array_type: ARRAY LBRAC index_list RBRAC OF component_type
        {
            t->type = symbol->elem[symbol->top]->type + 2;
            t->i = symbol->elem[symbol->top+3]->i * 4 * (symbol->elem[symbol->top]->type+1);
            break;
        }
    case 22:    //index_list: index_list comma index_type
        {
            t->i = symbol->elem[symbol->top+2]->i * (symbol->elem[symbol->top]->i - symbol->elem[symbol->top]->type+1);
            IntEnqueue(indexlist,symbol->elem[symbol->top]->type);
            IntEnqueue(indexlist,symbol->elem[symbol->top]->i);
            break;
        }
    case 23:    //index_list: index_type
        {
            t->i = symbol->elem[symbol->top]->i - symbol->elem[symbol->top]->type+1;
            IntEnqueue(indexlist,symbol->elem[symbol->top]->type);
            IntEnqueue(indexlist,symbol->elem[symbol->top]->i);
            break;
        }
    case 24:    //index_type: ordinal_type
        {
            t->i = symbol->elem[symbol->top]->i;
            t->type = symbol->elem[symbol->top]->type;
            break;
        }
    case 25:    //ordinal_type: new_ordinal_type
        {
            t->i = symbol->elem[symbol->top]->i;
            t->type = symbol->elem[symbol->top]->type;
            break;
        }
    case 26:    //component_type: type_denoter
        {
            t->type = symbol->elem[symbol->top]->type;
            break;
        }
    case 31:        //variable_declaration: identifier_list COLON type_denoter
        {
            while(Dequeue(idlist,id100) == 1)
            {
                enter(tblptr->elem[tblptr->top],id100,symbol->elem[symbol->top]->type,offset->elem[offset->top],indexlist);
                offset->elem[offset->top] = offset->elem[offset->top]+symbol->elem[symbol->top]->i;
            }
            break;
        }
    case 37:       //procedure_declaration:procedure_heading semicolon muldec_m2 procedure_block
        {
            st = tblptr->elem[tblptr->top];
            addwidth(st,offset->elem[offset->top]);
            pops(tblptr);
            pop(offset);
            enterproc(tblptr->elem[tblptr->top],symbol->elem[symbol->top+3]->name,st);    //需要词法分析器的第二个值id.name!!!!!
            break;
        }
    case 38:       //muldec_m2
        {
            st = mktable(tblptr->elem[tblptr->top]);
            pushs(tblptr,st);
            push(offset,0);
            break;
        }
    case 39:       //procedure_heading: procedure_identification
        {
            strcpy(t->name,symbol->elem[symbol->top]->name);
            break;
        }
    case 40:       //procedure_heading:procedure_identification formal_parameter_list
        {
            strcpy(t->name,symbol->elem[symbol->top+1]->name);
            break;
        }
    case 46:       //value_parameter_specification: identifier_list COLON identifier//just for correcting
        {
            MakeNULLQueue(idlist);
            break;
        }
    case 47:       //variable_parameter_specification: VAR identifier_list COLON identifier//just for correcting
        {
            MakeNULLQueue(idlist);
            break;
        }
    case 48:       //procedure_identification: PROCEDURE identifier
        {
            strcpy(t->name,symbol->elem[symbol->top]->name);
            break;
        }



    case 51:       //compound_statement: PBEGIN statement_sequence END
        {
            t->nextlist = symbol->elem[symbol->top+1]->nextlist;
            break;
        }
    case 52:       //statement_sequence: statement_sequence semicolon ctrl_m statement
        {
            backpatch(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top+1]->quad);
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 53:       //statement_sequence: statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 54:       //statement: open_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 55:       //statement: closed_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 56:       //open_statement: non_labeled_open_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 57:       //closed_statement: non_labeled_closed_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 60:       //non_labeled_closed_statement:compound_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 61:       //non_labeled_closed_statement: repeat_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 62:       //non_labeled_closed_statement:closed_if_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 63:       //non_labeled_closed_statement:closed_while_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 64:       //non_labeled_closed_statement: closed_for_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 66:       //non_labeled_open_statement:open_if_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 67:       //non_labeled_open_statement:open_while_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }
    case 68:       //non_labeled_open_statement: open_for_statement
        {
            t->nextlist = symbol->elem[symbol->top]->nextlist;
            break;
        }

    case 69:   //repeat_statement: REPEAT ctrl_m statement_sequence UNTIL repeat_n boolean_expression
        {
            backpatch(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top+1]->quad);
            backpatch(symbol->elem[symbol->top]->falselist,symbol->elem[symbol->top+4]->quad);
            t->nextlist = symbol->elem[symbol->top]->truelist;
            break;
        }

    case 70:          //open_while_statement: WHILE ctrl_m boolean_expression DO ctrl_m open_statement
        {
            backpatch(symbol->elem[symbol->top]->nextlist,symbol->elem[symbol->top+4]->quad);
            backpatch(symbol->elem[symbol->top+3]->truelist,symbol->elem[symbol->top+1]->quad);
            t->nextlist = symbol->elem[symbol->top+3]->falselist;
            sprintf(id100,"%d",symbol->elem[symbol->top+4]->quad);
            gencode(GOTO,"-","-",id100);
            break;
        }
    case 71:       //closed_while_statement: WHILE ctrl_m boolean_expression DO ctrl_m closed_statement
        {
            backpatch(symbol->elem[symbol->top]->nextlist,symbol->elem[symbol->top+4]->quad);
            backpatch(symbol->elem[symbol->top+3]->truelist,symbol->elem[symbol->top+1]->quad);
            t->nextlist = symbol->elem[symbol->top+3]->falselist;
            sprintf(id100,"%d",symbol->elem[symbol->top+4]->quad);
            gencode(GOTO,"-","-",id100);
            break;
        }
    case 72:       //open_for_statement: FOR control_variable ASSIGNMENT initial_value direction final_value DO for_m open_statement
        {
            backpatch(symbol->elem[symbol->top]->nextlist,symbol->elem[symbol->top+1]->i);
            sprintf(id100,"%d",symbol->elem[symbol->top+1]->i);
            gencode(GOTO,"-","-",id100);
            t->nextlist = symbol->elem[symbol->top+1]->nextlist;
            break;
        }
    case 73:       //closed_for_statement: FOR control_variable ASSIGNMENT initial_value direction final_value DO for_m closed_statement
        {
            backpatch(symbol->elem[symbol->top]->nextlist,symbol->elem[symbol->top+1]->i);
            sprintf(id100,"%d",symbol->elem[symbol->top+1]->i);
            gencode(GOTO,"-","-",id100);
            t->nextlist = symbol->elem[symbol->top+1]->nextlist;
            break;
        }
    case 74:       //open_if_statement: IF boolean_expression THEN ctrl_m statement
        {
            backpatch(symbol->elem[symbol->top+3]->truelist,symbol->elem[symbol->top+1]->quad);
            mergelist(symbol->elem[symbol->top+3]->falselist,symbol->elem[symbol->top]->nextlist);
            t->nextlist = symbol->elem[symbol->top+3]->falselist;
            break;
        }
    case 75:   //open_if_statement: IF boolean_expression THEN ctrl_m closed_statement ctrl_n ELSE ctrl_m open_statement
        {
            backpatch(symbol->elem[symbol->top+7]->truelist,symbol->elem[symbol->top+5]->quad);
            backpatch(symbol->elem[symbol->top+7]->falselist,symbol->elem[symbol->top+1]->quad);
            mergelist(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top]->nextlist);
            mergelist(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top+4]->nextlist);
            t->nextlist = symbol->elem[symbol->top+3]->nextlist;
            break;
        }
    case 76:   //closed_if_statement: IF boolean_expression THEN ctrl_m closed_statement ctrl_n ELSE ctrl_m closed_statement
        {
            backpatch(symbol->elem[symbol->top+7]->truelist,symbol->elem[symbol->top+5]->quad);
            backpatch(symbol->elem[symbol->top+7]->falselist,symbol->elem[symbol->top+1]->quad);
            mergelist(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top]->nextlist);
            mergelist(symbol->elem[symbol->top+3]->nextlist,symbol->elem[symbol->top+4]->nextlist);
            t->nextlist = symbol->elem[symbol->top+3]->nextlist;
            break;
        }



    case 77:           //assignment_statement: variable_access ASSIGNMENT expression
        {
            if(symbol->elem[symbol->top+2]->offset == NULL)
            {
                gencode(ASSIGN,symbol->elem[symbol->top]->addr->name,"-",symbol->elem[symbol->top+2]->addr->name);
            }
            else
            {
                gencode(OFFE,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top+2]->offset->name,symbol->elem[symbol->top]->addr->name);
            }
            break;
        }
    case 78:               //variable_access: identifier
        {
            Identifier *idaddr = lookup(symbol->elem[symbol->top]->name,tblptr->elem[tblptr->top]);
            if(idaddr)
            {
                t->addr = idaddr;
                t->offset = NULL;
            }
            else
            {
                printf("Variable %s wasn't defined in this procedure!\n",symbol->elem[symbol->top]->name);
                exit(1);
            }
            break;
        }
    case 79:           //variable_access: indexed_variable
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->offset = symbol->elem[symbol->top]->offset;
            break;
        }
    case 80:           //indexed_variable: index_expression_list RBRAC
        {
            t->addr = insertHeadList(&templink,&tempcount);
            t->offset = insertHeadList(&templink,&tempcount);
            itoa(*(symbol->elem[symbol->top+1]->offset->arrayex),id100,10);
            gencode(ASSIGN,id100,"-",t->addr->name);
            itoa(4*(symbol->elem[symbol->top+1]->offset->type-1),id100,10);
            gencode(MUL,symbol->elem[symbol->top+1]->addr->name,id100,t->offset->name);
            break;
        }
    case 81:           //index_expression_list: index_expression_list comma index_expression
        {
            temp = insertHeadList(&templink,&tempcount);
            m = symbol->elem[symbol->top+2]->i + 1;
            itoa(*(symbol->elem[symbol->top+2]->offset->arrayex+3+2*(m-1)),id100,10);
            gencode(MUL,symbol->elem[symbol->top+2]->addr->name,id100,temp->name);
            gencode(PLUS,temp->name,symbol->elem[symbol->top]->addr->name,temp->name);
            t->offset = symbol->elem[symbol->top+2]->offset;
            t->addr = temp;
            t->i = m;
            break;
        }
    case 82:          //index_expression_list: identifier LBRAC index_expression
        {
            Identifier *idaddr = lookup(symbol->elem[symbol->top+2]->name,tblptr->elem[tblptr->top]);
            if(idaddr == NULL)
            {
                exit(1);
            }
            t->offset = idaddr;
            t->addr = symbol->elem[symbol->top]->addr;
            t->i = 1;
            break;
        }
    case 83:       //index_expression: expression
        {
            t->addr = symbol->elem[symbol->top]->addr;
            break;
        }


    case 84:       //procedure_statement: identifier params
        {
            m = 0;
            while(Dequeue(actualpalist,id100))
            {
                m++;
                gencode(PARAM,"-","-",id100);
            }
            sprintf(id100,"%d",m);
            if(strcmp(symbol->elem[symbol->top+1]->name,"read") == 0||strcmp(symbol->elem[symbol->top+1]->name,"readln") == 0)
            {
                gencode(CALL,"SYSIN",id100,"-");
            }
            else if(strcmp(symbol->elem[symbol->top+1]->name,"write") == 0)     //1型
            {
                gencode(CALL,"SYSOUT",id100,"1");
            }
            else if(strcmp(symbol->elem[symbol->top+1]->name,"writeln") == 0)   //2型
            {
                gencode(CALL,"SYSOUT",id100,"2");
            }
            else
            {
                gencode(CALL,symbol->elem[symbol->top+1]->name,id100,"-");
            }
            break;
        }
    case 85:       //procedure_statement: identifier
        {
            gencode(CALL,symbol->elem[symbol->top]->name,"0","-");
            break;
        }
    case 87:       //actual_parameter_list: actual_parameter_list comma actual_parameter
        {
            Enqueue(actualpalist,symbol->elem[symbol->top]->addr->name);
            break;
        }
    case 88:       //actual_parameter_list: actual_parameter
        {
            //MakeNULLQueue(actualpalist);
            Enqueue(actualpalist,symbol->elem[symbol->top]->addr->name);
            break;
        }
    case 89:       //actual_parameter: expression
        {
            t->addr = symbol->elem[symbol->top]->addr;
            break;
        }


    case 90:       //control_variable: identifier
        {
            strcpy(t->name,symbol->elem[symbol->top]->name);
            break;
        }
    case 91:       //initial_value: expression
        {
            t->addr = symbol->elem[symbol->top]->addr;
            break;
        }
    case 92:       //direction: TO
        {
            t->type = 0;
            break;
        }
    case 93:       //direction: DOWNTO
        {
            t->type = 1;
            break;
        }
    case 94:       //final_value: expression
        {
            t->addr = symbol->elem[symbol->top]->addr;
            break;
        }


    case 95:       //boolean_expression: expression
        {
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 96:       //expression: simple_expression
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 97:       //expression: simple_expression relop simple_expression
        {
            t->truelist = makelist(fmlap);
            t->falselist = makelist(fmlap+1);
            switch(symbol->elem[symbol->top+1]->type)
            {
            case 0:     //EQUAL
                {
                    gencode(EQ,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            case 1:     //NOTEQUAL
                {
                    gencode(NE,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            case 2:     //LT
                {
                    gencode(LT,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            case 3:     //GT
                {
                    gencode(GT,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            case 4:     //LE
                {
                    gencode(LE,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            case 5:     //GE
                {
                    gencode(GE,symbol->elem[symbol->top+2]->addr->name,symbol->elem[symbol->top]->addr->name,"-");
                    break;
                }
            }
            gencode(GOTO,"-","-","-");
            break;
        }
    case 98:       //simple_expression: term
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 99:          //simple_expression: simple_expression addop boolean_m term
        {
            t->addr = insertHeadList(&templink,&tempcount);
            if(symbol->elem[symbol->top+2]->type == 0)          //+
            {
                gencode(PLUS,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
            }
            if(symbol->elem[symbol->top+2]->type == 1)          //-
            {
                gencode(SUB,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
            }
            if(symbol->elem[symbol->top+2]->type == 2)          //OR
            {
                backpatch(symbol->elem[symbol->top+3]->falselist,symbol->elem[symbol->top+1]->quad);
                clear_label_list(symbol->elem[symbol->top+3]->falselist);
                mergelist(symbol->elem[symbol->top+3]->truelist,symbol->elem[symbol->top]->truelist);
                t->truelist = symbol->elem[symbol->top+3]->truelist;
                t->falselist = symbol->elem[symbol->top]->falselist;
            }
            break;
        }
    case 100:       //term: factor
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 101:       //term: term mulop boolean_m factor //STAR SLASH DIV MOD AND
        {
            t->addr = insertHeadList(&templink,&tempcount);
            switch(symbol->elem[symbol->top+2]->s[0])
            {
            case '*':
                {
                    gencode(MUL,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
                    break;
                }
            case '/':
                {
                    gencode(RDIV,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
                    break;
                }
            case '\\':
                {
                    gencode(DIV,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
                    break;
                }
            case '%':
                {
                    gencode(MOD,symbol->elem[symbol->top+3]->addr->name,symbol->elem[symbol->top]->addr->name,t->addr->name);
                    break;
                }
            case '&':
                {
                    backpatch(symbol->elem[symbol->top+3]->truelist,symbol->elem[symbol->top+1]->quad);
                    clear_label_list(symbol->elem[symbol->top+3]->truelist);
                    t->truelist = symbol->elem[symbol->top]->truelist;
                    mergelist(symbol->elem[symbol->top+3]->falselist,symbol->elem[symbol->top]->falselist);
                    t->falselist = symbol->elem[symbol->top+3]->falselist;
                    break;
                }
            }
            break;
        }
    case 102:       //factor: sign factor
        {
            t->addr = insertHeadList(&templink,&tempcount);
            if(symbol->elem[symbol->top+1]->type == 0)
            {
                gencode(ASSIGN,symbol->elem[symbol->top]->addr->name,"-",t->addr->name);
            }
            if(symbol->elem[symbol->top+1]->type == 1)
            {
                gencode(MINUS,symbol->elem[symbol->top]->addr->name,"-",t->addr->name);
            }
            break;
        }
    case 103:       //factor: exponentiation
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 104:       //exponentiation: primary
        {
            t->addr = symbol->elem[symbol->top]->addr;
            t->truelist = symbol->elem[symbol->top]->truelist;
            t->falselist = symbol->elem[symbol->top]->falselist;
            break;
        }
    case 105:       //primary: variable_access
        {
            if(symbol->elem[symbol->top]->offset == NULL)       //简单变量
            {
                t->addr = symbol->elem[symbol->top]->addr;
            }
            else
            {
                t->addr = insertHeadList(&templink,&tempcount);
                gencode(EOFF,symbol->elem[symbol->top]->addr->name,symbol->elem[symbol->top]->offset->name,t->addr->name);
            }
            break;
        }
    case 106:       //primary: unsigned_constant
        {
            t->addr = insertHeadList(&templink,&tempcount);
            if(symbol->elem[symbol->top]->type == 0)            //integer
            {
                itoa(symbol->elem[symbol->top]->i,id100,10);
                gencode(ASSIGN,id100,"-",t->addr->name);
            }
            if(symbol->elem[symbol->top]->type == 1)            //real
            {
                sprintf(id100,"%f",symbol->elem[symbol->top]->f);
                gencode(ASSIGN,id100,"-",t->addr->name);
            }
            if(symbol->elem[symbol->top]->type == 2)        //CHARACTER_STRING
            {
                gencode(ASSIGN,symbol->elem[symbol->top]->s,"-",t->addr->name);
            }
            break;
        }
    case 107:       //primary: LPAREN expression RPAREN
        {
            t->addr = symbol->elem[symbol->top+1]->addr;
            t->truelist = symbol->elem[symbol->top+1]->truelist;
            t->falselist = symbol->elem[symbol->top+1]->falselist;
            break;
        }
    case 108:       //primary: NOT primary
        {
            t->truelist = symbol->elem[symbol->top]->falselist;
            t->falselist = symbol->elem[symbol->top]->truelist;
            break;
        }


    case 109:       //unsigned_constant: unsigned_number
        {
            if(symbol->elem[symbol->top]->type == 0)
            {
                t->type = 0;
                t->i = symbol->elem[symbol->top]->i;
            }
            if(symbol->elem[symbol->top]->type == 1)
            {
                t->type = 1;
                t->f = symbol->elem[symbol->top]->f;
            }
            break;
        }
    case 110:       //unsigned_constant: CHARACTER_STRING
        {
            t->type = 2;
            strcpy(t->s,symbol->elem[symbol->top]->s);
            break;
        }
    case 111:       //unsigned_number: unsigned_integer
        {
            t->type = 0;
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 112:       //unsigned_number: unsigned_real
        {
            t->type = 1;
            t->f = symbol->elem[symbol->top]->f;
            break;
        }
    case 113:       //unsigned_integer: DIGSEQ
        {
            t->i = symbol->elem[symbol->top]->i;
            break;
        }
    case 114:       //unsigned_real: REALNUMBER
        {
            t->f = symbol->elem[symbol->top]->f;
            break;
        }

    case 115:       //addop: PLUS
        {
            t->type = 0;
            break;
        }
    case 116:       //addop: MINUS
        {
            t->type = 1;
            break;
        }
    case 117:       //addop: OR
        {
            t->type = 2;
            break;
        }
    case 118:       //mulop: STAR
        {
            t->s[0] = '*';
            break;
        }
    case 119:       //mulop: SLASH
        {
            t->s[0] = '/';
            break;
        }
    case 120:       //mulop: DIV
        {
            t->s[0] = '\\';
            break;
        }
    case 121:       //mulop: MOD
        {
            t->s[0] = '%';
            break;
        }
    case 122:       //mulop: AND
        {
            t->s[0] = '&';
            break;
        }

    case 123:       //relop: EQUAL
        {
            t->type = 0;
            break;
        }
    case 124:       //relop: NOTEQUAL
        {
            t->type = 1;
            break;
        }
    case 125:       //relop: LT
        {
            t->type = 2;
            break;
        }
    case 126:       //relop: GT
        {
            t->type = 3;
            break;
        }
    case 127:       //relop:LE
        {
            t->type = 4;
            break;
        }
    case 128:       //relop: GE
        {
            t->type = 5;
            break;
        }

    case 129:       //identifier: IDENTIFIER
        {
            strcpy(t->name,symbol->elem[symbol->top]->name);
            break;
        }

    case 132:       //boolean_m: /* empty */
        {
            t->quad = fmlap;
            break;
        }
    case 133:       //ctrl_m: /* empty */
        {
            t->quad = fmlap;
            break;
        }
    case 134:       //ctrl_n: /* empty */
        {
            t->nextlist = makelist(fmlap);
            gencode(GOTO,"-","-","-");
            break;
        }
    case 135:       //repeat_n: /* empty */
        {
            t->quad = fmlap;
            break;
        }
    case 136:       //for_m: /* empty */ stack:FOR control_variable ASSIGNMENT initial_value direction final_value DO ..
        {
            strcpy(t->name,symbol->elem[symbol->top+5]->name);      //id
            gencode(ASSIGN,symbol->elem[symbol->top+3]->addr->name,"-",t->name);
            temp = insertHeadList(&templink,&tempcount);            //final_value
            gencode(ASSIGN,symbol->elem[symbol->top+1]->addr->name,"-",temp->name);
            m = fmlap;
            sprintf(id100,"%d",m+2);
            gencode(GOTO,"-","-",id100);
            t->i = m+1;

            if(symbol->elem[symbol->top+2]->type == 0)        //to
            {
                gencode(PLUS,t->name,"1",t->name);
                gencode(GT,t->name,temp->name,"-");
            }
            else if(symbol->elem[symbol->top+2]->type == 1)     //downto
            {
                gencode(SUB,t->name,"1",t->name);
                gencode(LT,t->name,temp->name,"-");
            }
            t->nextlist = makelist(fmlap-1);
            break;
        }
    }


    for(i = 0;i < len;i++)
    {
        pop(state);
    }
    for(i = 0;i < len;i++)
    {
        array[i] = popsym(symbol);
    }
    t->symbolnum = yyr1[k];
    pushsym(symbol,t);

    //printf("&&");
    /*
    printf("%s",yytname[yyr1[k]]);      //begin打印产生式
    printf("%s","->");
    for(i = len - 1 ;i >= 0;i--)
    {
        printf("%s ",yytname[array[i]]);
    }
    printf("\n");                       ///end
    */

    //printf("\n");
    //PrintStack(state);
    //printf("%c",'&');
    //PrintSymStack(symbol);

    symbolnum = symbol->elem[symbol->top]->symbolnum - TN;    /*执行goto动作*/
    statenum = state->elem[state->top];

    if(yypgoto[symbolnum] == YYPACT_NINF)
    {
        push(state,yydefgoto[symbolnum]);
    }
    else
    {
        index = yypgoto[symbolnum] + statenum;
        if((index >= LCHECK) || (yycheck[index] != statenum))
        {
            push(state,yydefgoto[symbolnum]);
        }
        else
        {
            push(state,yytable[index]);
        }
    }
}

Token ReadToken()
{
    char strLine[1024];
    char n1[10];
    char n2[1027];
    int i=0,j=0;
    int t1;
    Token rt = (Token)malloc(sizeof(To));
    rt->addr = NULL;
    rt->offset = NULL;
    rt->truelist = NULL;
    rt->falselist = NULL;
    rt->nextlist = NULL;

    if(feof(fp)||(NULL == fgets(strLine,1024,fp)))
    {
        rt->symbolnum = 0;
        return rt;
    }

    for(i=1;;i++)
    {
        if(strLine[i] == ',')
        {
            n1[i-1] = '\0';
            t1 = atoi(n1);
            break;
        }
        n1[i-1] = strLine[i];
    }
    rt->symbolnum = yytranslate[t1];
    i++;

    switch(t1)
    {
    case 36:        //id
        {
            while(strLine[i] != ')')
            {
                n2[j] = strLine[i];
                j++;
                i++;
            }
            n2[j] = '\0';
            strcpy(rt->name,n2);
            break;
        }
    case 37:        //int
        {
            while(strLine[i] != ')')
            {
                n2[j] = strLine[i];
                j++;
                i++;
            }
            n2[j] = '\0';
            rt->i = atoi(n2);
            break;
        }
    case 38:        //float
        {
            while(strLine[i] != ')')
            {
                n2[j] = strLine[i];
                j++;
                i++;
            }
            n2[j] = '\0';
            rt->f = atof(n2);
            break;
        }
    case 39:        //string
        {
            while(strLine[i] != ')')
            {
                n2[j] = strLine[i];
                j++;
                i++;
            }
            n2[j] = '\0';
            strcpy(rt->s,n2);
            break;
        }
    }
    return rt;
}


void gencode(int op,char *arg1,char *arg2,char* ret)
{
    fmlay[fmlap] = (pFour)malloc(sizeof(FourElemFormula));
    fmlay[fmlap]->op = op;
    strcpy(fmlay[fmlap]->arg1,arg1);
    strcpy(fmlay[fmlap]->arg2,arg2);
    strcpy(fmlay[fmlap]->ret,ret);
    fmlap++;
}

void backpatch(LabelNode* lis,int labelnum)
{
    LabelNode* t = lis;
    char numstr[60];
    sprintf(numstr,"%d",labelnum);

    while(t != NULL)
    {
        strcpy(fmlay[t->label]->ret,numstr);
        t = t->next;
    }
}
