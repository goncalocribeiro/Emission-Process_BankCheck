/*#####################################################################################
/*#                         PROJETO 2 - IAED (2014-2015) - LEIC IST                   #
/*#                                                                                   #
/*#         Turno: Terca-feira, 08h00                                                 #
/*#         Grupo: Al049                                                              #
/*#                                                                                   #
/*#         Elementos do grupo:                                                       #
/*#         Goncalo Ribeiro - 82303                                                   #
/*#         Andre Mendonca - 82304                                                    #
/*#         Joao Pestana - 79515                                                      #
/*#                                                                                   #
/*#####################################################################################
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "cheques.h"
#include "queue.h"
#include "tree.h"

int main(){
    char command[12];
    int valor; /*Valor do cheque*/
    long ref, refe, refb, refc; /*Referencia emissor, referencia benificario, referencia cheque*/
    QUEUEinit();
    TREEinit();
    
    while(1){
        scanf("%s",command);
        if(strcmp(command,"cheque")==0) /*Adicionar novo cheque aos cheques por processar*/
        {
            scanf("%d%ld%ld%ld", &valor, &refe, &refb, &refc);
            adiciona_cheque_por_processar(valor, refe, refb, refc);
            TREEaddnode(valor, refe, refb);
        }
        else if(strcmp(command,"processa")==0) /*Processar o cheque mais antigo*/
        {
            processa();
        }
        else if(strcmp(command,"processaR")==0) /*Processar um cheque especifico*/
        {
            scanf("%ld", &refc);
            processaR(refc);
        }
        else if(strcmp(command,"infocheque")==0) /*Mostrar informacao de um cheque*/
        {
            scanf("%ld", &refc);
            infocheque(refc);
        }
        else if(strcmp(command,"infocliente")==0) /*Mostrar informacao de um cliente*/
        {
            scanf("%ld", &ref);
            infocliente(ref);
        }
        else if(strcmp(command,"info")==0) /*Mostra as informacoes dos clientes ativos*/
        {
            if (TREEcounter() == 0)
                printf("No active clients\n");
            else
                TREElista();
        }
        else if(strcmp(command,"sair")==0) /*Sair do programa*/			{
            printf("%d %d %d\n", TREEcounter(), QUEUEsize(), QUEUEvalor());
            QUEUEfree();
            TREEclean();
            return EXIT_SUCCESS;
        }
        getchar();
    }
    return EXIT_FAILURE;
}
