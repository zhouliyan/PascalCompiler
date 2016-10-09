#define QUESIZE 1000        //循环队列的最大存储空间

typedef struct queue
{
    char pBase[QUESIZE][64];             //字符串型
    int front;                          //指向队列第一个元素，出的一端
    int rear;                           //指向队列最后一个元素的下一个元素，入的一端
}queue,*pqueue;

void MakeNULLQueue(pqueue Q)
{
    Q->front=0;                         //初始化参数
    Q->rear=0;
}

int FullQueue(pqueue Q)
{
    if(Q->front==(Q->rear+1)%QUESIZE)    //判断循环队列是否满，留一个预留空间不用
        return 1;
    else
        return 0;
}

int EmptyQueue(pqueue Q)
{
    if(Q->front==Q->rear)    //判断是否为空
        return 1;
    else
        return 0;
}

int Enqueue(pqueue Q, char *val)
{
    if(FullQueue(Q))
        return 0;
    else
    {
        strcpy(Q->pBase[Q->rear],val);
        Q->rear=(Q->rear+1)%QUESIZE;
        return 1;
    }
}

int Dequeue(pqueue Q, char *val)
{
    if(EmptyQueue(Q))
    {
        return 0;
    }
    else
    {
        strcpy(val,Q->pBase[Q->front]);
        Q->front=(Q->front+1)%QUESIZE;
        return 1;
    }
}

typedef struct intqueue
{
    int pBase[QUESIZE];             //整型
    int front;                          //指向队列第一个元素，出的一端
    int rear;                           //指向队列最后一个元素的下一个元素，入的一端
}intqueue,*pintqueue;

void PrintIntQueue(pintqueue Q)
{
    int i;
    if(Q->front==Q->rear)
    {
        printf("empty queue!");
    }
    for(i=Q->front;i<Q->rear;i=(i+1)%QUESIZE)
    {
        printf("%d",Q->pBase[i]);
    }
}

void IntMakeNULLQueue(pintqueue Q)
{
    Q->front=0;                         //初始化参数
    Q->rear=0;
}

int IntFullQueue(pintqueue Q)
{
    if(Q->front==(Q->rear+1)%QUESIZE)    //判断循环队列是否满，留一个预留空间不用
        return 1;
    else
        return 0;
}

int IntEmptyQueue(pintqueue Q)
{
    if(Q->front==Q->rear)    //判断是否为空
        return 1;
    else
        return 0;
}

int IntEnqueue(pintqueue Q, int val)
{
    if(IntFullQueue(Q))
        return 0;
    else
    {
        Q->pBase[Q->rear] = val;
        Q->rear=(Q->rear+1)%QUESIZE;
        return 1;
    }
}

int IntDequeue(pintqueue Q, int *val)
{
    if(IntEmptyQueue(Q))
    {
        return 0;
    }
    else
    {
        *val = Q->pBase[Q->front];
        Q->front=(Q->front+1)%QUESIZE;
        return 1;
    }
}

