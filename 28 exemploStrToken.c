#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[20];
  float preco;
} tipoProduto;

void parserLinha(char *linha, tipoProduto *p) {
  char *token;
  float preco;

  token = strtok(linha, ";");
  strcpy(p->nome, token);
  token = strtok(NULL, ";");
  p->preco = atof(token);
}

int main(int argc, char *argv[]) {
  FILE *qualquer;
  char linha[300];
  tipoProduto *produto;
  int cont = 0;

  qualquer = fopen(argv[1], "r");
  if (qualquer == NULL) {
    printf("Nao foi possivel abrir o arquivo\n");
    exit(1);
  }

  while (fgets(linha, 300, qualquer)) {
    cont++;
  }
  produto = (tipoProduto *)malloc(sizeof(tipoProduto) * cont);

  fseek(qualquer, 0, SEEK_SET);

  cont = 0;
  while (fgets(linha, 300, qualquer)) {
    parserLinha(linha, &produto);
    printf("Nome do produto: %s\n", produto[cont].nome);
    printf("Nome do produto: %.2f\n", produto[cont].preco);
    cont++;
  }
}
