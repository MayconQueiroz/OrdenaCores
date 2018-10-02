#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>
#include <time.h>
#include "Listas.h"

/**
* Ordena cores por escala de cinza de acordo com parametros recebidos
*/

Elemento* lista; //Lista de triplas RGB
Elemento* final; //Lista de triplas RGB (ordenada)
float PR, PG, PB; //Fatores de ponderacao em R, G e B
int Anl = 0; //Analisados

//Funcoes
void insereValores();
Elemento* selection(Elemento* lista, Elemento* final);
DWORD WINAPI ThreadFunc();

int main(int argc, char const *argv[]){
  if (argc != 4){
    printf("Quantidade de parametros invalida.\n");
    printf("Chamada:\n");
    printf("OCor PesoR PesoG PesoB\n");
    printf("  PesoR\tFator de multiplicacao com o canal R para escala de cinza\n");
    printf("  PesoG\tFator de multiplicacao com o canal G para escala de cinza\n");
    printf("  PesoB\tFator de multiplicacao com o canal B para escala de cinza\n");
  }

  PR = atof(argv[1]);
  PG = atof(argv[2]);
  PB = atof(argv[3]);
  if (PR == 0 || PG == 0 || PB == 0){
    printf("Nao foi possivel converter a string em um numero ou \no numero e igual a zero o que nao e permitido, tente novamente");
    return 1;
  }

  lista = lista_cria();
  final = lista_cria();
  insereValores();

  //Chamada da thread filha
  system("ECHO Iniciado em \%DATE\% - \%TIME\%");
  printf("\nOrdenados         0 de 16777216");
  HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);

  lista_calculacinza(lista, PR, PG, PB);
  //lista_imprime(lista);
  final = selection(lista, final);
  //printf("-----\n");
  //lista_imprime(final);
  printf("Imprimindo no arquivo\n");
  lista_imprimearquivo(final);

  return 0;
}


void insereValores(){
  int i, j, k;
  for (i = 0; i < 256; i+=1){
    for (j = 0; j < 256; j+=1){
      for (k = 0; k < 256; k+=1){
        lista = lista_insere(lista, i, j, k);
      }
    }
  }
}

/*
void insereValores(){
  lista = lista_insere(lista, 0, 0, 0);
  lista = lista_insere(lista, 255, 255, 255);
  lista = lista_insere(lista, 128, 128, 128);
  lista = lista_insere(lista, 255, 0, 0);
  lista = lista_insere(lista, 0, 255, 0);
  lista = lista_insere(lista, 0, 0, 255);
  lista = lista_insere(lista, 128, 0, 255);
  lista = lista_insere(lista, 0, 128, 0);
}
*/

Elemento* selection(Elemento* lista, Elemento* final){
  float pivo;
  Elemento* p; //Menor
  Elemento* q; //Procura
  Elemento* r; //Anterior Procura
  Elemento* s; //Anterior Menor
  while (lista != NULL){ //Ate fim da lista
    pivo = lista->E;
    p = lista;
    s = NULL; //Se s for null ao final, elemento que vai ser retirado e o primeiro da lista
    if (lista->prox == NULL){ //So tem um elemento
      p->prox = final;
      final = p;
      Anl++;
      break;
    }

    for (r = lista; r->prox != NULL; r = r->prox){ //Procura menor elemento
      q = r->prox;
      if (q->E < pivo){
        p = q;
        s = r;
        pivo = q->E;
      }
    }

    if (p == lista){ //Costura
      lista = p->prox;
    } else {
      s->prox = p->prox;
    }

    p->prox = final;
    final = p;
    Anl++;
  }
  Anl = -1;
  return final;
}

//Funcao que a segunda Thread roda
DWORD WINAPI ThreadFunc(){ //AJUSTAR
  time_t OTm, NTm;
  OTm = time(NULL);
  char BS = 8;
  while (Anl != -1){
    NTm = time(NULL);
    if (NTm > (OTm + 10)){ //A cada 10 segundos
      OTm = NTm;
      printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS, BS);
      printf("%9d de 16777216", Anl);
      fflush(stdout);
    }

  }
  return 0;
}
