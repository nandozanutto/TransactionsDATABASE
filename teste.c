#include<stdio.h>
#include<stdlib.h>
#include "graph.h" 
#include "stack.h"



// int MAXSIZE = 100;       
// apontador stack[100];     
// int top = -1;            

// int isempty() {

//    if(top == -1)
//       return 1;
//    else
//       return 0;
// }
   
// int isfull() {

//    if(top == MAXSIZE)
//       return 1;
//    else
//       return 0;
// }

// apontador peek() {
//    return stack[top];
// }

// apontador pop() {
//    apontador data;
	
//    if(!isempty()) {
//       data = stack[top];
//       top = top - 1;   
//       return data;
//    } else {
//       printf("Could not retrieve data, Stack is empty.\n");
//    }
// }

// int push(apontador data) {

//    if(!isfull()) {
//       top = top + 1;   
//       stack[top] = data;
//    } else {
//       printf("Could not insert data, Stack is full.\n");
//    }
// }
// int t=1;
// void Busca(Graph G, int r){
//    push(G->vertices[r]);
//    G->vertices[r]->estado=1;
//    G->vertices[r]->pre=t;
//    t++;
//    while(!isempty()){
//       apontador v = peek();
//       if(v->proxVizinho == NULL){
//          pop();
//          v->estado = 2;
//          v->pos = t;
//          t++;
//       } 
//       else{
//          apontador w = v->proxVizinho->w;//proximo vizinho
//          v->proxVizinho = v->proxVizinho->next;//avança o ultimo vizinho lido

//          if(w->estado == 0){
//             w->pai = v;
//             push(w);
//             w->estado=1;
//             w->pre = t;
//             t++;
//          }
//       }
//    }


// }

// void envelopeBusca(Graph G){
//    for(int i=0; i<G->V; i++){
//       if(G->vertices[i]->estado == 0)
//          Busca(G, i);
//    }

// }

// int temCiclo(Graph G){
//    for(int i=0; i<G->V; i++)
//       for(link vizinho = G->vertices[i]->adj; vizinho!=NULL; vizinho=vizinho->next)
//          if(G->vertices[i]->pos < vizinho->w->pos)//arco de retorno
//             return 1;
         
//    return 0;
// }



int main(){
   Graph grafo;//ponteiro para o grafo
   grafo = GRAPHinit(9);
   GRAPHinsertArc(grafo, 0, 3);
   GRAPHinsertArc(grafo, 0, 2);
   GRAPHinsertArc(grafo, 0, 1);
   GRAPHinsertArc(grafo, 1, 2);
   GRAPHinsertArc(grafo, 3, 2);
   GRAPHinsertArc(grafo, 3, 4);

   GRAPHinsertArc(grafo, 5, 6);
   GRAPHinsertArc(grafo, 5, 0);
   GRAPHinsertArc(grafo, 6, 8);
   GRAPHinsertArc(grafo, 6, 4);
   GRAPHinsertArc(grafo, 7, 6);
   GRAPHinsertArc(grafo, 7, 5);
   GRAPHinsertArc(grafo, 8, 7);

   printGraph(grafo);
   envelopeBusca(grafo);
   printf("%d\n", temCiclo(grafo));
   for(int i=0; i<grafo->V; i++)
      printf("pre: %d pos: %d\n", grafo->vertices[i]->pre, grafo->vertices[i]->pos);



}