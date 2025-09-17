#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nome[20];
  float preco;
} tipoProduto;

int main(int argc, char *argv[]) {
  FILE *qualquer, *qualquerSaida;
  tipoProduto produto;

  if (argc != 3) {
    printf("Uso: %s <nome do arquivo entrada> <nome arquivo Saida>\n", argv[0]);
    exit(1);
  }

  qualquer = fopen(argv[1], "r");
  if (qualquer == NULL) {
    printf("Nao foi possivel abrir o arquivo\n");
    exit(1);
  }

  qualquerSaida = fopen(argv[2], "w");
  if (qualquerSaida == NULL) {
    printf("Nao foi possivel criar o arquivo\n");
    exit(1);
  }

  while (fscanf(qualquer, "%[^;]%*[; ]%f%*c", produto.nome, &produto.preco) ==
         2) {
    fprintf(qualquerSaida, "'%s': '%.2f'\n", produto.nome, produto.preco);
  }
}
