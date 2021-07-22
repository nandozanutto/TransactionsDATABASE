#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "stack.h"


int MAXSIZE = 100;       
apontador stack[100];     
int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

apontador peek() {
   return stack[top];
}

apontador pop() {
   apontador data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("pilha vazia\n");
   }
}

int push(apontador data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("pilha cheia\n");
   }
}