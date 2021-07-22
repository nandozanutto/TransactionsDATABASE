#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h" 
#include "stack.h"
#include "transacao.h"
#include "visaoEq.h"

apontTrans ultimaEscrita(apontAgen agendamento){
    //retorna uma lista com as ultimas escritas de cada atributo
    apontTrans historico = (apontTrans) malloc(sizeof(struct Transactions));
    historico->next = NULL;//cabeça
    historico->attri = -1;
    historico->id = -1;
    int atualizou=0;


    for(apontTrans transacao = agendamento->vetTransacao[0]; transacao!=NULL; transacao=transacao->next){
        if(transacao->op == 'W'){//escrita encontrada
            // necessario checar se ja existe escrita no mesmo atributo
            for(apontTrans aux=historico; aux!=NULL; aux=aux->next){
                if(aux->attri == transacao->attri){
                    aux->id = transacao->id;//atualiza id
                    atualizou = 1;
                }
            }
            if(!atualizou){//se não foi encontrada escrita anterior
                apontTrans aux2 = historico;
                while(aux2->next != NULL)
                    aux2 = aux2->next;//pega final do historico
                aux2->next = (apontTrans) malloc(sizeof(struct Transactions));
                aux2->next->attri = transacao->attri;
                aux2->next->id = transacao->id;
                aux2->next->next = NULL;
            }
            atualizou=0;
        }
    }
    return historico;

}

apontDepen leituraEscrita(apontAgen agendamento){
    //retorna uma lista de r -> w onde r vem antes de w (no mesmo atributo por diferentes transações)
    apontDepen dependencia = (apontDepen) malloc(sizeof(struct Dependency));
    dependencia->next = NULL;
    dependencia->read = -1;
    dependencia->write = -1;

    for(apontTrans transacao = agendamento->vetTransacao[0]; transacao!=NULL; transacao=transacao->next){
        if(transacao->op == 'R'){
            for(apontTrans procuraW = transacao; procuraW != NULL; procuraW = procuraW->next)
                if((procuraW->op == 'W') && (procuraW->attri==transacao->attri) && (procuraW->id!=transacao->id)){
                    apontDepen aux = dependencia;
                    while(aux->next != NULL)
                        aux = aux->next;//pega final da dependencia
                    aux->next = (apontDepen)malloc(sizeof(struct Dependency));
                    aux->next->read = transacao->time;
                    aux->next->write = procuraW->time;
                    aux->next->next = NULL;
                }
                    

        }

    }
    return dependencia;

}

int comparaDependencia(apontDepen dependencia1, apontDepen dependencia2){
    //as dependencias podem estar em ordem diferente
    int existeDepen = 0;
    for(apontDepen a=dependencia1; a!=NULL; a=a->next){
        for(apontDepen b=dependencia2; b!=NULL; b=b->next)
            if(a->read == b->read && a->write == b->write)
                existeDepen = 1;
        if(existeDepen == 0)
            return 0;//nao encontrou a mesma relação leitura-escrita
        existeDepen = 0;
    }

    return 1;
}

int comparaHistory(apontTrans historico1, apontTrans historico2){
    int mesmoHistorico = 0;
    for(apontTrans a=historico1; a!=NULL; a=a->next){
        for(apontTrans b=historico2; b!=NULL; b=b->next){
            if(a->attri==b->attri && a->id==b->id)
                mesmoHistorico=1;
        }
        if(mesmoHistorico==0)
            return 0;//a última escrita de algum atributo nao bateu!
        mesmoHistorico = 0;
    }

    return 1;
}

apontAgen transforma(apontAgen agendamento){
//esta função muda o agendamento da posição vertical para a horizontal
    apontAgen newAgendamento = criaAgendamento();
    for(int i=0; i<agendamento->tam; i++){
        for(apontTrans j=agendamento->vetTransacao[i]; j!=NULL; j=j->next){       
            appendTransacao(newAgendamento, j->time, j->id, j->op, j->attri);
            // printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
        
        }
    }

    return newAgendamento;

}
/* Function to swap values at two pointers */
void swap(apontAgen agendamento, int i, int j)
{
    apontTrans aux = agendamento->vetTransacao[i];
    agendamento->vetTransacao[i] = agendamento->vetTransacao[j];
    agendamento->vetTransacao[j] = aux;
}
 

