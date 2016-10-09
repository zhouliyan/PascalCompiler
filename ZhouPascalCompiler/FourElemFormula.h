typedef struct{
    int op;
    char arg1[64];
    char arg2[64];
    char ret[64];
}FourElemFormula;
typedef FourElemFormula* pFour;


void PrintFmla(pFour *fmlay,int fmlap)
{
    int i;
    FILE *imfp = fopen("imcode.txt","w");             //中间代码

    for(i = 1;i < fmlap;i++)
    {
        switch(fmlay[i]->op)
        {
        case ASSIGN:
            {
                fprintf(imfp,"%d: %s := %s\n",i,fmlay[i]->ret,fmlay[i]->arg1);
                break;
            }
        case PLUS:
            {
                fprintf(imfp,"%d: %s := %s + %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case SUB:
            {
                fprintf(imfp,"%d: %s := %s - %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case MUL:
            {
                fprintf(imfp,"%d: %s := %s * %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case RDIV:
            {
                fprintf(imfp,"%d: %s := %s / %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case MINUS:
            {
                fprintf(imfp,"%d: %s := minus %s\n",i,fmlay[i]->ret,fmlay[i]->arg1);
                break;
            }
        case DIV:
            {
                fprintf(imfp,"%d: %s := %s div %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case MOD:
            {
                fprintf(imfp,"%d: %s := %s mod %s\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case EQ:
            {
                fprintf(imfp,"%d: if %s=%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case LT:
            {
                fprintf(imfp,"%d: if %s<%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case GT:
            {
                fprintf(imfp,"%d: if %s>%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case LE:
            {
                fprintf(imfp,"%d: if %s<=%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case GE:
            {
                fprintf(imfp,"%d: if %s>=%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case NE:
            {
                fprintf(imfp,"%d: if %s!=%s goto %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case OFFE:
            {
                fprintf(imfp,"%d: %s[%s] := %s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                break;
            }
        case EOFF:
            {
                fprintf(imfp,"%d: %s := %s[%s]\n",i,fmlay[i]->ret,fmlay[i]->arg1,fmlay[i]->arg2);
                break;
            }
        case GOTO:
            {
                fprintf(imfp,"%d: goto %s\n",i,fmlay[i]->ret);
                break;
            }
        case PARAM:
            {
                fprintf(imfp,"%d: param %s\n",i,fmlay[i]->ret);
                break;
            }
        case CALL:      //call 过程名，参数个数
            {
                if(strcmp(fmlay[i]->ret,"-") == 0)
                {
                    fprintf(imfp,"%d: call %s,%s\n",i,fmlay[i]->arg1,fmlay[i]->arg2);
                }
                else
                {
                    fprintf(imfp,"%d: call %s,%s,%s\n",i,fmlay[i]->arg1,fmlay[i]->arg2,fmlay[i]->ret);
                }
                break;
            }
        }
    }
    fclose(imfp);
}

void clearFmlay(pFour *fmlay,int fmlap)
{
    int i;
    for(i = 0;i < fmlap;i++)
    {
        free(fmlay[i]);
    }
}

