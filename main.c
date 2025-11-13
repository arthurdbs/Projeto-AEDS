#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as): Taislane e Arthur

Data: 13/11/2025

****************/



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

void inserirElementos(int N, int *vet){
      if(N<=0)return;
      
      FLVazia(&segm.elementos);
      
      int anterior = -1;
      
      for(int i=0; i<N; i++){
      
        if(vet[i] == 0){
           segm.tiposeg = 1;
        } else if(vet[i] == 128){
           segm.tiposeg = 2;
        }else if(vet[i] == 255){
           segm.tiposeg = 3;     
        }
        if(segm.tiposeg != anterior){
        TipoItem item;
        item.Chave = segm.tiposeg;
        Insere(item, &segm.elementos);
        }
      }
}
void encontrarPadrao(int N,int *vet){
   int padrao[] = {1, 3, 2, 3, 1};
   int vetAux[5];
   int n=5 , qtd = 0;
   int cont = 0, confirmacao = 0;
   
   TipoApontador p = segm.elementos.Primeiro;
   
   while(p != NULL){
   
       if(p-> Item.Chave == padrao[cont]){
       
       vetAux[cont] = p->Item.Chave;
       cont++;
       }
       if(cont == n){
         confirmacao = 1;
          qtd++;
          cont = 0;
       } else{
           if(p->Item.Chave == padrao[0]){
           vetAux[0]= p->Item.Chave;
           cont = 1;
           }
       }
      p = p->Prox;
   }
   if(confirmacao == 1){
       printf("Resultado: Padrao encontrado.");
   }else{
       printf("Resultado: Padrao nao encontrado.");
   }
   
}
int main(){
     int N=0;
     printf("Digite o valor de N\n");
     scanf("%d", &N);
     int vet[N];
     
     for(int i =0; i<N; i++){
         scanf("%d", &vet[i]);
     }
     inserirElementos(N, vet);
     
     encontrarPadrao(N, vet);
 return 0;
}