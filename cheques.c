#include "cheques.h"
#include "queue.h"
#include "tree.h"

/* Neste projeto, os cheques foram armazenados, processados e analisados atraves de uma estrutura de dados FIFO (First in, First out), ou seja, uma fila de espera */

/***********************************************************************************************/
/*
/*  adiciona_cheque_por_processar: int x long x long x long
/*
/*      Descricao: Esta funcao tem o objetivo de adicionar um novo cheque a fila de cheques
/*                 recebendo como parametro o valor do cheque, a referencia do cliente emissor
/*                 do cheque, a referencia do cliente beneficiario do cheque e a referencia do
/*                 cheque em questao. E criado um novo objeto do tipo cheque e tendo em conta 
/*                 a memoria insere-se o cheque na fila dos cheques.
/*
/***********************************************************************************************/

void adiciona_cheque_por_processar(int valor, long refe, long refb, long refc){
    
    ChequeObj n_cheque; /*Cria um objeto cheque*/
    n_cheque = (ChequeObj)malloc(sizeof(struct cheque));
    
    n_cheque->valor = valor;
    n_cheque->refe = refe;
    n_cheque->refb = refb;
    n_cheque->refc = refc;
    
    QUEUEput(n_cheque); /*Insere-se um novo cheque na queue dos cheques*/
}

/***********************************************************************************************/
/*
/*  processa:
/*
/*      Descricao: Esta funcao tem o objetivo de processar o cheque que esta a mais tempo na
/*                 queue (fila dos cheques), ou seja, esta funcao processa o cheque que esta
/*                 no topo da fila, para que isso aconteca, e feita uma verificacao a fila,
/*                 que verifica se existe ou nao algum cheque na fila, caso nao exista o
/*                 programa mostra ao utilizador uma mensagem, caso exista pelo menos um cheque
/*                 na fila, as caracteristicas do cheque (valor do cheque, numero de cheque...)
/*                 sao relacionadas aos clientes atraves da referencias dos clientes emissores e
/*                 beneficiarios.
/*
/***********************************************************************************************/

void processa(){
    
    ClienteObj emissor, benificiario;
    ChequeObj n_cheque;
    int valor;
    long refe_aux, refb_aux;
    
    n_cheque = QUEUEget();
    
    if(n_cheque != NULL){
        valor = n_cheque->valor;
        refe_aux = n_cheque->refe;
        refb_aux = n_cheque->refb;
        
        emissor = (TREEfind(refe_aux)->item);
        benificiario = (TREEfind(refb_aux)->item);
    
        emissor->valor_total_cheques_emissor -= valor;
        emissor->num_total_cheques_emissor -= 1;
        benificiario->valor_total_cheques_benificiario -= valor;
        benificiario->num_total_cheques_benificiario -= 1;
        
        if (((emissor->num_total_cheques_emissor) == 0) && ((emissor->num_total_cheques_benificiario) == 0))
            TREEdeletenode(emissor);
        
        if (((benificiario->num_total_cheques_emissor) == 0) && ((benificiario->num_total_cheques_benificiario) == 0))
            TREEdeletenode(benificiario);
    } else {
        printf("Nothing to process\n");
    }
}

/************************************************************************************************************/
/*
/*  processaR: long
/*
/*      Descricao: Esta funcao tem o objetivo de processar um cheque identificado pelo utilizador
/*                   atraves da indicacao da referencia do cheque que se deseja processar, para isso,
/*                   e necessario utilizar a funcao QUEUEsearch (enviando a referencia por parametro),
/*                   para encontrar o cheque que contem a referencia indicada pelo utilizador, apos a
/*                   a procura do cheque, e feito uma verificacao a fila de cheques, que verifica se o cheque
/*                   com essa referencia existe ou nao, caso nao exista o programa mostra ao utilizador uma
/*                   mensagem, caso esse cheque exista na fila as caracteristicas do cheque (valor do cheque,
/*                   numero de cheque...) sao relacionadas aos clientes atraves da referencias dos clientes
/*                   emissores e beneficiarios.
/*
/************************************************************************************************************/

void processaR(long refc){
    
    ClienteObj emissor, benificiario;
    ChequeObj n_cheque;
    int valor;
    long refe_aux, refb_aux;
    
    n_cheque = QUEUEsearch(refc);
    
    if(n_cheque != NULL){
        valor = n_cheque->valor;
        refe_aux = n_cheque->refe;
        refb_aux = n_cheque->refb;
        
        emissor = (TREEfind(refe_aux)->item);
        benificiario = (TREEfind(refb_aux)->item);
        
        emissor->valor_total_cheques_emissor -= valor;
        emissor->num_total_cheques_emissor -= 1;
        benificiario->valor_total_cheques_benificiario -= valor;
        benificiario->num_total_cheques_benificiario -= 1;
        
        if (((emissor->num_total_cheques_emissor) == 0) && ((emissor->num_total_cheques_benificiario) == 0))
            TREEdeletenode(emissor);
        
        if (((benificiario->num_total_cheques_emissor) == 0) && ((benificiario->num_total_cheques_benificiario) == 0))
            TREEdeletenode(benificiario);
    } else {
        printf("Cheque %ld does not exist\n", refc);
    }
}

/************************************************************************************************************/
/*
/*  infocheque: long
/*
/*      Descricao: Esta funcao tem o objetivo de mostrar as informacoes referentes a um cheque especifico 
/*                   atraves da referencia recebida por parametro, tais como:
/*                   - referencia do cheque
/*                   - valor do cheque
/*                   - referencia do cliente emissor
/*                   - referencia do cliente beneficiario
/*
/************************************************************************************************************/

void infocheque(long refc){
    
    ChequeObj n_cheque;
    
    n_cheque = QUEUEfind(refc);
    printf("Cheque-info: %ld %d %ld --> %ld\n", n_cheque->refc, n_cheque->valor, n_cheque->refe, n_cheque->refb);
}
