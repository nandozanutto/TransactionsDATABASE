#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h" 
#include "stack.h"

typedef struct Transactions *apontTrans;
typedef struct Agendamento *apontAgen;
typedef struct Dependency *apontDepen;


struct Transactions 
{
    int time;
    int id;
    char op;
    char attri;
    apontTrans next;//ponteiro para a próx transação Ti
};

struct Dependency{
    int read;
    int write;
    apontDepen next;
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
 
/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
int global=0;
void permute(apontAgen agendamento, int l, int r, apontAgen agenSerial)
{
    int i;
    if (l == r){
        global++;
        apontAgen newAgen = transforma(agendamento);
        apontTrans historico = ultimaEscrita(agenSerial);
        apontTrans historicoTeste = ultimaEscrita(newAgen);

        apontDepen dependencia = leituraEscrita(agenSerial);
        apontDepen dependenciaTeste = leituraEscrita(newAgen);

        printf("ultima escrita: %d\n", comparaHistory(historico, historicoTeste));
        printf("dependencia: %d\n", comparaDependencia(dependencia, dependenciaTeste));
        // for(int i=0; i<newAgen->tam; i++){
        //     for(apontTrans j=newAgen->vetTransacao[i]; j!=NULL; j=j->next)
        //         printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
        //     printf("\n");
        // }
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap(agendamento, l, i);
            permute(agendamento, l+1, r, agenSerial);
            swap(agendamento, l, i);
        }
    }
}
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
    apontAgen teste = transforma(agendamento);
    for(int i=0; i<teste->tam; i++){
        for(apontTrans j=teste->vetTransacao[i]; j!=NULL; j=j->next)
            printf(".%d %d %c %c. ", j->time, j->id, j->op, j->attri);
        printf("\n");
    }

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

    permute(agendamento, 0, agendamento->tam-1, agendamento2);
    // apontTrans historico = ultimaEscrita(agendamento2);
    // apontTrans historicoTeste = ultimaEscrita(agendamento2);
    // historicoTeste->next->id=2;

    // printf("result: %d", comparaHistory(historico, historico));
    // for(apontTrans j=historico; j!=NULL; j=j->next)
    //     printf(".%d %c. ", j->id, j->attri);
    // printf("\n");
    
    // apontDepen dependencia = leituraEscrita(agendamento2);
    // apontDepen dependenciateste = leituraEscrita(agendamento2);
    // dependenciateste->next->write = -1;

    // for(apontDepen aux = dependencia; aux!=NULL; aux=aux->next){
    //     printf("%d %d\n", aux->read, aux->write);
    // }
    // printf("%d", comparaDependencia(dependencia, dependenciateste));

    // Graph grafo;
    // grafo = GRAPHinit(agendamento->tam);
    // testSeriab(agendamento, grafo);
    // printGraph(grafo);
    // envelopeBusca(grafo);
    // printf("%d\n", temCiclo(grafo));

    return 0;
}