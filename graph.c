#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "stack.h"
/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */

void NEWVertice(Graph grafo, int novoV) { 
   grafo->vertices[novoV] = (apontador)malloc(sizeof(struct vertex));               
   grafo->vertices[novoV]->number = novoV;
   grafo->vertices[novoV]->adj = NULL;
   grafo->vertices[novoV]->estado = 0;
   grafo->vertices[novoV]->pai=NULL;
   grafo->vertices[novoV]->proxVizinho=NULL;
}



/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */

Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V;
   G->vertices = malloc( V * sizeof (apontador));
   for(int i=0; i<V; i++)//criando V vertices
      NEWVertice(G, i);

   return G;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */

void GRAPHinsertArc( Graph G, int v, int w) {
   link aux = G->vertices[v]->adj;
   link newNodo = (link)malloc(sizeof(struct node));
   newNodo->w = G->vertices[w];

   G->vertices[v]->adj = newNodo;//w é o novo primeiro vizinho
   G->vertices[v]->proxVizinho = newNodo;
   newNodo->next = aux;
   // G->vertices[w]->pai = G->vertices[v];
   
}

void printGraph(Graph G){
   for(int i=0; i<G->V; i++){
      printf("Vertice %d: ", G->vertices[i]->number);
      for(link vizinho = G->vertices[i]->adj; vizinho!=NULL; vizinho=vizinho->next)
         printf("%d ", vizinho->w->number);
      printf("\n");
   }
}

//********busca em profundidade*********
int t=1;
void Busca(Graph G, int r){
   push(G->vertices[r]);
   G->vertices[r]->estado=1;
   G->vertices[r]->pre=t;
   t++;
   while(!isempty()){
      apontador v = peek();
      if(v->proxVizinho == NULL){
         pop();
         v->estado = 2;
         v->pos = t;
         t++;
      } 
      else{
         apontador w = v->proxVizinho->w;//proximo vizinho
         v->proxVizinho = v->proxVizinho->next;//avança o ultimo vizinho lido

         if(w->estado == 0){
            w->pai = v;
            push(w);
            w->estado=1;
            w->pre = t;
            t++;
         }
      }
   }


}

void envelopeBusca(Graph G){
   for(int i=0; i<G->V; i++){
      if(G->vertices[i]->estado == 0)
         Busca(G, i);
   }

}

int temCiclo(Graph G){
   for(int i=0; i<G->V; i++)
      for(link vizinho = G->vertices[i]->adj; vizinho!=NULL; vizinho=vizinho->next)
         if(G->vertices[i]->pos < vizinho->w->pos){//arco de retorno
            return 1;
         }
         
   return 0;
}
