#include <stdio.h>

// PARA TESTES DE MUDANCA NO TAMANHO DE STRUCT POR MUDANCA NA ORDEM DOS CAMPOS
// VARIAVEIS NUMERICAS INT, SHORT INT, LONG INT, DOUBLE e FLOAT, bem
// COMO SUAS VERSOES SEM SINAL, DEVEM FICAR SEMPRE EM
// ENDERECOS MULTIPLOS DO SEU TAMANHO (EX. LONG MULTIPLO DE 8 NO MEU COMPUTADOR)

typedef struct tipoCoisa {
  long d;
  long b;
  char c;
  char a;
} tipoCoisa;

typedef struct tipoCoisa2 {
  char c;
  long d;
  long b;
  char a;
} tipoCoisa2;

int main() {
  tipoCoisa x;
  tipoCoisa2 y;

  // note que sizeof pode ser usado tanto na variavel quanto no tipo dela
  // poderia colocar sizeof(tipoCoisa) no lugar de sizeof(x) que funcionaria
  // No meu computador, o os tipos abaixo vao dar 24 para o x e 32 para y
  // Teste no seu computador e procure saber mais buscando na web
  // Vao ver que voce pode até forcar o compilador a evitar, mas não vale a pena
  // porque gera custos pra tratar a falta de alinhamento
  // a melhor maneira de reduzir perdas de padding é ordenar os tipos numéricos
  // (mesmo que sejam vetores) do maior pro menor dentro da struct.

  printf("O tamanho de x na memória: %lu\n", sizeof(x));
  printf("O tamanho de y na memória: %lu\n", sizeof(y));
}
