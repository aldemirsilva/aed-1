#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp, *fpOut;
  char byte;

  fp = fopen(argv[1], "r");
  fpOut = fopen(argv[2], "w");

  if (fp) {
    while (fread(&byte, 1, 1, fp)) {
      fwrite(&byte, 1, 1, fpOut);
    }
  }
}
