#ifndef __TRANSACAO_H__
#define __TRANSACAO_H__


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

apontAgen criaAgendamento();
int retornaPos(apontAgen agendamento, char id);
void criaTransacao(apontAgen agendamento, int time, int id, char op, char attri);
void appendTransacao(apontAgen agendamento, int time, int id, char op, char attri);



#endif