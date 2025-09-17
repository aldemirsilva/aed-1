#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tipoPessoa {
  char nome[30];
  float salario;
  int id;
} tipoPessoa;

void preencheAleatoriamente(tipoPessoa v[], int tam) {
  int x, y;
  int tamString;
  char vogais[6] = "aeiou";
  char consoantes[22] = "bcdfghjklmnpqrstvxyzw";

  for (x = 0; x < tam; x++) {
    tamString = rand() % 29;
    for (y = 0; y < tamString; y++) {
      if (y == 0) {
        v[x].nome[y] = consoantes[rand() % 21] - 32;
      } else if ((y % 2) == 0) {
        v[x].nome[y] = consoantes[rand() % 21];
      } else {
        v[x].nome[y] = vogais[rand() % 5];
      }
    }
    v[x].nome[y] = 0;
    v[x].id = rand() % 1000;
    v[x].salario = ((rand() % 100000) + 100000) / 10.0;
  }
}

/* Funcao para ler valores para um vetor recebe como parametros um vetor v e seu
 * tamanho (tam)
 */

void lerVetor(tipoPessoa v[], int tam) {
  int x;
  static int k = 0;
  k++;

  for (x = 0; x < tam; x++) {
    printf("Entre com o nome da posicao [%d] : ", x);
    scanf("%[^\n]%*c", v[x].nome);
    printf("Entre com o id da posicao [%d] : ", x);
    scanf("%d%*c", &v[x].id);
    printf("Entre com o salario da posicao [%d] : ", x);
    scanf("%f%*c", &v[x].salario);
  }
}

/* Calcula o produto interno entre dois vetores, retornando o
   resultado */

int produtoInterno(int v1[], int v2[], int tam) {
  int x;
  int resultado = 0;

  for (x = 0; x < tam; x++) {
    resultado = resultado + (v1[x] * v2[x]);
  }
  return resultado;
}

/* busca binaria
 */

int buscabin(tipoPessoa v[], int n, int chave) {
  int inicio, fim, meio;

  inicio = 0;
  fim = n - 1;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;
    if (chave > v[meio].id) {
      inicio = meio + 1;
    } else {
      if (chave < v[meio].id) {
        fim = meio - 1;
      } else {
        return 1;
      }
    }
  }
  return 0;
}

void selecaoPorId(tipoPessoa v[], int n) {
  int i, j;
  int posMenor;
  tipoPessoa tmp;
  int tamMenos1 = n - 1;

  for (i = 0; i < tamMenos1; i++) {
    posMenor = i;
    for (j = i + 1; j < n; j++) {
      if (v[j].id < v[posMenor].id) {
        posMenor = j;
      }
    }
    tmp = v[i];
    v[i] = v[posMenor];
    v[posMenor] = tmp;
  }
}

void somarVetores(int res[], int v1[], int v2[], int tam) {
  int x;

  for (x = 0; x < tam; x++) {
    res[x] = v1[x] + v2[x];
  }
}

void mostrarVetor(tipoPessoa v[], int tam) {
  int x;

  for (x = 0; x < tam; x++) {
    printf("Pessoa na posição %d do vetor:\n", x);
    printf("Id: %.d\n", v[x].id);
    printf("Nome: %s\n", v[x].nome);
    printf("Salário: %.2f\n", v[x].salario);
    printf("-----------------------------\n");
  }
}

#define N 5

int main() {
  tipoPessoa v[8];

  preencheAleatoriamente(v, 8);
  //  lerVetor(v,8);
  mostrarVetor(v, 8);
  selecaoPorId(v, 8);
  printf("********* DEPOIS DE ORDENAR ************\n");

  mostrarVetor(v, 8);
}
