void PrintSymTable(symtbl *initst)      //print symboltable
{
    int i,j,k,l;
    Identifier *pid;
    printf("\nSymTable:\n");
    printf("program width:%d\n",initst->width);
    for(i = 0;i < PRIME;i++)
    {
        pid = initst->SymbolTable[i];
        while(pid != NULL)
        {
            printf("name:%s ",pid->name);
            printf("offset:%d ",pid->offset);
            printf("type:%d \n ",pid->type);
            if(pid->type==2 || pid->type==3)
            {
                printf("c:%d ",*(pid->arrayex));
                printf("ndim:%d ",*(pid->arrayex+1));
                for(l=2;l<=*(pid->arrayex+1)*2;l+=2)
                {
                    printf("%d,",*(pid->arrayex+l));
                    printf("%d ",*(pid->arrayex+(l+1)));
                }

            }
            printf("\n");
            pid = pid->next_hash;
        }
    }

    for(k = 0;k < initst->subprocptr;k++)
    {
        printf("subproc%d name:%s width:%d\n",k,initst->SubprocArray[k]->name,initst->SubprocArray[k]->s->width);
        for(j = 0;j < PRIME;j++)
        {
            pid = initst->SubprocArray[k]->s->SymbolTable[j];
            //system("pause");
            while(pid != NULL)
            {
                printf("name:%s ",pid->name);
                printf("offset:%d ",pid->offset);
                printf("type:%d \n ",pid->type);
                if(pid->type==2 || pid->type==3)
                {
                    printf("c:%d ",*(pid->arrayex));
                    printf("ndim:%d ",*(pid->arrayex+1));
                    for(i=2;i<=*(pid->arrayex+1)*2;i+=2)
                    {
                        printf("%d,",*(pid->arrayex+i));
                        printf("%d ",*(pid->arrayex+(i+1)));
                    }

                }
                printf("\n");
                pid = pid->next_hash;
            }
        }
    }
}


