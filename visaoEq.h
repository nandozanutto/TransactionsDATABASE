#ifndef __VISAOEQ_H__
#define __VISAOEQ_H__

typedef struct Dependency *apontDepen;

struct Dependency{
    int read;
    int write;
    apontDepen next;
};

apontTrans ultimaEscrita(apontAgen agendamento);
apontDepen leituraEscrita(apontAgen agendamento);
int comparaDependencia(apontDepen dependencia1, apontDepen dependencia2);
int comparaHistory(apontTrans historico1, apontTrans historico2);
apontAgen transforma(apontAgen agendamento);
void swap(apontAgen agendamento, int i, int j);


#endif