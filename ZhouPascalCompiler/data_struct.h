typedef struct{
    int symbolnum;
    int type;         //type index_listxiao
    char name[64];     //id36
    int i;          //int37 width index_listda arrayndim
    float f;        //float38
    char s[1027];        //string39

    struct idnode *addr;        //node pointer type
    struct idnode *offset;

    int quad;
    struct intnode *truelist;
    struct intnode *falselist;
    struct intnode *nextlist;
}To;
typedef To* Token;


