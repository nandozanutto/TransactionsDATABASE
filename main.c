#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    apontTrans next;//ponteiro para a próx transação Ti
};

struct Agendamento
{
    apontTrans *vetTransacao;//vetor de apontadores para transações
    int tam;//quantidade de transações
};

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

void testSeriab(apontAgen agendamento){
    for(int j=0; j<agendamento->tam; j++){
        for(apontTrans transacaoTj=agendamento->vetTransacao[j]; transacaoTj!=NULL; transacaoTj=transacaoTj->next){
            if(transacaoTj->op == 'R'){
                for(int i=0; i<agendamento->tam; i++){//varre as transações a procura de um write 
                    if(i==j) continue;//se Ti está comparando com Ti
                    for(apontTrans transacaoTi=agendamento->vetTransacao[i]; transacaoTi!=NULL; transacaoTi=transacaoTi->next){
                        if((transacaoTi->op=='W') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            printf("Aresta R,W em %d -> %d\n", transacaoTi->id, transacaoTj->id);
                    }
                }
            }else if(transacaoTj->op == 'W'){
                for(int i=0; i<agendamento->tam; i++){//varre as transações a procura de um write 
                    if(i==j) continue;//se Ti está comparando com Ti
                    for(apontTrans transacaoTi=agendamento->vetTransacao[i]; transacaoTi!=NULL; transacaoTi=transacaoTi->next){
                        if((transacaoTi->op=='R') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            printf("Aresta W,R em %d -> %d\n", transacaoTi->id, transacaoTj->id);
                        if((transacaoTi->op=='W') && (transacaoTj->attri==transacaoTi->attri) && (transacaoTj->time>transacaoTi->time))
                            printf("Aresta W,W em %d -> %d\n", transacaoTi->id, transacaoTj->id);
                    }
                }
            }
        }
    }
}
/* Function to swap values at two pointers */
void swap(apontAgen agendamento, int i, int j)
{
    apontTrans aux = agendamento->vetTransacao[i];
    agendamento->vetTransacao[i] = agendamento->vetTransacao[j];
    agendamento->vetTransacao[j] = aux;
}
 
/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
int global=0;
void permute(apontAgen agendamento, int l, int r)
{
    int i;
    if (l == r){
        printf("agendamento:\n");
        global++;
        for(int i=0; i<agendamento->tam; i++){
            for(apontTrans j=agendamento->vetTransacao[i]; j!=NULL; j=j->next)
                printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
            printf("\n");
        }
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap(agendamento, l, i);
            permute(agendamento, l+1, r);
            swap(agendamento, l, i);
        }
    }
}


// int visaoEquiv(apontAgen agendamento){
//     agendamento->vetTransacao[0].
// }


int main(){

    // apontAgen agendamento = criaAgendamento();
    // criaTransacao(agendamento, 1, 1, 'R', 'X');
    // criaTransacao(agendamento, 2, 2, 'R', 'X');
    // criaTransacao(agendamento, 3, 3, 'R', 'X');
    // criaTransacao(agendamento, 4, 1, 'R', 'X');
    // criaTransacao(agendamento, 5, 1, 'R', 'X');
    // criaTransacao(agendamento, 6, 3, 'R', 'X');
    // criaTransacao(agendamento, 7, 2, 'R', 'X');


    
    apontAgen agendamento = criaAgendamento();
    apontAgen agendamento2 = criaAgendamento();
    int commits=0;
    while(1){
        int time;
        int id;
        char op;
        char attri;
        if(scanf("%d", &time) == EOF)//checa se existe nova linha
            break;
        scanf("%d %c %c", &id, &op, &attri);
        if(op == 'C'){
            commits++;//commits não são salvos
            if(commits == agendamento->tam){//supõe que os commits são dados em seq
                commits=0;
                break;
            }
        }
        else{
                criaTransacao(agendamento, time, id, op, attri);
                appendTransacao(agendamento2, time, id, op, attri);
        }
 
    }

    for(int i=0; i<agendamento->tam; i++){
        for(apontTrans j=agendamento->vetTransacao[i]; j!=NULL; j=j->next)
            printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
        printf("\n");
    }
    for(int i=0; i<agendamento2->tam; i++){
        for(apontTrans j=agendamento2->vetTransacao[i]; j!=NULL; j=j->next)
            printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
        printf("\n");
    }
    // testSeriab(agendamento);
    // permute(agendamento, 0, agendamento->tam-1);



    return 0;
}