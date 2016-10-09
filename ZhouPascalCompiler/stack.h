typedef struct{      //ÕûĞÍÕ»
    int top;
    int elem[N];
}stack;
typedef stack* pstack;

typedef struct{     //·ûºÅÕ»
    int top;
    Token elem[N];
}symstack;
typedef symstack* psymstack;

typedef struct{      //·ûºÅ±íÖ¸ÕëÕ»
    int top;
    symtbl* elem[N];
}sstack;
typedef sstack* psstack;


void MakeNull(pstack S)
{
    S->top = N ;
}

void push(pstack S,int opd)
{
    if(S->top == 0)
    {
        return ;
    }
    S->top--;
    S->elem[S->top] = opd;
}

int pop(pstack S)
{
    if(S->top == N)
    {
        return -1;
    }
    return S->elem[S->top++];
}

void MakeNullsym(psymstack S)
{
    S->top = N ;
}

void pushsym(psymstack S,Token opd)
{
    if(S->top == 0)
    {
        return ;
    }
    S->top--;
    S->elem[S->top] = opd;
}

int popsym(psymstack S)
{
    int ret = S->elem[S->top]->symbolnum;
    free(S->elem[S->top]);
    S->elem[S->top] = NULL;
    S->top++;
    return ret;
}

void PrintStack(pstack S)   /*Ã»´òÓ¡¿ÕĞĞ*/
{
    int i;
    for(i = N-1;i >= S->top;i--)
    {
        printf("%d ",S->elem[i]);
    }
}

void PrintSymStack(psymstack S)      //´òÓ¡·ûºÅÕ»
{
    int i;
    for(i = N-1;i >= S->top;i--)
    {
        printf("%s ",yytname[S->elem[i]->symbolnum]);
    }
}

void MakeNulls(psstack S)
{
    S->top = N ;
}

void pushs(psstack S,symtbl* opd)
{
    if(S->top == 0)
    {
        return ;
    }
    S->top--;
    S->elem[S->top] = opd;
}

int pops(psstack S)
{
    if(S->top == N)
    {
        return -1;
    }
    else
    {
        S->top++;
        return 0;
    }
}



