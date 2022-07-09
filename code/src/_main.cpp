#include <cstdio>
#include <cstring>

#include "assembler.h"
#include "preprocess.h"

int main(int argc, char *argv[]) {
  char fileNameIn[30];
  char fileNameOut[30];
  char instruction[] = "-?";

  if (argc != 4) {
    printf("Comando errado!\n");
    printf(
        "Precisa de pelo menos 3 argumentos: a flag, o arquivo de entrada e o "
        "de saida!\n");
    printf("Exemplo: ./program.exe -o fileIn.asm fileOut.obj\n");
    printf("\n");
    printf("Flags aceitas:\n");
    printf("  -p para pre-processar\n");
    printf("  -o para montar\n");
    printf("\n");
    printf("Tente de novo.\n");
    printf("\n");
    return 0;
  }

  strcpy(instruction, argv[1]);
  strcpy(fileNameIn, argv[2]);
  strcpy(fileNameOut, argv[3]);

  if (strcmp(instruction, "-p") == 0) {
    preProcessCode(fileNameIn, fileNameOut);
  } else if (strcmp(instruction, "-o") == 0) {
    assembleCode(fileNameIn, fileNameOut);
  } else {
    printf("Flag invalida!\n");
    printf("\n");
    printf("Flags aceitas:\n");
    printf("  -p para pre-processar\n");
    printf("  -o para montar\n");
    printf("\n");
    printf("Exemplo: ./program.exe -o fileIn.asm fileOut.obj\n");
    printf("\n");
    printf("Tente de novo.\n");
    printf("\n");
  }

  return 0;
}
