#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* implementação do Ziviani começa aqui */
typedef int TipoChave;

typedef struct {
  int Chave; // posição da ocorrência
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

//  Funções do Ziviani 
void FLVazia(TipoLista *Lista) {
  Lista->Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista) {
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) {
  Lista->Ultimo->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

void ImprimeLista(TipoLista Lista) {
  TipoApontador Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) {
    printf("%d ", Aux->Item.Chave);
    Aux = Aux->Prox;
  }
}

typedef struct{
  int tiposeg;
  TipoLista elementos;
} Segmento;
 
Segmento segm;

void inserirElementos(int N, *vet){
      
      for(int i=0; i<N; i++){
        if(vet[i] == 0){
        TipoItem item;
        item.Chave = tiposeg;
        Insere(item, segm.elementos);
        }
      }
}

int main(){
     int N=0;
     scanf("%d", &N);
     int vet[N];
     
     
     for(int i =0; i<N; i++){
         scanf("%d", vet[i]);
     }
 
 
 return 0;
}