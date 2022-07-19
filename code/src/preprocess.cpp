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
  map<string, int> equTable;
  bool skipNextLine = false;
  bool foundLabelAlone = false;
  bool isSuccess = true;

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

    // Le a linha e pega no maximo 4 tokens
    fgets(line, MAX_LINE_SIZE, inputFile);
    lineToken = strtok(line, WHITESPACE);

    // Vamos ver quantos tokens tem nessa linha
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

    // Usado quando teve if falso na linha passada
    if (skipNextLine == true) {
      if (lineTokensAmount != 0) {
        char token1LastChar;
        token1LastChar = token1[strlen(token1) - 1];
        if (lineTokensAmount == 1 && token1LastChar == ':') {
          if (foundLabelAlone == true) {
            // Se veio aqui, o codigo tava
            // IF LABEL1
            // LABEL2:
            // LABEL3:
            printf("Foram encontradas 2 labels uma depois da outra. Erro!\n");
            isSuccess = false;
          }
          foundLabelAlone = true;
          continue;
        }
        skipNextLine = false;
        continue;
      }
    }

    // Guardo a quantidade de linhas lidas ate agora
    lineCount++;

    // Aqui eu checo quantos tokens apareceram na linha e mexo neles conforme,
    // podendo haver 0 tokens (linha em branco) ate 4 tokens
    switch (lineTokensAmount) {
      // Aqui achei linha em branco... xau xau bau bau
      case 0:
        continue;

      // Aqui so mexo se tiver label
      case 1:
        char token1LastChar;
        token1LastChar = token1[strlen(token1) - 1];
        foundLabelAlone = false;

        if (token1LastChar == ':') {
          // Label sozinha agora vai ser alinhada
          fprintf(outputFile, "%s ", toupperString(token1));
          foundLabelAlone = true;

        } else {
          // Linha normal, entao so imprime a linha mesmo
          fprintf(outputFile, "%s\n", toupperString(token1));
        }

        break;

      // Aqui so mexo se tiver IF ou CONST
      case 2:
        foundLabelAlone = false;

        if (strcmp(IF_STR, toupperString(token1)) == 0) {
          // Achei um IF!
          map<string, int>::iterator equFound;
          string equString(toupperString(token2));
          equFound = equTable.find(equString);

          // Procuro aqui a label usada pelo IF na equTable
          if (equFound != equTable.end()) {
            if (equFound->second == 0) {
              skipNextLine = true;
            }
          } else {
            printf("Nao achei a label do IF. Erro!\n");
            isSuccess = false;
          }

        } else if (strcmp(CONST_STR, toupperString(token1)) == 0) {
          // Achei um const!
          char tokenName[MAX_TOKEN_SIZE];
          map<string, int>::iterator tokenFound;
          strcpy(tokenName, toupperString(token2));

          // Procuro aqui a label usada pelo CONST na equTable
          string tokenString(toupperString(tokenName));
          tokenFound = equTable.find(tokenString);
          if (tokenFound == equTable.end()) {
            // Nao achei na equTable, entao pode ser o numero direto
            fprintf(outputFile, "%s ", toupperString(token1));
            fprintf(outputFile, "%s\n", toupperString(token2));
          } else {
            // Achei na equTable, entao ja substitui
            fprintf(outputFile, "%s ", toupperString(token1));
            fprintf(outputFile, "%d\n", tokenFound->second);
          }
        } else {
          // Linha normal, entao so imprime a linha mesmo
          fprintf(outputFile, "%s ", toupperString(token1));
          fprintf(outputFile, "%s\n", toupperString(token2));
        }

        break;

      // Aqui so mexo se tiver EQU ou CONST
      case 3:
        foundLabelAlone = false;

        if (strcmp(EQU_STR, toupperString(token2)) == 0) {
          // Achei um EQU!
          char equName[MAX_TOKEN_SIZE];
          map<string, int>::iterator equFound;
          strcpy(equName, toupperString(token1));
          equName[strlen(equName) - 1] = '\0';

          // Aqui procuro a label usada no EQU na equTable, esperando nao achar
          string equString(toupperString(equName));
          equFound = equTable.find(equString);
          if (equFound == equTable.end()) {
            equTable.insert(pair<char*, int>(equName, atoi(token3)));
          } else {
            printf("Dois EQUs com o mesmo nome encontrados. Erro!\n");
            isSuccess = false;
          }

        } else if (strcmp(CONST_STR, toupperString(token2)) == 0) {
          // Achei um CONST!
          char tokenName[MAX_TOKEN_SIZE];
          map<string, int>::iterator tokenFound;
          strcpy(tokenName, toupperString(token3));

          // Procuro aqui a label usada pelo CONST na equTable
          string tokenString(toupperString(tokenName));
          tokenFound = equTable.find(tokenString);
          if (tokenFound == equTable.end()) {
            // Nao achei na equTable, entao pode ser o numero direto
            fprintf(outputFile, "%s ", toupperString(token1));
            fprintf(outputFile, "%s ", toupperString(token2));
            fprintf(outputFile, "%s\n", toupperString(token3));
          } else {
            // Achei na equTable, entao ja substitui
            fprintf(outputFile, "%s ", toupperString(token1));
            fprintf(outputFile, "%s ", toupperString(token2));
            fprintf(outputFile, "%d\n", tokenFound->second);
          }
        } else {
          // Linha normal, entao so imprime a linha mesmo
          fprintf(outputFile, "%s ", toupperString(token1));
          fprintf(outputFile, "%s ", toupperString(token2));
          fprintf(outputFile, "%s\n", toupperString(token3));
        }

        break;

      // Aqui so imprime a linha mesmo
      case 4:
        // Linha normal, entao so imprime a linha mesmo
        fprintf(outputFile, "%s ", toupperString(token1));
        fprintf(outputFile, "%s ", toupperString(token2));
        fprintf(outputFile, "%s ", toupperString(token3));
        fprintf(outputFile, "%s\n", toupperString(token4));

        foundLabelAlone = false;
        break;

      // O maximo de tokens era 4, entao algo deu errado...
      default:
        printf("Nunca era nem para entrar aqui......... huh?\n");
        isSuccess = false;
    }
    strcpy(line, "");
  }

  fclose(outputFile);
  fclose(inputFile);
  if (isSuccess == true) {
    printf("Pre-processamento terminado com sucesso!\n\n");
  } else {
    printf("Pre-processamento terminado com erro(s)!\n\n");
  }
  return;
}
