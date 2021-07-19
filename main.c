#include<stdio.h>
#include<stdlib.h>
#include "graph.h" 
#include "stack.h"

typedef struct Transactions *apontTrans;
typedef struct Agendamento *apontAgen;


struct Transactions 
{
    int time;
    int id;
    char op;
    char attri;
};

struct Agendamento
{
    apontTrans *transacao;//vetor de apontadores para transações
    int tam;//quantidade de transações
    int primeiraVazia; //primeira pos vazia no vetor
};

apontAgen criaAgendamento(int tam){
    apontAgen agendamento = (apontAgen) malloc(sizeof(struct Agendamento));
    agendamento->transacao = malloc(tam*sizeof(apontTrans));
    agendamento->tam = tam;
    agendamento->primeiraVazia = 0;
    return agendamento;
}

void criaTransacao(apontAgen agendamento, int time, int id, char op, char attri){
    apontTrans transacao = (apontTrans) malloc(sizeof(struct Transactions));
    transacao->attri = attri;
    transacao->op = op;
    transacao->id = id;
    transacao->time = time;
    agendamento->transacao[agendamento->primeiraVazia] = transacao;
    agendamento->primeiraVazia++;

}




// void printAgen(Agendamento agen[]){
//     for(int j=1; j<2; j++){
//         for(int i=0; i<agen[j].tam; i++)
//             printf("%d %d %c %c\n", agen[j].trans[i].time, agen[j].trans[i].id, agen[j].trans[i].op, agen[j].trans[i].attri);
//     }
// }


int main(){

    apontAgen agendamento = criaAgendamento(5);
    criaTransacao(agendamento, 1, 2, 'W', 'X');
    criaTransacao(agendamento, 2, 3, 'R', 'X');
    printf("%c", agendamento->transacao[1]->op);
    
    
    // Transaction trans;
    // Agendamento agen[100];
    // agen[0].tam = 0;
    // agen[1].tam= 0;
    // int time, id, commit=0;
    // char op, attri;
    // int i=0;
    // int agenI=0;
    // int somado=0;
    // while(1){
    //     int time;
    //     int id;
    //     char op;
    //     char attri;
    //     if(scanf("%d", &time) == EOF)
    //         break;
    //     scanf("%d %c %c", &id, &op, &attri);
    //     if(op == 'C'){
    //         if(!somado){
    //             agenI++;
    //             somado=1;
    //         }
    //         i=0;
    //         continue;
    //     }
    //     else{
    //         agen[agenI].trans[i].time = time;
    //         agen[agenI].trans[i].id = id;
    //         agen[agenI].trans[i].op = op;
    //         agen[agenI].trans[i].attri = attri;
    //     }
    //     somado=0;
    //     i++;
    //     agen[agenI].tam++;

 
    // }
    // printAgen(agen);

}