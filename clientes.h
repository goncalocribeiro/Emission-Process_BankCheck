#ifndef ____clientes__
#define ____clientes__

#include <stdio.h> 

struct cliente{
    long ref;
    int num_total_cheques_emissor, valor_total_cheques_emissor, num_total_cheques_benificiario, valor_total_cheques_benificiario;
};

typedef struct cliente* ClienteObj;

ClienteObj NEWCLIENTE(long ref, int ntce, int vtce, int ntcb, int vtcb);
void infocliente(long);
void lista_clientes_ativos(ClienteObj n_cliente);

#endif /* defined(____clientes__) */
