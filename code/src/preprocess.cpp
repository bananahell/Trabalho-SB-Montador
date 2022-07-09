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
    bool skipLineBecauseComment = false;

    // Usado quando teve if falso na linha passada
    if (skipNextLine == true) {
      skipNextLine = false;
      continue;
    }

    // Le a linha e pega no maximo 4 tokens
    fgets(line, MAX_LINE_SIZE, inputFile);
    lineToken = strtok(line, WHITESPACE);
    while (lineToken != NULL) {
      // Ja mata qualquer token que comeca com comentario
      if (lineToken[0] == ';') {
        break;
      }
      // Aqui mata token que tem comentario no meio, tipo to;ken
      char* commentChar = strchr(lineToken, ';');
      if (commentChar != NULL) {
        lineToken[commentChar - lineToken] = '\0';
        skipLineBecauseComment = true;
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

      // Achou token com comentario no meio, tipo to;ken
      if (skipLineBecauseComment == true) {
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
        continue;

      // Aqui so mexo se tiver label
      case 1:
        char token1LastChar;
        token1LastChar = token1[(sizeof(token1) / sizeof(token1[0])) - 1];

        if (token1LastChar == ':') {
          // Label sozinha agora vai ser alinhada
          fprintf(outputFile, toupperString(token1));
          fprintf(outputFile, " ");

        } else {
          // So imprime a linha mesmo
          fprintf(outputFile, toupperString(token1));
          fprintf(outputFile, "\n");
        }

        break;

      // Aqui so mexo se tiver if ou label
      case 2:
        if (strcmp(IF_STR, toupperString(token1)) == 0) {
          // Achei um if!
          map<char*, int>::iterator equFound;
          equFound = equTable.find(token2);

          if (equFound != equTable.end()) {
            if (equFound->second != 0) {
              skipNextLine = true;
            }
          }

        } else {
          // So imprime a linha mesmo
          fprintf(outputFile, toupperString(token1));
          fprintf(outputFile, " ");
          fprintf(outputFile, toupperString(token2));
          fprintf(outputFile, "\n");
        }

        break;

      // Aqui so mexo se tiver equ ou label
      case 3:
        if (strcmp(EQU_STR, toupperString(token2)) == 0) {
          // Achei um equ!
          char* equName;
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
          // So imprime a linha mesmo
          fprintf(outputFile, toupperString(token1));
          fprintf(outputFile, " ");
          fprintf(outputFile, toupperString(token2));
          fprintf(outputFile, " ");
          fprintf(outputFile, toupperString(token3));
          fprintf(outputFile, "\n");
        }

        break;

      // Aqui so mexo se tiver label
      case 4:
        // So imprime a linha mesmo
        fprintf(outputFile, toupperString(token1));
        fprintf(outputFile, " ");
        fprintf(outputFile, toupperString(token2));
        fprintf(outputFile, " ");
        fprintf(outputFile, toupperString(token3));
        fprintf(outputFile, " ");
        fprintf(outputFile, toupperString(token4));
        fprintf(outputFile, "\n");

        break;

      default:
        printf("Nunca era nem para entrar aqui......... huh?\n");
        return;
    }
  }

  fclose(outputFile);
  fclose(inputFile);
  printf("Sucesso!\n");
  printf("\n");
  return;
}
