#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "transacao.h"

apontAgen criaAgendamento(){
    apontAgen agendamento = (apontAgen) malloc(sizeof(struct Agendamento));
    agendamento->tam = 0;
    agendamento->vetTransacao=NULL;
    return agendamento;
}
int retornaPos(apontAgen agendamento, char id){
    //retorna -1 se não há nenhuma transação com o mesmo id. Caso contrário retorna a pos
    //da transição com o mesmo id
    for(int i=0; i<agendamento->tam; i++)
        if(agendamento->vetTransacao[i]->id == id)
            return i;
    return -1;
}

void criaTransacao(apontAgen agendamento, int time, int id, char op, char attri){
    apontTrans transacao = (apontTrans) malloc(sizeof(struct Transactions));
    transacao->attri = attri;
    transacao->op = op;
    transacao->id = id;
    transacao->time = time;
    transacao->next = NULL;
    
    int pos = retornaPos(agendamento, id);
    if(pos!=-1){
        apontTrans aux = agendamento->vetTransacao[pos];
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = (apontTrans) transacao;
    }else{//nenhuma transação com o mesmo id
        agendamento->vetTransacao = (apontTrans *) realloc(agendamento->vetTransacao, sizeof(apontTrans)*(agendamento->tam+1));//aumenta vetor
        agendamento->vetTransacao[agendamento->tam] = transacao;
        agendamento->tam++;
    }
}

void appendTransacao(apontAgen agendamento, int time, int id, char op, char attri){
    apontTrans transacao = (apontTrans) malloc(sizeof(struct Transactions));
    transacao->attri = attri;
    transacao->op = op;
    transacao->id = id;
    transacao->time = time;
    transacao->next = NULL;
    if(agendamento->tam==0){
        agendamento->vetTransacao = (apontTrans *) malloc(sizeof(apontTrans));//aumenta vetor
        agendamento->tam++;
    }
    apontTrans aux = agendamento->vetTransacao[0];
    if(aux == NULL) agendamento->vetTransacao[0] = transacao;
    else{
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = (apontTrans) transacao;
    }
}

