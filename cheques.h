#ifndef ____cheques__
#define ____cheques__

#include <stdio.h>
#include <stdlib.h>

struct cheque{
    long refc, refe, refb;
    int valor; /* O atributo processado pode ter o valor 0 ou 1 em que 0 indica que o cheque ainda nao esta processado e 1 indica que ja se encontra processado*/
};

typedef struct cheque* ChequeObj;

void adiciona_cheque_por_processar(int valor, long refe, long refb, long refc);
void processa();
void processaR(long);
void infocheque(long);

#endif /* defined(____cheques__) */
