#include <stdio.h>

// usando ponteiros para passagem de parametros por referencia


typedef struct tipoTeste {
  unsigned long a;
  int b;
} tipoTeste;

// Ponteiros sendo usados para modificar parametros

void zeraNumero(unsigned long *n) {
 // A variavel apontada por n recebe (NAO É o n). n é ponteiro para unsigned long. *n é um unsigned long  apontado por ele.
  *n = 0;
} 

void inc(unsigned long *n) {
  (*n)++;
}


void zeraPonteiro(int **p) {
  // A variavel apontada por p recebe NULL (NAO É o P). p é ponteiro para ponteiro para inteiro, *p é o ponteiro apontado por ele.

  *p = NULL;
}

int main() {
  unsigned long k,l,*pu;

  int *pt;
  tipoTeste x;
 
  // passando o endereco de k para a funcao, a funcao vai zerar o k
  zeraNumero(&k); 
  
  // notem que x.a é unsigned long, logo &x.a pode ser passado como parâmetro, visto que ele é ponteiro para unsigned long (recebe enderecos de unsigned long)
  zeraNumero(&x.a);
  pu = &x.a;
  // note que na chamada abaixo nao tem o &, pois o pu é ponteiro e quero passar o valor dele!
  zeraNumero(pu);

  // note que &p é do tipo ponteiro para ponteiro para inteiro( int **), logo pode ser passado pra funcao. O parametro vai ficar entao com o endereco de pt. pt vai zer zerado (receber NULL) na funcao.

  zeraPonteiro(&pt);
  
}
