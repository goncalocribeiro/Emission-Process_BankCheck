#include <stdlib.h>

#include "tree.h"
#include "clientes.h"

static TREElink TREEhead;

#define less(A, B) (A < B)
#define eq(A, B) (A == B)

void TREEinit(){
    TREEhead = NULL;
}

TREElink NEWTREE(ClienteObj item, TREElink l, TREElink r, int N){
    /*Cria um novo no na arvore*/
    TREElink x = (TREElink)malloc(sizeof(struct TREEnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
    
    return x;
}

/********************************************************************************************************/
/*
 /*  TREEsearch: TREElink x long -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de procurar um elemento especifico na arvore de clientes
 /*                 atraves da referencia desse mesmo cliente
 /*
 /*******************************************************************************************************/

TREElink TREEsearch(TREElink h, long v){
    if (h == NULL)
        return NULL;
    
    if (eq(v, h->item->ref))
        return h;
    
    if (less(v, h->item->ref))
        return TREEsearch(h->l, v);
    else
        return TREEsearch(h->r, v);
}

TREElink TREEfind(long v){
    return TREEsearch(TREEhead, v);
}

/***********************************************************************************************/
/*
 /*  TREEinsert: TREElink, ClienteObj -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de inserir um novo cliente na arvore de clientes.
 /*
 /***********************************************************************************************/

TREElink TREEinsert(TREElink h, ClienteObj item){
    if (h == NULL)
        return NEWTREE(item, NULL, NULL, 0);
    
    if (less(item->ref, h->item->ref))
        h->l = TREEinsert(h->l, item);
    else
        h->r = TREEinsert(h->r, item);
    
    TREEhead = TREEbalance();
    return h;
}

/*********************************************************************************************************************/
/*
 /*  TREEcount: TREElink -> int
 /*
 /*      Descricao: Esta funcao tem o objetivo de contar e devolver o numero de clientes ou nos, existentes na arvore
 /*
 /********************************************************************************************************************/

int TREEcount(TREElink h){
    if (h==NULL)
        return 0;
    else
        return TREEcount(h->r) + TREEcount(h->l) + 1;
}

int TREEcounter(){
    return TREEcount(TREEhead);
}

TREElink rotL(TREElink h)
{
    int height_left, height_right;
    TREElink x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = TREEheight(h->l);
    height_right = TREEheight(h->r);
    h->N = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = TREEheight(x->l);
    height_right = TREEheight(x->r);
    x->N = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

TREElink rotR(TREElink h)
{
    int height_left, height_right;
    TREElink x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = TREEheight(h->l);
    height_right = TREEheight(h->r);
    h->N = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = TREEheight(x->l);
    height_right = TREEheight(x->r);
    x->N = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

/********************************************************************************************************/
/*
 /*  rotLR: TREElink -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de realizar uma rotacao dupla da esquerda para a direita
 /*
 /********************************************************************************************************/

TREElink rotLR(TREElink h){
    if (h==NULL) return h;
    h->l = rotL(h->l);
    return rotR(h);
}

/********************************************************************************************************/
/*
 /*  rotRL: TREElink -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de realizar uma rotacao dupla da direita para a esquerda
 /*
 /********************************************************************************************************/

TREElink rotRL(TREElink h){
    if (h==NULL) return h;
    h->r = rotR(h->r);
    return rotL(h);
}

/********************************************************************************************************/
/*
 /*  rotLR: TREElink -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de realizar um balanço a arvore
 /*
 /********************************************************************************************************/

int Balance(TREElink h) {
    if(h == NULL)
        return 0;
    return TREEheight(h->l) - TREEheight(h->r);
}

TREElink partR(TREElink h, int k){
    int t = h->l->N;
    
    if(t>k){
        h->l = partR(h->l, k);
        h = rotR(h);
    }
    
    if(t<k){
        h->r = partR(h->r, k-t-1);
        h = rotL(h);
    }
    return h;
}

TREElink joinLR(TREElink a, TREElink b){
    if(b == NULL)
        return a;
    b = partR(b, 0);
    b->l = a;
    
    return b;
}

/********************************************************************************************************/
/*
 /*  TREEmax: TREElink -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de procurar e devolver o maior elemento da arvore de clientes
 /*
 /********************************************************************************************************/

TREElink TREEmax(TREElink h){
    if (h==NULL || h->r==NULL){
        return h;
    } else {
        return TREEmax(h->r);
    }
}

/********************************************************************************************************/
/*
 /*  TREEdelete: TREElink, ClienteObj -> TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de eliminar um cliente ou no da arvore de clientes.
 /*
 /********************************************************************************************************/

TREElink TREEdelete(TREElink h, ClienteObj v){
    
    if(h==NULL)
        return NULL;
    else if(less(v->ref, h->item->ref))
        h->l = TREEdelete(h->l, v);
    else if(less(h->item->ref, v->ref))
        h->r = TREEdelete(h->r, v);
    else {
        if (h->l !=NULL && h->r !=NULL){
            TREElink aux = TREEmax(h->l);
            
            { /*As chavetas permitem declarar variaveis a meio da funcao*/
                ClienteObj x;
                x=h->item;
                h->item=aux->item;
                aux->item=x;
            }
            
            h->l= TREEdelete(h->l, aux->item);
        }
        else {
            TREElink aux=h;
            if ( h->l == NULL && h->r == NULL )
                h=NULL;
            else if (h->l==NULL)
                h=h->r;
            else
                h=h->l;
            free(aux->item);
            free(aux);
        }
    }
    
    TREEhead = TREEbalance();
    return h;
}

void TREEdeletenode(ClienteObj v){
    TREEhead = TREEdelete(TREEhead, v);
}

int TREEheight(TREElink h){
    if(h==NULL)
        return 0;
    return h->N;
}

void TREEvisit(ClienteObj n_cliente){
    printf("%ld\n", n_cliente->ref);
}

/********************************************************************************************************/
/*
 /*  TREEtraverse: TREElink
 /*
 /*      Descricao: Esta funcao tem o objetivo de imprimir todos os dados relativos ao cliente em questao.
 /*
 /********************************************************************************************************/

void TREEtraverse(TREElink h){
    /*Utilizada para imprimir informacoes de todos os clientes*/
    if(h==NULL){
        return;
    }
    TREEtraverse(h->l);
    lista_clientes_ativos(h->item);
    TREEtraverse(h->r);
}

void TREElista(){
    TREEtraverse(TREEhead);
}

void TREEaddnode(int valor, long refe, long refb){
    /*Insere um novo no na arvore*/
    ClienteObj emissor, benificiario;
    
    if (TREEfind(refe) != NULL) {
        emissor = (TREEfind(refe)->item);
        emissor->valor_total_cheques_emissor += valor;
        emissor->num_total_cheques_emissor += 1;
    } else {
        TREEhead = TREEinsert(TREEhead, NEWCLIENTE(refe, 1, valor, 0, 0));
    }
    
    if (TREEfind(refb) != NULL) {
        benificiario = (TREEfind(refb)->item);
        benificiario->valor_total_cheques_benificiario += valor;
        benificiario->num_total_cheques_benificiario += 1;
    } else {
        TREEhead = TREEinsert(TREEhead, NEWCLIENTE(refb, 0, 0, 1, valor));
    }
}

TREElink TREEfree(TREElink h){
    /*Liberta a memoria da arvore para terminar o programa*/
    if (h==NULL)
        return h;
    h->l=TREEfree(h->l);
    h->r=TREEfree(h->r);
    
    return TREEdelete(h, h->item);
}

void TREEclean(){
    TREEhead = TREEfree(TREEhead);
}

TREElink TREEbalance(){
    /*Funcao que permite balancear a arvore quando se insere ou elimina um no*/
    int balanceFactor;
    
    if(TREEhead==NULL)
        return TREEhead;
    
    balanceFactor = Balance(TREEhead);
    if (balanceFactor>1){
        if (Balance(TREEhead->l)>0)
            TREEhead=rotR(TREEhead);
        else
            TREEhead=rotLR(TREEhead);
    } else if (balanceFactor<-1){
        if (Balance(TREEhead->r)<0)
            TREEhead=rotL(TREEhead);
        else
            TREEhead=rotRL(TREEhead);
    } else {
        int height_left = TREEheight(TREEhead->l);
        int height_right = TREEheight(TREEhead->r);
        TREEhead->N = height_left > height_right ? height_left+1 : height_right+1;
    }
    
    return TREEhead;
}
