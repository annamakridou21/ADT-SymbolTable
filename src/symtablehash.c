#include "symtable.h"
#define HASH_MULTIPLIER 65599
#define SIZE 509

/*ULOPOIHSH ME KSEXWRISTES ALUSIDES - LISTES ANA BUCKET*/

struct SymTable_T{
    struct node* head;      /*o Symbol Table einai mia kenh domh pou se auth to to arxeio tha einai ena oloklhro hashtable*/
    unsigned int length;      /*mia metavlhth length gia na mporw na auksanw kai na meiwnw ton arithmo twn nodes eukola*/
};                          /*giauto periexei enan pointer ton opoion ustera tha valoume na deixnei ston prwto komvo ths kathe listas tou kathe keliou tou table*/

struct node {
    char* key;
    char* temp;             /*to temp to xrhsimopoiw gia na apothikeuw to antigrafo to pckey sth put(tha ekshghthei parakatw)*/
    void* value;            /*to struct auto perigrafei ta nodes ths listas pou periexoun to key kai to value. epishs xrhsimopoiw*/
    struct node* next;
};

typedef struct node* Node;       /*sunonymo tou node gia eukolia*/

static unsigned int SymTable_hash(const char *pcKey){
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)			
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash;
}

SymTable_T SymTable_new(void){
    SymTable_T oSymTable;
    int i;
    oSymTable=malloc(sizeof(struct SymTable_T)*SIZE);      /*array 509 thesewn apo pointer se listes*/
    assert(oSymTable);
    for(i=0;i<SIZE;i++) {
        oSymTable[i].head=NULL;        /*arxikopoiw to head kathe array bucket se null*/
    }
    return oSymTable;
}

void SymTable_free(SymTable_T oSymTable){
    Node tmp;
    int i;
    assert(oSymTable);
    for(i=0;i<SIZE;i++) {
        while (oSymTable[i].head){          /*diatrexw kai tis 509 theseis kai apeleutherwnw kathe node ths listas*/
            tmp=oSymTable[i].head;
            free(tmp->temp);
            free(tmp);
            oSymTable[i].head=oSymTable[i].head->next;     
        }
    }
    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    int i;
    unsigned int count=0;
    assert(oSymTable);
    for(i=0;i<SIZE;i++){
        count=count+oSymTable[i].length;
    }
    return count;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
    Node newnode, p, last;
    int count = 0, flag = 0, i;
    unsigned int position,result;
    assert(pcKey);
    assert(oSymTable);
    result=SymTable_hash(pcKey);
    position=result%SIZE;           /*pairnw to mod509 gia na exw apotelesma sto range 0-509*/
    p= oSymTable[position].head;
    last = oSymTable[position].head;
    while (p){
        if (strcmp(p->key, pcKey) == 0){        /*an vrhka to key tote den to ksanavazw sth lista*/
            flag = 1;
        }
        p = p->next;
    }
    if (flag == 0){
        newnode = malloc(sizeof(struct node));       /*an den vrhka to key tote ftiaxnw neo node gia na eisagw ta nea stoixeia*/
        newnode->temp = malloc(sizeof(char));       /*xreiazomai ena temp gia na valw mesa to antigrafo tou pckey*/
        assert(newnode);
        assert(newnode->temp);
        count = strlen(pcKey);           /*antigrafw ena ena ta char tou string sto temp*/
        for (i = 0; i < count; i++) {        /*metraw to mhkos tou pckey epeidh an ekana strcpy sketo to pckey tha antegrafe mono to prwto char tou. emeis theloume OLO to string*/
            strcpy(newnode->temp, pcKey);
        }
        newnode->key = newnode->temp;     /*o logos pou evala to temp san pedio tou struct htan gia na mporesw na to kanw free epeita sth sunarthsh FREE mesw tou osymtable*/
        newnode->value = (void *)pvValue;
        if (oSymTable[position].head == NULL){      /*an to list einai adeio vazw to head na deixnei sto prwto node pou molis mphke*/
            oSymTable[position].head=newnode;
            oSymTable[position].length=1;           /*h lista periexei ena mono stoixeio*/
        }
        else{
            oSymTable->length++;            /*auksanw to mhkos*/
            while (last-> next){      /*alliws proxoraw th lista mexri to telos ths*/
                last = last->next;
            }
            last->next = newnode;       /*kai vazw to pedio next tou teleutaiou komvou ths listas na deixnei sto nenwode*/
        }
        return 1;         /*epistrefw 1 afou mphke kainourgio node*/
    }
    else{
        return 0;         /*epistrefw 0 ama de mphke neo node*/
    }
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    int flag=0;
    unsigned int position,result;
    Node prev,tmp;
    assert(pcKey);
    assert(oSymTable);
    result=SymTable_hash(pcKey);
    position=result%SIZE;
    prev=oSymTable[position].head;
    tmp=oSymTable[position].head;
    while(tmp) {        /*diatrexw olh th lista kai krataw enan pointer sto prohgoumeno node*/
        prev=tmp;       /*etsi wste otan diagrapsw px to deutero node na mporesw na enwsw to prwto node me to trito*/
        if(strcmp(tmp->key,pcKey)==0) {
            flag=1;          /*an to vrhka tote mporw na to diagrapsw alliws den exw ti na diagrapsw*/
            break;
        }       
        tmp=tmp->next;
    }
    if(flag==1) {
        if(tmp==oSymTable[position].head) {      /*an thelw na diagrapsw to head tote allazw to head kai to vazw na deixnei sto epomeno node.*/
            oSymTable[position].head=oSymTable[position].head->next;      /*an den uparxei epomeno tote apla tha deiksei sto null afou to next to head thanai null*/
        }
        else {
            prev->next=tmp->next; /*an svhnw endiameso (h to teleutaio komvo) tote enwnw to prohgoumeno tou me ton epomeno tou*/
        }  
        oSymTable[position].length--;
        return 1;       /*epistrefw 1 se periptwsh diagrafhs*/
    }
    else {  
        return 0;       /*epistrefw 0 an den diegrapsa tipota.*/
    }       /*!!ta free tha ginoun sthn sunarthsh SymTable_free!!*/
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    Node tmp;
    int flag=0;
    unsigned int position,result;
    assert(pcKey);
    assert(oSymTable);
    result=SymTable_hash(pcKey);
    position=result%SIZE;    
    tmp=oSymTable[position].head;
    while(tmp) {        /*diatrexw olh th lista mexri na vrw to key*/
        if(strcmp(tmp->key,pcKey)==0) {
            flag=1;        /*an to vrhka thetw to flag 1*/
        }   
        tmp=tmp->next;
    }
    if(flag==1)return 1;    /*an to vrhka epistrefw 1.*/
    else return 0;        /*alliws 0.*/
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    Node tmp;
    unsigned int position,result;
    assert(pcKey);
    assert(oSymTable);
    result=SymTable_hash(pcKey);
    position=result%SIZE;      
    tmp=oSymTable[position].head;
    while(tmp) {
        if(strcmp(tmp->key,pcKey)==0) {     /*an vrw to key tote epistrefw to value pou antistoixei se auto*/
            return tmp->value;  
        }
        tmp=tmp->next;  /*alliws epistrefw null*/
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    Node tmp;
    int i;
    for(i=0;i<SIZE;i++) {       /*gia kathe bucket*/
        tmp=oSymTable[i].head;
        while(tmp){                 /*gia kathe komvo ths listas efarmozetai h pfapply*/
            pfApply(tmp->key,tmp->value,(void*)pvExtra);
            tmp=tmp->next;          /*xreiazetai cast se void* epeidh to pvextra einai const void**/
        }
    }
    return;
}
