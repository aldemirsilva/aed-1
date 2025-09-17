#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000000

void ordenaInsercao(int v[], int tamanho) {
  int i, j;
  int pivot;

  for (j = 1; j < tamanho; j++) {
    i = j - 1;
    pivot = v[j];
    while ((i >= 0) && (v[i] > pivot)) {
      v[i + 1] = v[i];
      i--;
    }
    v[i + 1] = pivot;
  }
}

void qSortInterno(int v[], int inicio, int fim);
/* Funcao quickSort a ser chamada em outros pontos do programa. Serve apenas
 * para disparar a chamada recursiva */
void quickSort(int v[], int n) {
  qSortInterno(v, 0, n - 1);
  ordenaInsercao(v, n);
}

/* Implementacao do quicksort em si. */
void qSortInterno(int v[], int inicio, int fim) {
  int pivot;
  int temp;
  int i, j;

  if (fim - inicio > 50) { // 50 seria para ser estudado, pode ser um pouco menor
    i = inicio;
    j = fim;
    pivot = v[(i + j) / 2];

    do {
      while (v[i] < pivot)
        i++; /* procura por algum item do lado errado (>= pivot) */
      while (v[j] > pivot)
        j--;        /* procura por algum item do lado errado (<= pivot) */
      if (i <= j) { /* deixa o igual para garantir que ao final i<j */
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
        i++;
        j--;
      }
    } while (i <= j);
    qSortInterno(v, inicio, j);
    qSortInterno(v, i, fim);
  }
}

int main() {
  int *v;
  int i;
  srand(0);

  v = (int *)malloc(sizeof(int) * N);
  for (i = 0; i < N; i++) {
    v[i] = rand();
  }

  printf("iniciando ordenacao...\n");
  quickSort(v, N);
  printf("ordenacao concluida.\n");
  for (i = 0; i < 10; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
}
