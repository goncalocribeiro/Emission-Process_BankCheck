#ifndef ____tree__
#define ____tree__

#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

typedef struct TREEnode* TREElink;
struct TREEnode {
    ClienteObj item;
    TREElink l, r;
    int N;
};

void TREEinit();
TREElink TREEfind(long v); /*AUXILIAR FUNCTION OF TREEsearch*/
int TREEcounter(); /*AUXILIAR FUNCTION OF TREEcount*/
void TREEdeletenode(ClienteObj); /*AUXILIAR FUNCTION OF TREEdelete*/
int TREEheight(TREElink h);
void TREElista(); /*AUXILIAR FUNCTION OF TREEtraverse*/
void TREEaddnode(int valor, long refe, long refb);
void TREEclean(); /*AUXILIAR FUNCTION OF TREEfree*/
TREElink TREEbalance();

#endif /* defined(____tree__) */
