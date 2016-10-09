#define N 1000

#define LEX_ID 36
#define LEX_INT 37
#define LEX_REAL 38
#define LEX_STRING 39
#define LEX_PLUS 40
#define LEX_MINUS 41
#define LEX_MUL 42
#define LEX_RDIV 43
#define LEX_EQ 44
#define LEX_LT 45
#define LEX_GT 46
#define LEX_LE 47
#define LEX_GE 48
#define LEX_NE 49
#define LR_BRAC 50
#define RR_BRAC 51
#define COMMA 52
#define OTHERWISE 53
#define F_STOP 54
#define RANGE 55
#define COLON 56
#define LEX_ASSIGN 57
#define SEMIC 58
#define CAP 59
#define EXP 60
#define LS_BRAC 61
#define RS_BRAC 62
#define FORWARD 63
#define EXTERNAL 64

char* key_table[36] = {"","and","array","begin","case","const","div","do","downto","else",
"end","file","for","function","goto","if","in","label","mod","nil","not","of","or",
"packed","procedure","program","record","repeat","set","then","to","type","until",
"var","while","with"};


int lexeme_beginning = 0;           /*开始指针*/
int forward = 0;                    /*向前指针*/
char *buffer = NULL;

int token_scan(char temp[][64]);
void ReadFile();
char mgetchar();
char *copy_token(int flag);
float matof(char *token);
int check_ktable(char *token);
char *get_substr(char *token,int start,int end);
void error_handle();

int line = 1;       /*行数*/
int flength;
int error[1000][2];
int perr = 0;
char error_ch;

int token_analyze()
{
    int i=0;
    char temp[2][64];
    FILE *fp= fopen("lex.txt", "w");
    if (fp == NULL)
    {
        printf("Open LEXfile ERROR!\n");
        exit(1);
    }

    ReadFile();

    while(i>-2 && forward<flength)
    {
        lexeme_beginning = forward;
        i = token_scan(temp);
        if(i == 0)
        {
            fprintf(fp,"(%s,%s)\n",temp[0],temp[1]);
        }
    }

    fclose(fp);
    if(perr>0)
    {
        error_handle();
        return 1;
    }
    return 0;
}

int token_scan(char temp[][64])
{
    char ch;
    char *token;
    int count = 0;
    float token_num;
    int comment_line;

    ch = mgetchar();
    while(ch == ' '||ch == '\t'||ch == '\n')
    {
        if(ch == '\n')
        {
            line++;
        }
        ch = mgetchar();        /*forward总比ch多一,ch和lexeme_begin指向同一个*/
        lexeme_beginning++;
    }

    if(ch == '{')
    {
        comment_line = line;
        ch = mgetchar();
        lexeme_beginning++;
        if(ch == '}')
        {
            return -1;
        }
        else if(ch == '*')
        {
            while(1)
            {
                while(ch != '*')
                {
                    if(ch =='\0')
                    {
                        printf("Line %d ERROR:unterminated comment!\n",comment_line);
                        return -2;
                    }
                    ch = mgetchar();
                    lexeme_beginning++;
                    if(ch == '\n')
                    {
                        line++;
                    }
                }
                ch = mgetchar();
                lexeme_beginning++;
                if(ch == '\n')
                {
                    line++;
                }
                if(ch == '}')
                {
                    return -1;
                }
            }

        }
        else
        {
            while(ch != '}'&&ch != '\0'&&ch != '\n')
            {
                ch = mgetchar();
                lexeme_beginning++;
            }
            if(ch == '\n')
            {
                if(perr < N)
                {
                    error[perr][0] = 6;
                    error[perr][1] = line;
                    perr++;
                    return 1;
                }
                else
                {
                    printf("Too much Error!Please check your program!\n");
                    return -2;
                }
            }
            if(ch == '\0')
            {
                printf("Line %d ERROR:unterminated comment!\n",comment_line);
                return -2;
            }
            return -1;
        }
    }

    if(isalpha(ch))    /*标识符类型*/
    {
        ch = mgetchar();
        count++;
        while(isalpha(ch)||isdigit(ch))
        {
            ch = mgetchar();
            count++;
        }
        if(count > 127)     /*最大长度为127*/
        {
            if(perr < N)
            {
                error[perr][0] = 1;
                error[perr][1] = line;
                perr++;
            }
            else
            {
                printf("Too much Error!Please check your program!\n");
                return -2;
            }
        }

        forward--;      /*forward指向other字符*/
        token = copy_token(0);
        if(strcmp(token,"otherwise") == 0)
        {
            sprintf(temp[0],"%d",OTHERWISE); /*种别*/
            strcpy(temp[1], "0");            /*属性值*/
            return 0;
        }
        else if(strcmp(token,"forward") == 0)
        {
            sprintf(temp[0],"%d",FORWARD); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
        }
        else if(strcmp(token,"external") == 0||strcmp(token,"extern") == 0)
        {
            sprintf(temp[0],"%d",EXTERNAL); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
        }
        else if(check_ktable(token) != -1)
        {
            sprintf(temp[0],"%d",check_ktable(token)); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
        }
        else
        {
            sprintf(temp[0],"%d",LEX_ID); /*种别*/
            strcpy(temp[1], token);       /*属性值*/
            return 0;
        }
    }

    if(isdigit(ch))         /*无符号整数与无符号浮点数（含科学计数法）*/
    {
        ch = mgetchar();
        while(isdigit(ch))
        {
            ch = mgetchar();
        }
        if(ch == '.')
        {
            ch = mgetchar();
            if(isdigit(ch))
            {
                ch = mgetchar();
                while(isdigit(ch))
                {
                    ch = mgetchar();
                }
                if(ch != 'E')
                {
                    forward--;
                    token = copy_token(1);
                    token_num = matof(token);       /*token_num为浮点数类型*/
                    sprintf(temp[0],"%d",LEX_REAL); /*种别*/
                    sprintf(temp[1],"%f",token_num);       /*属性值*/
                    return 0;
                }
            }
            else if(ch == '.')
            {
                forward-=2;
                token = copy_token(1);
                sprintf(temp[0],"%d",LEX_INT); /*种别*/
                strcpy(temp[1],token);       /*属性值*/
                return 0;
            }
            else
            {
                forward--;
                if(perr < N)
                {
                    error[perr][0] = 2;
                    error[perr][1] = line;
                    perr++;
                    return 1;
                }
                else
                {
                    printf("Too much Error!Please check your program!\n");
                    return -2;
                }
            }
        }

        if(ch == 'E')
        {
            ch = mgetchar();
            if(ch == '+' || ch == '-')
            {
                ch = mgetchar();
                if(!isdigit(ch))
                {
                    forward--;
                    if(perr < N)
                    {
                        error[perr][0] = 2;
                        error[perr][1] = line;
                        perr++;
                        return 1;
                    }
                    else
                    {
                        printf("Too much Error!Please check your program!\n");
                        return -2;
                    }
                }
            }
            if(isdigit(ch))
            {
                ch = mgetchar();
                while(isdigit(ch))
                {
                    ch = mgetchar();
                }
                forward--;
                token = copy_token(1);
                sprintf(temp[0],"%d",LEX_REAL); /*种别*/
                strcpy(temp[1], token);       /*属性值*/
                return 0;
            }
            else
            {
                forward--;
                if(perr < N)
                {
                    error[perr][0] = 2;
                    error[perr][1] = line;
                    perr++;
                    return 1;
                }
                else
                {
                    printf("Too much Error!Please check your program!\n");
                    return -2;
                }
            }
        }

        forward--;
        token = copy_token(1);
        sprintf(temp[0],"%d",LEX_INT); /*种别*/
        strcpy(temp[1], token);       /*属性值*/
        return 0;
    }

    switch(ch)                      /*运算符*/
    {
        case '+':
        {
            sprintf(temp[0],"%d",LEX_PLUS); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '-':
        {
            sprintf(temp[0],"%d",LEX_MINUS); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '/':
        {
            sprintf(temp[0],"%d",LEX_RDIV); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '*':
        {
            ch = mgetchar();
            if(ch == '*')
            {
                sprintf(temp[0],"%d",EXP); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else
            {
                forward--;
                sprintf(temp[0],"%d",LEX_MUL); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            return 0;
            break;
        }
        case '=':
        {
            sprintf(temp[0],"%d",LEX_EQ); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '<':
        {
            ch = mgetchar();
            if(ch == '=')
            {
                sprintf(temp[0],"%d",LEX_LE); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else if(ch == '>')
            {
                sprintf(temp[0],"%d",LEX_NE); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else
            {
                forward--;
                sprintf(temp[0],"%d",LEX_LT); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            return 0;
            break;
        }
        case '>':
        {
            ch = mgetchar();
            if(ch == '=')
            {
                sprintf(temp[0],"%d",LEX_GE); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else
            {
                forward--;
                sprintf(temp[0],"%d",LEX_GT); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            return 0;
            break;
        }
        case '(':
        {
            sprintf(temp[0],"%d",LR_BRAC); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case ')':
        {
            sprintf(temp[0],"%d",RR_BRAC); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case ',':
        {
            sprintf(temp[0],"%d",COMMA); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '.':
        {
            ch = mgetchar();
            if(ch == '.')
            {
                sprintf(temp[0],"%d",RANGE); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else
            {
                forward--;
                sprintf(temp[0],"%d",F_STOP); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            return 0;
            break;
        }
        case ':':
        {
            ch = mgetchar();
            if(ch == '=')
            {
                sprintf(temp[0],"%d",LEX_ASSIGN); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            else
            {
                forward--;
                sprintf(temp[0],"%d",COLON); /*种别*/
                strcpy(temp[1], "0");       /*属性值*/
            }
            return 0;
            break;
        }
        case ';':
        {
            sprintf(temp[0],"%d",SEMIC); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '^':
        {
            sprintf(temp[0],"%d",CAP); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '[':
        {
            sprintf(temp[0],"%d",LS_BRAC); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case ']':
        {
            sprintf(temp[0],"%d",RS_BRAC); /*种别*/
            strcpy(temp[1], "0");       /*属性值*/
            return 0;
            break;
        }
        case '\'':
        {
            ch = mgetchar();
            while(ch != '\'')
            {
                ch = mgetchar();
                if(ch == '\0')
                {
                    if(perr < N)
                    {
                        error[perr][0] = 3;
                        error[perr][1] = line;
                        perr++;
                        return 1;
                    }
                    else
                    {
                        printf("Too much Error!Please check your program!\n");
                        return -2;
                    }
                    return 1;
                }
            }
            token = copy_token(1);
            sprintf(temp[0],"%d",LEX_STRING); /*种别*/
            strcpy(temp[1], token);       /*属性值*/
            return 0;
            break;
        }
        case '\0':
        {
            return -2;
            break;
        }
        default:
        {
            if(perr < N)
            {
                error[perr][0] = 4;
                error[perr][1] = line;
                error_ch = ch;
                perr++;
                return 1;
            }
            else
            {
                printf("Too much Error!Please check your program!\n");
                return -2;
            }
        }
    }
}

void ReadFile()
{
   FILE *pfile;

    pfile = fopen("code.txt", "r");
    if (pfile == NULL)
    {
        printf("Open CODEfile ERROR!\n");
        exit(1);
    }
    fseek(pfile, 0, SEEK_END);
    flength = ftell(pfile);
    buffer = (char *)malloc((flength + 1) * sizeof(char));
    rewind(pfile);
    flength = fread(buffer, 1, flength, pfile);
    buffer[flength] = '\0';
    fclose(pfile);
}

char mgetchar()
{
    char ch = *(buffer + forward);
    forward++;
    return ch;
}

char *copy_token(int flag)  //从lexeme_beginning开始拷贝到forward
{
    int length = forward - lexeme_beginning;        /*要拷贝的字符串长度*/
    char* token = (char*)calloc(sizeof(char),length+1);
    char* pcode = buffer + lexeme_beginning;
    int i;

    if(flag == 0 && length > 63)
    {
        if(perr < N)
        {
            error[perr][0] = 5;
            error[perr][1] = line;
            perr++;
        }
        else
        {
            printf("Too much Error!Please check your program!\n");
        }
        for(i=0;i<63;i++)
        {
            token[i]=*pcode;
            pcode++;
        }
        token[63]='\0'; /*加上字符串结束符*/
    }
    else
    {
        for(i=0;i<length;i++)
        {
            token[i]=*pcode;
            pcode++;
        }
        token[length]='\0'; /*加上字符串结束符*/
    }
    return token;       /*返回分配的字符数组地址 */
}


float matof(char *token)
{
    int i;
    float before;
    int after;
    int l = strlen(token);
    for(i = 0;i < l;i++)
    {
        if(token[i] == 'E')
        {
            before = atof(get_substr(token,0,i));
            if(token[i+1] == '+')
            {
                after = atoi(get_substr(token,i+2,l));
                return before*pow(10,after);
            }
            else if(token[i+1] == '-')
            {
                after = atoi(get_substr(token,i+2,l));
                return before*pow(10,-after);
            }
            else
            {
                after = atoi(get_substr(token,i+1,l));
                return before*pow(10,after);
            }
        }
    }
    return atof(token);
}

int check_ktable(char *token)
{
    int i;
    for(i=1;i<36;i++)
    {
        if(strcmp(key_table[i],token) == 0)
        {
            return i;
        }
    }
    return -1;
}

char *get_substr(char *token,int start,int end) /*含左不含右*/
{
    int length = end - start;       /*要拷贝的字符串长度*/
    char* ret = (char*)calloc(sizeof(char),length+1);
    char* pcode = token + start;
    int i;

    for(i=0;i<length;i++)
    {
        ret[i]=*pcode;
        pcode++;
    }
    ret[length]='\0';   /*加上字符串结束符*/
    return ret;       /*返回分配的字符数组地址 */
}


void error_handle()
{
    int i;
    for(i = 0;i < perr;i++)
    {
        switch(error[i][0])
        {
            case 1:
            {
                printf("Line %d ERROR:Too long identifier!\n",error[i][1]);
                break;
            }
            case 2:
            {
                printf("Line %d ERROR:Illeagle float num!\n",error[i][1]);
                break;
            }
            case 3:
            {
                printf("Line %d ERROR:No end of string!\n",error[i][1]);
                break;
            }
            case 4:
            {
                printf("Line %d ERROR:Illegal char '%c'\n",error[i][1],error_ch);
                break;
            }
            case 5:
            {
                printf("Line %d Warning:identifier will be cut off!\n",error[i][1]);
                break;
            }
            case 6:
            {
                printf("Line %d ERROR:unterminated comment!\n",error[i][1]);
                break;
            }
            default:
            {
                continue;
            }
        }
    }
}

