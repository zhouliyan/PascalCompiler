typedef struct intnode{
    int label;
    struct intnode *next;
}LabelNode;

LabelNode* makelist(int para)
{
    LabelNode* head = (LabelNode*)malloc(sizeof(LabelNode));
    head->next = NULL;
    head->label = para;
    return head;
}

void mergelist(LabelNode* list1,LabelNode* list2)     //list1/2都不为空,list2并到list1上去
{
    LabelNode* nextnode = list1;
    if(nextnode == NULL)
    {
        return ;
    }
    while(nextnode->next != NULL)
    {
        nextnode = nextnode->next;
    }
    (*nextnode).next = list2;
}

void clear_label_list(LabelNode* lalist)
{
    LabelNode* t;
    if(lalist == NULL)
    {
        return ;
    }
    while(lalist->next != NULL)
    {
        t = lalist->next;//保存下一结点的指针
        free(lalist);
        lalist = t;      //表头下移
    }
    free(lalist);
    lalist = NULL;
}

/* 初始化线性表，即置单链表的表头指针为空 */
void initList(Identifier **pNode)
{
    *pNode = NULL;
}

/*向单链表的表头插入一个元素 */
Identifier * insertHeadList(Identifier **pNode,int *tempcount)
{
    Identifier *pInsert;
    pInsert = (Identifier *)malloc(sizeof(Identifier));
    memset(pInsert,0,sizeof(Identifier));

    pInsert->arrayex = NULL;
    pInsert->offset = -1;
    pInsert ->type = -1;
    pInsert ->type = -1;

    sprintf(pInsert->name,"t%d",*tempcount);
    (*tempcount)++;
    pInsert->next_hash = *pNode;

    *pNode = pInsert;
    return pInsert;
}

/*清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
void clearList(Identifier *pHead)
{
    Identifier *pNext;            //定义一个与pHead相邻节点

    if(pHead == NULL)
    {
        return;
    }
    while(pHead->next_hash != NULL)
    {
        pNext = pHead->next_hash;//保存下一结点的指针
        free(pHead);
        pHead = pNext;      //表头下移
    }
    free(pHead);
    pHead = NULL;
    return ;
}
