#ifndef ____queue__
#define ____queue__

#include <stdio.h>
#include <stdlib.h>
#include "cheques.h"

typedef struct QUEUEnode* link;

struct QUEUEnode{
    ChequeObj item;
    link next;
};

void QUEUEinit();
void QUEUEput(ChequeObj);
ChequeObj QUEUEget();
ChequeObj QUEUEsearch(long ref);
int QUEUEsize();
int QUEUEvalor();
ChequeObj QUEUEfind(long);
void QUEUEfree();

#endif /* defined(____queue__) */
