#include <cstdio>
#include <cstring>

#include "assembler.h"
#include "preprocess.h"

int main(int argc, char *argv[]) {
  char fileName[30];
  char instruction[] = "-?";
  int fileNameSize;
  bool success = true;

  if (argc > 1 && (strcmp(argv[1], "-p") && strcmp(argv[1], "-o"))) {
    printf("Command to run this program was wrong.\n");
    printf("There must be exactly 3 fields in the command, ");
    printf("one being the command, then the flag, then the file's name.\n");
    printf("Example: ./main.exe -p file.asm\n");
    printf("\n");
    printf("Flags accepted:\n");
    printf("  -p to preprocess\n");
    printf("  -o to make the object.\n\n");
    printf("Try again\n");
    return 0;
  }

  strcpy(fileName, argv[2]);
  strcpy(instruction, argv[1]);

  if (strcmp(instruction, "-p") == 0) {
    // Ja mata aqui se o arquivo de entrada nao tiver a extensao .asm
    fileNameSize = strlen(fileName);
    if (fileName[fileNameSize - 3] != 'a' ||
        fileName[fileNameSize - 2] != 's' ||
        fileName[fileNameSize - 1] != 'm') {
      printf("File format was not asm!\n");
      success = false;
    }

    if (success == true) {
      success = preProcessCode(fileName);
      if (success == true) {
        printf("Success!\n");
      }
    }

  } else if (strcmp(instruction, "-o") == 0) {
    // Ja mata aqui se o arquivo de entrada nao tiver a extensao .asm
    fileNameSize = strlen(fileName);
    if (fileName[fileNameSize - 3] != 'a' ||
        fileName[fileNameSize - 2] != 's' ||
        fileName[fileNameSize - 1] != 'm') {
      printf("File format was not asm!\n");
      success = false;
    }

    if (success == true) {
      success = preProcessCode(fileName);
    }

    if (success == true) {
      fileName[fileNameSize - 3] = 'p';
      fileName[fileNameSize - 2] = 'r';
      fileName[fileNameSize - 1] = 'e';
      success = assembleCode(fileName);
      if (success == true) {
        printf("Success!\n");
      }
    }
  }

  return 0;
}
