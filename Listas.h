#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
* Listas especiais com uma tripla RGB e escala de cinza
*/

typedef struct elemento Elemento;
FILE *IN1;

struct elemento{
  unsigned char R, G, B;
  float E;
  Elemento* prox;
};

struct Elemento{
  unsigned char R, G, B;
  float E;
  Elemento* prox;
};

Elemento* lista_insere(Elemento* lista, int iR, int iG, int iB){ //Insere direto
  Elemento* novo = (Elemento*) malloc(sizeof(Elemento)); //Reserva um espaço para novo
  novo->R = iR;
  novo->G = iG;
  novo->B = iB;
  novo->prox = lista; //Poe o ponteiro para o novo apontando para o elemento anterior da lista
  return novo;
}

Elemento* lista_cria(){ //Retorna Null, criação de listas
  return NULL;
}

void lista_imprime (Elemento* lista){ //Varre e imprime
  Elemento* p;
  if (lista == NULL){
    printf("Lista Vazia\n");
  }
  for (p = lista; p != NULL; p = p->prox){
    printf("%hu\t%hu\t%hu\t%f\n", p->R, p->G, p->B, p->E);
  }
}

void lista_imprimearquivo(Elemento* lista){ //Imprime no arquivo OUT.txt
  Elemento* p;
  IN1 = fopen("OUT.txt","w");
  if (IN1 == NULL){
    printf("Nao foi possivel abrir o arquivo de saida, tente novamente");
  }
  if (lista == NULL){
    fprintf(IN1, "Lista Vazia\n");
  }
  for (p = lista; p != NULL; p = p->prox){
    fprintf(IN1, "%i\t%i\t%i\n", p->B, p->G, p->R);
  }
}

Elemento* lista_apagar(Elemento* lista){
  Elemento* p;
  Elemento* q;
  int U = 0;
  if (lista == NULL){
    return NULL;
  }
  p = lista;
  while(U == 0){
    q = p->prox;
    free(p);
    p = q;
    if (p == NULL)
      U = 1;
  }
  return NULL;
}

void lista_calculacinza(Elemento* lista, float pR, float pG, float pB){ //Calcula escala de cinza da lista baseado nos parametros
  Elemento* p;
  for (p = lista; p != NULL; p = p->prox){
    p->E = (p->R*pR) + (p->G*pG) + (p->B*pB);
  }
}

//Funcao main isolada porque codigo virou um .h
/*int main (){ //Listas simplesmente encadeadas
  Elemento* lista;
  int O, V=0, E, A=0;
  lista=lista_cria();
  printf("-----------------------------------\n");
  printf("   LISTAS SIMPLESMENTE ENCADEADAS\n");
  printf("-----------------------------------\n");
  while(A==0){
    printf("-----------------------------------\n");
    printf("Selecione alguma das opcoes abaixo:\n");
    printf("-----------------------------------\n");
    printf(" 0 - Inserir Elemento\n");
    printf(" 1 - Remover Elemento\n");
    printf(" 2 - Procurar Elemento\n");
    printf(" 3 - Imprimir Lista\n");
    printf(" 4 - Zerar Lista\n");
    printf(" 5 - Leitura de Arquivo\n");
    printf(" 6 - Escrita em Arquivo\n");
    printf(" 7 - Encerrar Programa\n");
    printf("-----------------------------------\n");
    scanf("%i", &O);
    printf("-----------------------------------\n");
    switch (O) {
      case 0:
        printf("Insira o elemento que deseja inserir na lista:\n");
        scanf("%i", &V);
        lista=lista_insere(lista, V);
        break;
      case 1:
        printf("Insira o elemento que deseja remover na lista:\n");
        scanf("%i", &V);
        lista=lista_remove(lista, V);
        break;
      case 2:
        printf("Insira o elemento que deseja procurar na lista:\n");
        scanf("%i", &V);
        E=lista_procura(lista, V);
        if (E==1) {
          printf("Elemento nao encontrado\n");
        }
        break;
      case 3:
        lista_imprime(lista);
        break;
      case 4:
        lista = lista_apagar(lista);
        break;
      case 5:
        lista = lista_leituraarquivo(lista);
        break;
      case 6:
        lista_imprimearquivo(lista);
        break;
      case 7:
        A=1;
        lista = lista_apagar(lista);
        break;
      default:
        printf("Opcao Invalida\n");
    }
  }
  return 0;
}*/
