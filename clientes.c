#include "clientes.h"
#include "queue.h"
#include "tree.h"

/* Neste projeto, os clientes foram armazenados, organizados e analisados atraves da estrutura de dados arvore */

typedef long int Key;
#define key(A) (A->ref)
#define less(A, B) (A < B)
#define eq(A, B) (A == B)

/*----------------------Estrutura do tipo ClienteObj que cria um novo cliente-----------------------*/

ClienteObj NEWCLIENTE(long ref, int ntce, int vtce, int ntcb, int vtcb){
    ClienteObj n_cliente;
    n_cliente = (ClienteObj)malloc(sizeof(struct cliente));
    
    n_cliente->ref = ref;
    n_cliente->num_total_cheques_emissor = ntce;
    n_cliente->valor_total_cheques_emissor = vtce;
    n_cliente->num_total_cheques_benificiario = ntcb;
    n_cliente->valor_total_cheques_benificiario = vtcb;
    
    return n_cliente;
}

/************************************************************************************************************/
/*
/*  infocliente: long
/*
/*      Descricao: Esta funcao tem o objetivo de mostrar as informacoes referentes a um determinado cliente
/*                   atraves da referencia recebida por parametro e com a ajuda da funcao TREEfind que procura
/*                   esse mesmo cliente, tais como:
/*                   - Referencia do cliente
/*                   - o numero de cheques em que e emissor
/*                   - o valor total dos cheques em que e emissor
/*                   - o numero de cheques em que e beneficiario
/*                   - o valor total dos cheques em que e beneficiario
/*
/************************************************************************************************************/

void infocliente(long ref){
    ClienteObj n_cliente;
    
    n_cliente = (TREEfind(ref)->item);
    printf("Cliente-info: %ld %d %d %d %d\n", ref, n_cliente->num_total_cheques_emissor, n_cliente->valor_total_cheques_emissor, n_cliente->num_total_cheques_benificiario, n_cliente->valor_total_cheques_benificiario);
}

/************************************************************************************************************/
/*
/*  lista_clientes_ativos: ClienteObj
/*
/*      Descricao: Esta funcao tem o objetivo de mostrar as informacoes referentes a um determinado cliente
/*                   atraves do valor (numero do cliente) recebido como parametro do tipo cliente, tais como:
/*                   - Referencia do cliente
/*                   - o numero de cheques em que e emissor
/*                   - o valor total dos cheques em que e emissor
/*                   - o numero de cheques em que e beneficiario
/*                   - o valor total dos cheques em que e beneficiario
/*
/************************************************************************************************************/

void lista_clientes_ativos(ClienteObj n_cliente){
    printf("*%ld %d %d %d %d\n", n_cliente->ref, n_cliente->num_total_cheques_emissor, n_cliente->valor_total_cheques_emissor, n_cliente->num_total_cheques_benificiario, n_cliente->valor_total_cheques_benificiario);
}
