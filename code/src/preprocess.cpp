#include "preprocess.h"

#include <cstdio>
#include <cstring>
#include <map>

#include "globalOps.h"

using namespace std;

void preProcessCode(char* fileNameIn, char* fileNameOut) {
  FILE* inputFile;
  FILE* outputFile;
  int lineCount = 0;
  map<char*, int> equTable;
  bool skipNextLine = false;

  // Abre o arquivo a ser lido
  inputFile = fopen(fileNameIn, "r");
  if (inputFile == NULL) {
    printf("Arquivo de entrada %s nao pode ser lido!\n", fileNameIn);
    return;
  }

  // Cria o arquivo onde vai ser escrito o pre-processado
  outputFile = fopen(fileNameOut, "w");
  if (outputFile == NULL) {
    printf("Arquivo de saida %s nao pode ser criado!\n", fileNameOut);
    fclose(inputFile);
    return;
  }

  // Loop principal, que le de linha em linha
  while (!feof(inputFile)) {
    char line[MAX_LINE_SIZE];
    char* lineToken;
    char token1[MAX_TOKEN_SIZE];
    char token2[MAX_TOKEN_SIZE];
    char token3[MAX_TOKEN_SIZE];
    char token4[MAX_TOKEN_SIZE];
    int lineTokensAmount = 0;

    // Usado quando teve if falso na linha passada
    if (skipNextLine == true) {
      skipNextLine = false;
      strcpy(line, "");
      continue;
    }

    // Le a linha e pega no maximo 4 tokens
    fgets(line, MAX_LINE_SIZE, inputFile);
    printf("%s ", line);
    lineToken = strtok(line, WHITESPACE);

    while (lineToken != NULL) {
      // Ja mata qualquer token que comeca com comentario
      if (lineToken[0] == ';') {
        break;
      }

      // Pega sempre no maximo 4 tokens para trabalhar neles
      switch (lineTokensAmount) {
        case 0:
          strcpy(token1, lineToken);
          break;
        case 1:
          strcpy(token2, lineToken);
          break;
        case 2:
          strcpy(token3, lineToken);
          break;
        case 3:
          strcpy(token4, lineToken);
          break;
        default:
          break;
      }

      // Pega o proximo token
      lineToken = strtok(NULL, WHITESPACE);
      lineTokensAmount++;
    }

    // Guardo a quantidade de linhas lidas ate agora
    lineCount++;

    // Aqui eu checo quantos tokens apareceram na linha e mexo neles conforme, o
    // que eh um saco, mas se tem mais ou menos tokens em uma linha, pode ser
    // que funcione diferente zzzzzz
    switch (lineTokensAmount) {
      // Aqui achei linha em branco... xau xau bau bau
      case 0:
        printf("case 0\n");
        printf("\n");
        continue;

      // Aqui so mexo se tiver label
      case 1:
        printf("case 1   ");
        char token1LastChar;
        token1LastChar = token1[strlen(token1) - 1];

        if (token1LastChar == ':') {
          printf("if :   ");
          // Label sozinha agora vai ser alinhada
          fprintf(outputFile, "%s ", toupperString(token1));

        } else {
          printf("if not :   ");
          // So imprime a linha mesmo
          fprintf(outputFile, "%s\n", toupperString(token1));
        }

        break;

      // Aqui so mexo se tiver if ou label
      case 2:
        printf("case 2   ");
        if (strcmp(IF_STR, toupperString(token1)) == 0) {
          printf("if if   ");
          // Achei um if!
          map<char*, int>::iterator equFound;
          equFound = equTable.find(token2);

          if (equFound != equTable.end()) {
            if (equFound->second != 0) {
              skipNextLine = true;
            }
          }

        } else {
          printf("if not if   ");
          // So imprime a linha mesmo
          fprintf(outputFile, "%s ", toupperString(token1));
          fprintf(outputFile, "%s\n", toupperString(token2));
        }

        break;

      // Aqui so mexo se tiver equ ou label
      case 3:
        printf("case 3   ");
        if (strcmp(EQU_STR, toupperString(token2)) == 0) {
          printf("if equ   ");
          // Achei um equ!
          char equName[] = "";
          map<char*, int>::iterator equFound;
          strcpy(equName, token1);
          equName[strlen(equName) - 1] = '\0';

          equFound = equTable.find(equName);
          if (equFound == equTable.end()) {
            equTable.insert(pair<char*, int>(equName, atoi(token3)));
          } else {
            printf("Dois EQUs com o mesmo nome encontrados!\n");
            printf("Retornando com erro!\n");
            // TODO tipo de erro? Professor falou que nao tinha......
            fclose(outputFile);
            fclose(inputFile);
            return;
          }

        } else {
          printf("if not equ   ");
          // So imprime a linha mesmo
          fprintf(outputFile, "%s ", toupperString(token1));
          fprintf(outputFile, "%s ", toupperString(token2));
          fprintf(outputFile, "%s\n", toupperString(token3));
        }

        break;

      // Aqui so mexo se tiver label
      case 4:
        printf("case 4   ");
        // So imprime a linha mesmo
        fprintf(outputFile, "%s ", toupperString(token1));
        fprintf(outputFile, "%s ", toupperString(token2));
        fprintf(outputFile, "%s ", toupperString(token3));
        fprintf(outputFile, "%s\n", toupperString(token4));

        break;

      default:
        printf("Nunca era nem para entrar aqui......... huh?\n");
        return;
    }
    printf("\n");
    printf("\n");
    strcpy(line, "");
  }

  fclose(outputFile);
  fclose(inputFile);
  printf("Sucesso!\n");
  printf("\n");
  return;
}
