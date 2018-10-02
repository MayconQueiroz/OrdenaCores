#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char A[50331648];
unsigned int N[13] = {50331702,0,54,40,4096,4096,1572865,0,50331648,0,0,0,0};
FILE* IN1;
FILE* OT1;

int main(int argc, char const *argv[]){
  int i = 0;

  IN1 = fopen("OUT.txt","r");
  if (IN1 == NULL){
    printf("Erro abrindo arquivo de entrada");
    return 1;
  }

  while (!feof(IN1)){
    fscanf(IN1, "%hu %hu %hu\n", &A[i], &A[i+1], &A[i+2]);
    i+=3;
  }

  OT1 = fopen("Imagem.bmp","w");
  if (OT1 == NULL){
    printf("Erro abrindo arquivo de saida");
    return 1;
  }

  fprintf(OT1, "BM");
  fwrite(N, sizeof(int), 13, OT1);
  fwrite(A, sizeof(char), 50331648, OT1);
  return 0;
}