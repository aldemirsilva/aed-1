#include <stdio.h>

int main() {
  unsigned char x;
  short y;
  int z;
  long k;

  x = 5;
  y = -3;
  z = 4;
  k = 455566677;

  printf(
      "valor de x -> %u \nvalor de y -> %d\nvalor de z -> %d\nvalor de k -> "
      "%ld\n",
      x, y, z, k);

  printf("tamanho de x na memória: %lu bytes\n", sizeof(x));

  printf("tamanho de y na memória: %lu bytes\n", sizeof(y));

  printf("tamanho de z na memória: %lu bytes\n", sizeof(z));

  for (x = 48; x <= 127; x++) {
    printf("%d  -> %c\n", x, x);
  }

  x = 'A';
  x = x + 32;
  printf("%c \n", x);

  // onde estao nossas variaveis ?
  printf("Endereco de x %p\n", &x);
  printf("Endereco de y %p\n", &y);
  printf("Endereco de z %p\n", &z);
  printf("Endereco de k %p\n", &k);
}
