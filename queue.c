#include <stdlib.h>

#include "queue.h"
#include "cheques.h"

#define less(A, B) (A < B)
#define eq(A, B) (A == B)

static link QUEUEhead, QUEUEtail;

/***********************************************************************************************/
/*
/*  QUEUEinit:
/*
/*      Descricao: Esta funcao tem o objetivo iniciar a head (topo da fila) e a tail (fim da fila)
/*                 a NULL, para que assim a fila de cheques esteja vazia quando se iniciar.
/*
/***********************************************************************************************/

void QUEUEinit(){
    /*Inicia-se a head e a tail a NULL*/
    QUEUEhead = NULL;
    QUEUEtail = NULL;
}

/***********************************************************************************************/
/*
/*  QUEUEempty: -> int
/*
/*      Descricao: Esta funcao tem o objetivo verificar se a fila de cheques esta vazia, atraves
/*                 da verificacao da existencia do valor NULL na head da fila, pois sabendo que a
/*                 se encontra a NULL, sabemos que a fila esta vazia decerteza.
/*
/***********************************************************************************************/

int QUEUEempty(){
    /*Verifica se a QUEUE esta vazia*/
    return QUEUEhead == NULL;
}

/*********************************************************************************************************/
/*
/*  NEWQUEUE: ChequeObj x link -> link
/*
/*      Descricao: Esta funcao tem o objetivo de criar e alocar devidamente um novo elemento na fila
/*                 recebendo por parametro as caracteristicas de um cheque e aponta para o proximo cheque
/*
/********************************************************************************************************/

link NEWQUEUE(ChequeObj item, link next){
    link x = (link) malloc(sizeof(struct QUEUEnode));
    
    x->item = item;
    x->next = next;
    return x;
}

/*********************************************************************************************************/
/*
/*  QUEUEput: ChequeObj
/*
/*      Descricao: Esta funcao tem o objetivo de inserir um novo elemento na fila de cheques, executando
/*                 a verificacao da existencia do valor NULL da head, conseguindo assim inserir um novo
/*                 novo cheque atraves dos valor do cheque recebido por parametro
/*
/********************************************************************************************************/

void QUEUEput(ChequeObj item){
    if (QUEUEhead == NULL){
        QUEUEtail = NEWQUEUE(item, QUEUEhead);
        QUEUEhead = QUEUEtail;
        return;
    }
    
    QUEUEtail->next = NEWQUEUE(item, QUEUEtail->next); /*Nos outros casos insere-se no fim da fila*/
    QUEUEtail = QUEUEtail->next; /*Atualiza-se a tail*/
}

/*****************************************************************************************************************************************/
/*
 /*  QUEUEget: -> ChequeObj
 /*
 /*      Descricao: Esta funcao tem o objetivo de retornar o elemento (cheque) que foi inserido a mais tempo na fila de cheques (QUEUE),
 /*                 caso a fila de cheques esteja vazia a funcao retorna NULL.
 /*
 /****************************************************************************************************************************************/

ChequeObj QUEUEget(){
    if(QUEUEempty()){
        return NULL;
    } else {
        ChequeObj item = QUEUEhead->item; /*Guarda-se o primeiro elemento numa variavel auxiliar*/
        link t = QUEUEhead->next;
        free(QUEUEhead); /*Liberta-se a memoria*/
        QUEUEhead = t; /*Atualiza-se a head da fila com o elemento seguinte*/
        return item; /*Retorna-se o elemento*/
    }
}

/*********************************************************************************************************/
/*
 /*  QUEUEsearch: long -> ChequeObj
 /*
 /*      Descricao: Esta funcao tem o objetivo de procurar um cheque (caso exista) na fila de cheques (QUEUE)
 /*                 atraves da referencia recebida por parametro (referencia de um cheque) e por fim retorna
 /*                 NULL caso esse cheque nao exista na fila e retorna o numero do cheque caso contrario.
 /*
 /********************************************************************************************************/

ChequeObj QUEUEsearch(long ref){
    link aux, x;
    ChequeObj n_cheque;
    
    if(QUEUEempty())
        return NULL;
    if (eq(ref, QUEUEhead->item->refc))
        return QUEUEget();
        
    for(x=QUEUEhead; x->next!=NULL; x=x->next){
        if (eq(ref, x->next->item->refc)){
            if (x->next->next==NULL)
                QUEUEtail = x;
            aux = x->next;
            n_cheque = aux->item;
            x->next = aux->next;
            free(aux);
            return n_cheque;
        }
    }
    
    return NULL;
}

/*********************************************************************************************************/
/*
 /*  QUEUEfind: long -> ChequeObj
 /*
 /*      Descricao: Esta funcao tem o objetivo de procurar um cheque (caso exista) na fila de cheques (QUEUE)
 /*                 atraves da referencia recebida por parametro (referencia de um cheque) e por fim retorna
 /*                 NULL caso esse cheque nao exista na fila e retorna o numero do cheque caso contrario
 /*                 mas com a particularidade de ser mais ser feita uma procura mais simples e sem remocao de memoria
 /*
 /********************************************************************************************************/

ChequeObj QUEUEfind(long ref){
    /*Procura um cheque que esta na QUEUE com a referencia ref recebida por parametro de uma forma mais simples, sem remover memoria*/
    link n_cheque;
    for(n_cheque=QUEUEhead; n_cheque!=NULL; n_cheque=n_cheque->next){
        if(eq(ref, n_cheque->item->refc))
            return n_cheque->item;
    }
    
    return NULL;
}

/*******************************************************************************************************************/
/*
 /*  QUEUEsize: -> int
 /*
 /*      Descricao: Esta funcao tem o objetivo de devolver o numero de cheques existentes na QUEUE (fila de cheques),
 /*                   percorrendo a lista de cheques com um while.
 /*******************************************************************************************************************/

int QUEUEsize(){
    int n=0;
    if(QUEUEempty()){
        return 0;
    } else {
        link t = QUEUEhead;
        while(t != NULL){
            n++;
            t = t->next;
        }
        return n;
    }
}

/**************************************************************************************************************************************/
/*
 /*  QUEUEvalor: -> int
 /*
 /*      Descricao: Esta funcao tem o objetivo de devolver o valor total em dinheiro dos cheques existentes na QUEUE (fila de cheques),
 /*                 percorrendo a lista de cheques com um while.
 /*************************************************************************************************************************************/


int QUEUEvalor(){
    int n=0;
    if(QUEUEempty()){
        return 0;
    } else {
        link t = QUEUEhead;
        while(t != NULL){
            n += t->item->valor;
            t = t->next;
        }
        return n;
    }
}

/*********************************************************************************************************/
/*
 /*  QUEUEfree:
 /*
 /*      Descricao: Esta funcao tem o objetivo de libertar a memoria relativa a QUEUE (fila de cheques)
 /*                 quando se sai do programa, para poupar o processador
 /********************************************************************************************************/

void QUEUEfree(){
    if(QUEUEhead == NULL){
        free(QUEUEhead);
        return;
    }
    QUEUEget();
    QUEUEfree();
}
