#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h" 
#include "stack.h"
#include "transacao.h"
#include "testeConflito.h"
#include "visaoEq.h"


int globalVisao=0;
void visaoEquiv(apontAgen agendamento, int l, int r, apontAgen agenSerial)
{
    if(globalVisao == 1)
        return;
    int i;
    if (l == r){
        apontAgen newAgen = transforma(agendamento);
        apontTrans historico = ultimaEscrita(agenSerial);
        apontTrans historicoTeste = ultimaEscrita(newAgen);

        apontDepen dependencia = leituraEscrita(agenSerial);
        apontDepen dependenciaTeste = leituraEscrita(newAgen);
        if(comparaHistory(historico, historicoTeste) && comparaDependencia(dependencia, dependenciaTeste)){
            globalVisao = 1;//achou uma visão serial equivalente
            return;
        }
            
        // printf("ultima escrita: %d\n", comparaHistory(historico, historicoTeste));
        // printf("dependencia: %d\n", comparaDependencia(dependencia, dependenciaTeste));

    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap(agendamento, l, i);
            visaoEquiv(agendamento, l+1, r, agenSerial);
            swap(agendamento, l, i);
        }
    }
}




int lerAgendamento(int numAgen){
    int acabouArquivo=0;
    int vazio=1;//nao li nada
    apontAgen agendamento = criaAgendamento();
    apontAgen agendamento2 = criaAgendamento();
    int commits=0;
    while(1){
        int time;
        int id;
        char op;
        char attri;
        if(scanf("%d", &time) == EOF){//checa se existe nova linha
            acabouArquivo=1;
            break;
        }
        scanf("%d %c %c", &id, &op, &attri);
        if(op == 'C'){
            commits++;//commits não são salvos
            if(commits == agendamento->tam){//se todas as transações abertas foram fechadas
                commits=0;
                break;
            }
        }
        else{
                vazio=0;//alguma transação foi lida
                criaTransacao(agendamento, time, id, op, attri);
                appendTransacao(agendamento2, time, id, op, attri);
        }
 
    }
    if(vazio)
        return acabouArquivo;

    // for(int i=0; i<agendamento->tam; i++){
    //     for(apontTrans j=agendamento->vetTransacao[i]; j!=NULL; j=j->next)
    //         printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
    //     printf("\n");
    // }
    // for(int i=0; i<agendamento2->tam; i++){
    //     for(apontTrans j=agendamento2->vetTransacao[i]; j!=NULL; j=j->next)
    //         printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
    //     printf("\n");
    // }

    visaoEquiv(agendamento, 0, agendamento->tam-1, agendamento2);


    Graph grafo;
    grafo = GRAPHinit(agendamento->tam);
    testSeriab(agendamento, grafo);
    // printGraph(grafo);
    envelopeBusca(grafo);


    //impressão de resultados
    printf("%d ", numAgen);
    for(int i=0; i<agendamento->tam; i++){
        if(i==agendamento->tam-1)
            printf("%d ", agendamento->vetTransacao[i]->id);
        else
            printf("%d,", agendamento->vetTransacao[i]->id);
    
    } 
    if(temCiclo(grafo))
        printf("NS");
    else
        printf("SS");
    if(globalVisao)
        printf(" SV\n");
    else
        printf(" NV\n");
    
    globalVisao=0;
    return acabouArquivo;

}

int main(){
    int numAgen=1;
    while(lerAgendamento(numAgen)!=1)
        numAgen++;
    return 0;
}