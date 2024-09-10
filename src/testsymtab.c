#include <stdio.h>
#include "symtable.h"

int main(){
    SymTable_T p;
    int a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9;
    p=SymTable_new();
    printf("Prosthetw 9 komvous:\n");
    SymTable_put(p, "Anna", &a);
    SymTable_put(p, "Makridou", &b);
    SymTable_put(p, "AM", &c);
    SymTable_put(p, "CSD", &d);
    SymTable_put(p, "4934", &e);
    SymTable_put(p, "Computer", &f);
    SymTable_put(p, "Science", &g);
    SymTable_put(p, "Department", &h);
    SymTable_put(p, "UOC", &i);
    printf("Posous komvous exw? %u\n",SymTable_getLength(p));
    printf("Dieuthunsh tou value tou string Anna %p\n",SymTable_get(p,"Anna"));
    printf("Dieuthunsh tou value tou string CSD %p\n",SymTable_get(p,"CSD"));
    printf("Periexei to string Anna? %d\n",SymTable_contains(p,"Anna"));
    printf("Periexei to string csd? %d\n",SymTable_contains(p,"csd"));
    printf("Periexei to string 4934? %d\n",SymTable_contains(p,"4934"));
    printf("Afairw 2 komvous:\n");
    printf("Afairesh komvou Anna %d\n",SymTable_remove(p,"Anna"));
    printf("Afairesh komvou CSD %d\n",SymTable_remove(p,"CSD"));
    printf("Periexei to string Anna? %d\n",SymTable_contains(p,"Anna"));
    printf("Posous komvous exw twra? %u\n",SymTable_getLength(p));
    printf("Prosthetw 4 komvous:\n");
    SymTable_put(p, "New1", &f);
    SymTable_put(p, "New2", &g);
    SymTable_put(p, "New3", &h);
    SymTable_put(p, "New4", &i);
    printf("Posous komvous exw twra? %u\n",SymTable_getLength(p));
    printf("Dieuthunsh tou value tou string New1 %p\n",SymTable_get(p,"New1"));
    printf("Afairesh komvou New1 %d\n",SymTable_remove(p,"New1"));
    printf("Afairesh komvou New2 %d\n",SymTable_remove(p,"New2"));
    printf("Posous komvous exw twra? %u\n",SymTable_getLength(p));
    SymTable_free(p);
    return 0;
}
