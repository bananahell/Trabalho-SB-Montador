#include "preprocess.h"

#include <cstdio>
#include <cstring>

#include "globalOps.h"

bool preProcessCode(char* fileName) {
  FILE* inputFile;
  FILE* outputFile;
  int lineCount = 0;

  // Abre o arquivo a ser lido
  inputFile = fopen(fileName, "r");
  if (inputFile == NULL) {
    printf("Input file %s could not be read.\n", fileName);
    return false;
  }

  // Cria o arquivo onde vai ser escrito o pre-processado
  outputFile = fopen(fileName, "w");
  if (outputFile == NULL) {
    printf("Output file could not be created.\n");
    fclose(inputFile);
    return false;
  }

  while (!feof(inputFile)) {
    char line[MAX_LINE_SIZE];
    char* lineTokens;
    char token1[MAX_TOKEN_SIZE];
    char token2[MAX_TOKEN_SIZE];
    char token3[MAX_TOKEN_SIZE];
    char token4[MAX_TOKEN_SIZE];
    int lineTokensAmount = 0;
    char tokenLastChar;

    // Le a linha e pega no maximo 4 tokens
    fgets(line, MAX_LINE_SIZE, inputFile);
    lineTokens = strtok(line, WHITESPACE);
    while (lineTokens != NULL) {
      switch (lineTokensAmount) {
        case 0:
          strcpy(token1, lineTokens);
          break;
        case 1:
          strcpy(token2, lineTokens);
          break;
        case 2:
          strcpy(token3, lineTokens);
          break;
        case 3:
          strcpy(token4, lineTokens);
          break;
        default:
          break;
      }
      lineTokens = strtok(NULL, WHITESPACE);
      lineTokensAmount++;
    }

    // Guardo a quantidade de linhas lidas ate agora
    lineCount++;

    // Ja mata aqui linhas que sao so comentario
    if (token1 != NULL && token1[0] == ';') {
      continue;
    }

    if (lineTokensAmount > 0) {
      tokenLastChar = token1[(sizeof(token1) / sizeof(token1[0])) - 1];
    }

    // Aqui eu checo quantos tokens apareceram na linha e mexo neles conforme, o
    // que eh um saco, mas se tem mais ou menos tokens em uma linha, pode ser
    // que funcione diferente zzzzzz
    switch (lineTokensAmount) {
      // Aqui achei linha em branco... xau xau bau bau
      case 0:
        continue;

      // Aqui tem 1 token, entao eh label, stop, ou endmacro
      case 1:
        if (tokenLastChar == ':') {
          // TODO achei label!
        } else if (strcmp(token1, STOP_STR) == 0 ||
                   strcmp(token1, STOP_STR_LOW) == 0) {
          // TODO achei stop!
        } else if (strcmp(token1, ENDMACRO_STR) == 0 ||
                   strcmp(token1, ENDMACRO_STR_LOW) == 0) {
          // TODO achei endmacro!
        } else {
          // TODO aqui nao era pra chegar, filhao... instrucao errada ou if.....
        }
        break;

      // Aqui tem 2 tokens, entao eh label com stop, instrucao tamanho 2, if, ou
      // label com macro
      case 2:
        if (tokenLastChar == ':') {
          if (strcmp(token2, MACRO_STR) == 0 ||
              strcmp(token2, MACRO_STR_LOW) == 0) {
            // TODO achei macro!
          } else if (strcmp(token2, STOP_STR) == 0 ||
                     strcmp(token2, STOP_STR_LOW) == 0) {
            // TODO achei stop!
          } else {
            // TODO nao eh macro, nem stop.... eh erro
          }
        } else if (strcmp(token1, IF_STR) == 0 ||
                   strcmp(token1, IF_STR_LOW) == 0) {
          // TODO achei if!
        } else if (checkIfInstructionOf2Ops(token1) == true) {
          // TODO achou uma instrucao de dois operandos!
        } else {
          // TODO aqui nao era pra chegar, filhao... erro
        }
        break;

      // Aqui tem 3 tokens, entao eh label com instrucao tamanho 2, const,
      // space, ou copy
      case 3:
        if (tokenLastChar == ':') {
          if (checkIfInstructionOf2Ops(token2) == true) {
            // TODO achei label com instrucao de 2!
          } else {
            // TODO que instrucao eh essa, mane?
          }
        } else if (strcmp(token1, CONST_STR) == 0 ||
                   strcmp(token1, CONST_STR_LOW) == 0) {
          // TODO achei const!
        } else if (strcmp(token1, SPACE_STR) == 0 ||
                   strcmp(token1, SPACE_STR_LOW) == 0) {
          // TODO achei space!
        } else if (strcmp(token1, COPY_STR) == 0 ||
                   strcmp(token1, COPY_STR_LOW) == 0) {
          // TODO achei copy!
        } else {
          // TODO achou o que ai, filhao? erro eh o que tu achou
        }
        break;

      // Aqui tem 4 tokens, entao eh label com copy, const, ou space
      case 4:
        if (tokenLastChar == ':') {
          if (strcmp(token1, CONST_STR) == 0 ||
              strcmp(token1, CONST_STR_LOW) == 0) {
            // TODO achei const!
          } else if (strcmp(token1, SPACE_STR) == 0 ||
                     strcmp(token1, SPACE_STR_LOW) == 0) {
            // TODO achei space!
          } else if (strcmp(token1, COPY_STR) == 0 ||
                     strcmp(token1, COPY_STR_LOW) == 0) {
            // TODO achei copy!
          }
        } else {
          // TODO achou o que ai, filhao? erro eh o que tu achou
        }
        break;

      default:
        break;
    }
  }

  fclose(outputFile);
  fclose(inputFile);
  return true;
}
