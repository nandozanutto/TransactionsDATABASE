#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "transacao.h"
#include "testeConflito.h"
#include "graph.h"


void testSeriab(apontAgen agendamento, Graph grafo){
    for(int j=0; j<agendamento->tam; j++){
        for(apontTrans transacaoTj=agendamento->vetTransacao[j]; transacaoTj!=NULL; transacaoTj=transacaoTj->next){
            if(transacaoTj->op == 'R'){
                for(int i=0; i<agendamento->tam; i++){//varre as transações a procura de um write 
                    if(i==j) continue;//se Ti está comparando com Ti
                    for(apontTrans transacaoTi=agendamento->vetTransacao[i]; transacaoTi!=NULL; transacaoTi=transacaoTi->next){
                        if((transacaoTi->op=='W') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            // printf("Aresta R,W em %d(%d) -> %d(%d)\n", transacaoTi->id, i,  transacaoTj->id, j);
                            GRAPHinsertArc(grafo, i, j);
                    }
                }
            }else if(transacaoTj->op == 'W'){
                for(int i=0; i<agendamento->tam; i++){//varre as transações a procura de um write 
                    if(i==j) continue;//se Ti está comparando com Ti
                    for(apontTrans transacaoTi=agendamento->vetTransacao[i]; transacaoTi!=NULL; transacaoTi=transacaoTi->next){
                        if((transacaoTi->op=='R') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            // printf("Aresta R,W em %d(%d) -> %d(%d)\n", transacaoTi->id, i,  transacaoTj->id, j);
                            GRAPHinsertArc(grafo, i, j);
                        if((transacaoTi->op=='W') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            // printf("Aresta R,W em %d(%d) -> %d(%d)\n", transacaoTi->id, i,  transacaoTj->id, j);
                            GRAPHinsertArc(grafo, i, j);
                    }
                }
            }
        }
    }
}
