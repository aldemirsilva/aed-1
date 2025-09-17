#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* aqui definimos o tipo dado contendo os dados que vao ser guardados em nossa
 * lista encadeada */
typedef struct tipoDado {
  char nome[30];
  int id;
} tipoDado;

/* definicao do tipo que representa cada nó da lista. */
typedef struct tipoNo {
  struct tipoNo *prox;
  tipoDado d;
} tipoNo;

/* definicao do tipo lista que será usado para representar nossas listas */
typedef struct tipoLista {
  tipoNo *prim;
} tipoLista;

/* funcao que cria uma lista encadeada vazia */
void criaLista(tipoLista *l) { l->prim = NULL; }

/* funcao que insere elemento na lista */
void insereNaLista(tipoLista *l, tipoDado d) {
  tipoNo *aux;
  aux = (tipoNo *)malloc(sizeof(tipoNo));
  aux->d = d;
  aux->prox = l->prim;
  l->prim = aux;
}

/* Carrega dados de um arquivo para uma lista encadeada */
void carregaListaDoArquivo(char *arquivo, tipoLista *lista) {
  FILE *fpArq;
  tipoDado d;
  fpArq = fopen(arquivo, "r");
  if (fpArq) {
    while (fread(&d, sizeof(tipoDado), 1, fpArq)) {
      insereNaLista(lista, d);
    }
  }
  fclose(fpArq);
}

/* Grava os dados de uma lista encadeada
   cuidado! destroi o arquivo caso já exista um com mesmo nome!
*/
void gravaListaEmArquivo(char *arquivo, tipoLista *lista) {
  FILE *fpArq;
  tipoDado d;
  tipoNo *aux = lista->prim;

  fpArq = fopen(arquivo, "w");
  if (fpArq) {
    while (aux) {
      fwrite(&(aux->d), sizeof(tipoDado), 1, fpArq);
      aux = aux->prox;
    }
  }
  fclose(fpArq);
}

int tamanhoArquivo(FILE *f) {
  struct stat buf;
  fstat(fileno(f), &buf);
  return buf.st_size;
}

/* Funcao de busca para vetores NÃO ordenados.
   Busca sequencialmente
   Retorna verdadeiro se o elemento buscado está no vetor
*/

int buscaSequencial(FILE *fp, char *chave) {
  tipoDado d;

  fseek(fp, 0, SEEK_SET);

  while (fread(&d, sizeof(tipoDado), 1, fp)) {
    if (!strcmp(d.nome, chave)) {
      return 1;  // 1 é o nosso verdadeiro!
    }
  }
  return 0;
}

int buscaBinaria(FILE *fp, char *chave, tipoDado *pd) {
  int inicio, fim, meio;
  tipoDado d;
  inicio = 0;
  fim = (tamanhoArquivo(fp) / sizeof(tipoDado)) - 1;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;
    fseek(fp, meio * sizeof(tipoDado), SEEK_SET);
    fread(&d, sizeof(tipoDado), 1, fp);
    if (strcmp(chave, d.nome) > 0) {
      inicio = meio + 1;
    } else {
      if (strcmp(chave, d.nome) < 0) {
        fim = meio - 1;
      } else {
        *pd = d;
        return 1;
      }
    }
  }
  return 0;
}

/* versao 1
   usa tipoLista *l para ficar padronizada com funcao de insercao!
   retorna um ponteiro para o dado, caso encontre e retorna NULL em caso
   contrario
 */
tipoDado *buscaPorNomeNaLista(tipoLista *l, char *chave) {
  tipoNo *aux;
  aux = l->prim;
  while ((aux != NULL) && (strcmp(aux->d.nome, chave) != 0)) {
    aux = aux->prox;
  }
  if (aux) {
    return &aux->d;
  }
  return NULL;
}

char removeElemento(tipoLista *l, char *chave) {
  tipoNo *ant, *atual;

  if (l->prim) {
    ant = l->prim;
    if (!strcmp(ant->d.nome, chave)) {  // Se quero apagar 1o
      l->prim = ant->prox;
      free(ant);
      return 1;
    } else {  // Se quero apagar algum outro
      atual = ant->prox;
      while (atual) {
        if (!strcmp(atual->d.nome, chave)) {  // Se quero apagar 1o
          ant->prox = atual->prox;
          free(atual);
          return 1;
        }
        ant = atual;
        atual = atual->prox;
      }
    }
  }
  return 0;
}

void mostraDado(tipoDado d) {
  printf("------------------\n");
  printf("Nome: %s\n", d.nome);
  printf("ID: %d\n", d.id);
}

/* uma das muitas versoes para mostrar os dados armazenados em uma lista */
void mostraLista(tipoLista l) {
  while (l.prim) {
    mostraDado(l.prim->d);
    l.prim = l.prim->prox;
  }
}

/* mais uma das muitas versoes para mostrar os dados armazenados em uma lista */
void mostraListaVersao2(tipoLista *l) {
  tipoNo *aux = l->prim;
  while (aux) {
    mostraDado(aux->d);
    aux = aux->prox;
  }
}

void destroiLista(tipoLista *l) {
  tipoNo *aux, *tmp;
  aux = l->prim;
  while (aux != NULL) {
    tmp = aux;
    aux = aux->prox;
    free(tmp);
  }
  l->prim = NULL;
}

void leDados(tipoDado *x) {
  printf("Entre com os dados de uma pessoa:\n");
  printf("Nome:");
  scanf("%[^\n]%*c", x->nome);
  printf("Id:");
  scanf("%d%*c", &x->id);
}

int main() {
  tipoLista l1;
  tipoLista l2;
  tipoDado x;
  tipoDado *resultado;
  char nome[30];
  int c;
  FILE *fp1, *fp2;

  fp1 = fopen("...");
  fp2 = fp1;
  criaLista(&l1);
  criaLista(&l2);

  /* TO DO FUNCAO para carregar os dados da lista entrados em execucoes
   * passadas */

  carregaListaDoArquivo("arqLista.data", &l1);

  printf("********* INSERINDO DADOS NA LISTA 1 *************\n");
  for (c = 0; c < 5; c++) {
    leDados(&x);
    insereNaLista(&l1, x);
  }
  printf("********* INSERINDO DADOS NA LISTA 2 *************\n");
  leDados(&x);
  insereNaLista(&l2, x);
  printf("conteudo da lista 1:\n");
  mostraLista(l1);
  printf("\n**************\n conteudo da lista 2:\n");
  mostraLista(l2);

  do {
    printf("Entre com um nome a ser buscado: ");
    scanf("%[^\n]%*c", nome);
    /* busca abaixo deve retornar um ponteiro para o dado existente na lista
     * caso encontre a chave e retornar NULL em caso contrário */

    printf("Fazendo buscas na lista 1. Tecle fim para terminar\n");
    resultado = buscaPorNomeNaLista(&l1, nome);
    if (resultado) {
      printf("Nome encontrado: %s\n", resultado->nome);
      printf("Id da pessoa: %d \n", resultado->id);
      /* inserindo o nome na lista 2. Assumindo que esse era o objetivo */
      insereNaLista(&l2, *resultado);
    } else {
      printf("Nome não encontrado\n");
    }
  } while (strcmp(nome, "fim") != 0);

  printf("\n**************\n conteudo da lista 2:\n");
  mostraLista(l2);

  do {
    printf("Entre com um nome a ser removido: ");
    scanf("%[^\n]%*c", nome);
    /* busca abaixo deve retornar um ponteiro para o dado existente na lista
     * caso encontre a chave e retornar NULL em caso contrário */

    if (removeElemento(&l2, nome)) {
      printf("Elemento removido\n");
    } else {
      printf("Elemento não encontrado\n");
    }
    printf("\n**************\n conteudo da lista 2 apos remocao:\n");
    mostraLista(l2);

  } while (strcmp(nome, "fim") != 0);

  /* zera o arquivo e grava nova lista com os dados anteriormente gravados */
  gravaListaEmArquivo("arqLista.data");
}
