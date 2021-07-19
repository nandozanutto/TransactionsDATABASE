#ifndef __GRAPH_H__
#define __GRAPH_H__

// #define vertex int
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
typedef struct node *link;
typedef struct vertex *apontador;


struct vertex{
    int number;//vertice number;
    apontador pai; //ponteiro para o vértice pai
    link adj; // ponteiro para o primeiro vizinho de saída
    int pre, pos;//pre e pos number setados na busca em profund.
    int estado;
    link proxVizinho; //ultimoVizinho lido da lista de adjacencia
};


struct graph {
    int V;//num de vertices
    apontador *vertices; //vetor de apontadores para os vertices
    // link *adj; 
};

/* Um Graph é um ponteiro para um graph. */
typedef struct graph *Graph;

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */


struct node { 
   apontador w; 
   link next; 
};

void NEWVertice(Graph grafo, int novoV);
Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, int v, int w);
void printGraph(Graph G);
void Busca(Graph G, int r);
void envelopeBusca(Graph G);
int temCiclo(Graph G);
#endif