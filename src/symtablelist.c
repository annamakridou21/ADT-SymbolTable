#include "symtable.h"

struct SymTable_T{
    struct node* head;       /*o Symbol Table einai mia kenh domh pou se auth to to arxeio tha einai mia oloklhrh lista*/
    unsigned int length;      /*mia metavlhth length gia na mporw na auksanw kai na meiwnw ton arithmo twn nodes eukola*/
};                          /*giauto periexei enan pointer ton opoion ustera tha valoume na deixnei ston prwto komvo ths lustas*/

struct node {
    char* key;
    char* temp;             /*to temp to xrhsimopoiw gia na apothikeuw to antigrafo to pckey sth put(tha ekshghthei parakatw)*/
    void* value;            /*to struct auto perigrafei ta nodes ths listas pou periexoun to key kai to value. epishs xrhsimopoiw*/
    struct node* next;
};

typedef struct node* Node;       /*sunonymo tou node gia eukolia*/

SymTable_T SymTable_new(void){
    SymTable_T oSymTable;
    oSymTable=malloc(sizeof(struct SymTable_T));       /*desmeuw mnhmh gia th kenh m domh*/
    assert(oSymTable);          
    oSymTable->head=NULL;       /*vazw to head ths listas na deixnei sto null. otan erthei to prwto stoixeio tha deixnei sto neo node*/
    return oSymTable;
}

void SymTable_free(SymTable_T oSymTable){
    Node tmp;
    assert(oSymTable);
    while (oSymTable->head){         /*diatrexw olh th lista kai me th xrhsh vohthitikhs metavlhths svhnw kathe node*/
        tmp=oSymTable->head;          /*krataw sto temp to kathe komvo giati an ton kanw kateutheian free pws tha exw prosvash sto next tou?*/
        free(tmp->temp);
        free(tmp);                   /*mporw na grapsw free tmp epeidh exei thn idia dieuthunsh me to osymtable pou ekana malloc*/ 
        oSymTable->head=oSymTable->head->next;    /*proxwraw parakatw*/
    }
    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable);      
    return oSymTable->length;       /*epistrefw th vohthitikh metavlhth length pou upologizetai se kathe put*/
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
    Node newnode,p,last;
    int count=0,flag=0,i;
    assert(pcKey);
    assert(oSymTable);
    p=oSymTable->head;          /*vohthitikes metavlhtes gia parakatw*/
    last=oSymTable->head;
    while(p) {
        if(strcmp(p->key,pcKey)==0) {       /*an vrhka to key tote den to ksanavazw sth lista*/
            flag=1;
        }   
        p=p->next;
    }
    if(flag==0) {              /*an den vrhka to key tote ftiaxnw neo node gia na eisagw ta nea stoixeia*/
        newnode=malloc(sizeof(struct node));
        newnode->temp=malloc(sizeof(char));         /*xreiazomai ena temp gia na valw mesa to antigrafo tou pckey*/
        assert(newnode);
        assert(newnode->temp);
        count=strlen(pcKey);        /*metraw to mhkos tou pckey epeidh an ekana strcpy sketo to pckey tha antegrafe mono to prwto char tou. emeis theloume OLO to string*/
        for(i=0;i<count;i++){
            strcpy(newnode->temp,pcKey);        /*antigrafw ena ena ta char tou string sto temp*/
        }
        newnode->key=newnode->temp;         /*o logos pou evala to temp san pedio tou struct htan gia na mporesw na to kanw free epeita sth sunarthsh FREE mesw tou osymtable*/
        newnode->value=(void*)pvValue;        /*-prin th lhksh tou programmatos. ama ekana edw to free tote tha xanotan h timh pou tha hthela na valw sto node.*/
        if(oSymTable->head==NULL){
            oSymTable->head=newnode;        /*an to list einai adeio vazw to head na deixnei sto prwto node pou molis mphke*/
            oSymTable->length=1;             /*h lista periexei ena mono stoixeio*/
        }
        else {
            oSymTable->length++;            /*auksanw to mhkos*/
            while(last->next) {    /*alliws proxoraw th lista mexri to telos ths*/
                last=last->next;
            }
            last->next=newnode;     /*kai vazw to pedio next tou teleutaiou komvou ths listas na deixnei sto nenwode*/
        }
        return 1;       /*epistrefw 1 afou mphke kainourgio node*/
    }
    else {
        return 0;       /*epistrefw 0 ama de mphke neo node*/
    }
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    int flag=0;
    Node prev,tmp;
    assert(pcKey);
    assert(oSymTable);
    prev=oSymTable->head;
    tmp=oSymTable->head;
    while(tmp) {        /*diatrexw olh th lista kai krataw enan pointer sto prohgoumeno node*/
        prev=tmp;       /*etsi wste otan diagrapsw px to deutero node na mporesw na enwsw to prwto node me to trito*/
        if(strcmp(tmp->key,pcKey)==0) {
            flag=1;          /*an to vrhka tote mporw na to diagrapsw alliws den exw ti na diagrapsw*/
            break;
        }       
        tmp=tmp->next;
    }
    if(flag==1) {
        if(tmp==oSymTable->head) {      /*an thelw na diagrapsw to head tote allazw to head kai to vazw na deixnei sto epomeno node.*/
            oSymTable->head=oSymTable->head->next;      /*an den uparxei epomeno tote apla tha deiksei sto null afou to next to head thanai null*/
        }
        else {
            prev->next=tmp->next; /*an svhnw endiameso (h to teleutaio komvo) tote enwnw to prohgoumeno tou me ton epomeno tou*/
        }  
        oSymTable->length--;      /*to mhkos ths listas meiwnetai*/
        return 1;       /*epistrefw 1 se periptwsh diagrafhs*/
    }
    else {  
        return 0;       /*epistrefw 0 an den diegrapsa tipota.*/
    }       /*!!ta free tha ginoun sthn sunarthsh SymTable_free!!*/
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    Node tmp;
    int flag=0;
    assert(pcKey);
    assert(oSymTable);
    tmp=oSymTable->head;
    while(tmp) {        /*diatrexw olh th lista mexri na vrw to key*/
        if(strcmp(tmp->key,pcKey)==0) {
            flag=1;        /*an to vrhka thetw to flag 1*/
        }   
        tmp=tmp->next;
    }
    if(flag==1) return 1;      /*an to vrhka epistrefw 1.*/
    else return 0;      /*alliws 0.*/
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    Node tmp;
    assert(pcKey);
    assert(oSymTable);
    tmp=oSymTable->head;
    while(tmp) {    
        if(strcmp(tmp->key,pcKey)==0) {     /*an vrw to key tote epistrefw to value pou antistoixei se auto*/
            return tmp->value;
        }
        tmp=tmp->next;
    }
    return NULL;        /*alliws epistrefw null*/
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    Node tmp;
    tmp=oSymTable->head;
    while(tmp){     /*gia kathe komvo ths listas efarmozetai h pfapply*/
        pfApply(tmp->key,tmp->value,(void*)pvExtra);        /*xreiazetai cast se void* epeidh to pvextra einai const void**/
        tmp=tmp->next;
    }
    return;
}
