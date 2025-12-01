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

typedef struct {
    int tipo;      // 1, 2 ou 3
    int inicio;    // posição inicial do segmento
    int fim;       // posição final do segmento
} SegmentoInfo;

void inserirElementos(int N, int *vet, TipoLista *lista) {
    if(N<=0) return;

    FLVazia(lista);

    int anterior = -1;
    int inicio_seg = 0;

    for(int i=0; i<N; i++) {
        int tipo_atual;
        
        if(vet[i] == 0) {
            tipo_atual = 1;
        } else if(vet[i] == 128) {
            tipo_atual = 2;
        } else if(vet[i] == 255) {
            tipo_atual = 3;
        } else {
            continue; // ignora valores inválidos
        }

        if(tipo_atual != anterior) {
            if(anterior != -1) {
                TipoItem item;
                item.Chave = anterior * 1000000 + inicio_seg * 1000 + (i-1);
                // formato: tipo * 1000000 + inicio * 1000 + fim
                Insere(item, lista);
            }
            anterior = tipo_atual;
            inicio_seg = i;
        }
    }
    
    if(anterior != -1) {
        TipoItem item;
        item.Chave = anterior * 1000000 + inicio_seg * 1000 + (N-1);
        Insere(item, lista);
    }
}
int encontrarPontoMedio(TipoLista *lista) {
    int padrao[] = {1, 3, 2, 3, 1};
    int n = 5;
    
    TipoApontador p = lista->Primeiro->Prox;
    TipoApontador segmentos[100]; // guardar ponteiros dos segmentos
    int count = 0;
    
    // Coletar todos os segmentos
    while(p != NULL && count < 100) {
        segmentos[count++] = p;
        p = p->Prox;
    }
    
    // Procurar o padrão
    for(int i = 0; i <= count - n; i++) {
        int match = 1;
        for(int j = 0; j < n; j++) {
            int tipo = segmentos[i+j]->Item.Chave / 1000000;
            if(tipo != padrao[j]) {
                match = 0;
                break;
            }
        }
        
        if(match) {
            // Encontrou o padrão! O segmento da pista é o índice i+2 (elemento tipo 2)
            int chave = segmentos[i+2]->Item.Chave;
            int inicio = (chave % 1000000) / 1000;
            int fim = chave % 1000;
            int ponto_medio = (inicio + fim) / 2;
            return ponto_medio;
        }
    }
    
    return -1; // Não encontrou o padrão
}
int main(){
    int N, L;
    scanf("%d", &L);
    
    int pontos_medios[L];
    int linhas_validas = 0;
    
    for(int i = 0; i < L; i++) {
        scanf("%d", &N);
        
        int vet[N];
        for (int j = 0; j < N; j++){
            scanf("%d", &vet[j]);
        }
        
        TipoLista lista;
        inserirElementos(N, vet, &lista);
        int ponto_medio = encontrarPontoMedio(&lista);

        if(ponto_medio != -1){
            pontos_medios[linhas_validas] = ponto_medio;
            linhas_validas++;
        }
    }
    
    // Verificar se temos pelo menos 70% das linhas válidas
    float percentual = (float)linhas_validas / L;
    
    if(percentual < 0.7){
        printf("Resultado: Formato da pista nao estimado.\n");
        return 0;
    }
    
    // Analisar tendência dos pontos médios usando regressão linear
    if(linhas_validas < 3) {
        printf("Resultado: Formato da pista nao estimado.\n");
        return 0;
    }
    
    // Calcular coeficiente angular (inclinação) usando regressão linear
    // y = ax + b, onde y = ponto_medio e x = índice da linha
    float soma_x = 0, soma_y = 0, soma_xy = 0, soma_x2 = 0;
    
    for(int i = 0; i < linhas_validas; i++) {
        float x = i;
        float y = pontos_medios[i];
        soma_x += x;
        soma_y += y;
        soma_xy += x * y;
        soma_x2 += x * x;
    }
    
    // Coeficiente angular a = (n*sum(xy) - sum(x)*sum(y)) / (n*sum(x²) - (sum(x))²)
    float n = linhas_validas;
    float coef_angular = (n * soma_xy - soma_x * soma_y) / (n * soma_x2 - soma_x * soma_x);
    
    // Calcular R² (coeficiente de determinação) para medir quão bem a linha se ajusta
    float media_y = soma_y / n;
    float ss_tot = 0, ss_res = 0;
    
    for(int i = 0; i < linhas_validas; i++) {
        float y_pred = coef_angular * i + (soma_y - coef_angular * soma_x) / n;
        float y_real = pontos_medios[i];
        ss_tot += (y_real - media_y) * (y_real - media_y);
        ss_res += (y_real - y_pred) * (y_real - y_pred);
    }
    
    float r2 = 1 - (ss_res / ss_tot);
    
    // Decisão baseada no coeficiente angular
    // Threshold mais tolerante: considerar linha reta para inclinações pequenas
    
    if(coef_angular > -2.5 && coef_angular < 2.5) {
        // Inclinação pequena = linha reta
        printf("Resultado: Pista em linha reta.\n");
    }
    else if(coef_angular >= 2.5) {
        // Pontos médios aumentam fortemente = curva à esquerda
        printf("Resultado: Curva a esquerda.\n");
    }
    else if(coef_angular <= -2.5) {
        // Pontos médios diminuem fortemente = curva à direita
        printf("Resultado: Curva a direita.\n");
    }
    else {
        printf("Resultado: Pista em linha reta.\n");
    }

    return 0;
}

