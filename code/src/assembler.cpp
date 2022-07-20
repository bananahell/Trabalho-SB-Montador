#include "assembler.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "globalOps.h"

using namespace std;

void assembleCode(char* fileNameIn, char* fileNameOut) {
  bool isSuccess = true;
  string line;
  vector<string> tokenVector;
  int lineCount = 0;
  int addrCount = 0;
  map<string, int> symbolTable;
  map<string, vector<int>> useTable;
  vector<string> defTable;
  bool hasBegin = false;

  ifstream inputFile(fileNameIn, ifstream::in);
  if (inputFile.good() == false) {
    cout << "Arquivo de entrada " << fileNameIn << " nao pode ser lido!"
         << endl;
    return;
  }

  while (getline(inputFile, line)) {
    istringstream stringStream(line);
    string token;
    tokenVector.clear();
    lineCount++;

    while (stringStream >> token) {
      tokenVector.push_back(token);
    }
    switch (tokenVector.size()) {
      case 1:
        if (tokenVector.at(0) == STOP_STR) {
          addrCount += 1;
        } else if (tokenVector.at(0) != END_STR) {
          // Linha de 1 token nao STOP ou END nao existe
          printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
          isSuccess = false;
        }
        break;
      case 2:
        if (tokenVector.at(0).back() == ':') {
          map<string, int>::iterator tokenFoundSymbol;
          map<string, vector<int>>::iterator tokenFoundUse;
          string label;
          tokenVector.at(0).pop_back();
          label = tokenVector.at(0);

          if (checkLabel(label, lineCount) == false) {
            isSuccess = false;
          }

          tokenFoundSymbol = symbolTable.find(label);
          if (tokenFoundSymbol != symbolTable.end()) {
            printError(lineCount, "Redefinicao de label!", SEMANTIC_ERR_STR);
            isSuccess = false;
          }
          tokenFoundUse = useTable.find(label);
          if (tokenFoundUse != useTable.end()) {
            printError(lineCount, "Redefinicao de label!", SEMANTIC_ERR_STR);
            isSuccess = false;
          }

          if (tokenVector.at(1) == EXTERN_STR) {
            vector<int> addressVector;
            useTable.insert(pair<string, vector<int>>(label, addressVector));
          } else {
            symbolTable.insert(pair<string, int>(label, addrCount));
          }

          if (tokenVector.at(1) == STOP_STR || tokenVector.at(1) == SPACE_STR) {
            addrCount += 1;
          } else if (tokenVector.at(1) == BEGIN_STR) {
            hasBegin = true;
          } else if (tokenVector.at(1) != EXTERN_STR) {
            // Nesse if, so pode ter STOP com label, nao sei o que eh isso
            printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
            isSuccess = false;
          }
        } else if (tokenVector.at(0) == PUBLIC_STR) {
          defTable.push_back(tokenVector.at(1));
        } else if (checkInstruction(tokenVector.at(0).c_str()) == 2) {
          for (auto& x : useTable) {
            if (x.first == tokenVector.at(1)) {
              x.second.push_back(addrCount + 1);
            }
          }
          addrCount += 2;
        } else if (line != SECAO_TEXTO_STR && line != SECAO_DADOS_STR &&
                   line != SECTION_TEXT_STR && line != SECTION_DATA_STR) {
          // Linha de 2 tokens sem label no comeco so pode ser instrucao
          // ou diretiva
          printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
          isSuccess = false;
        }
        break;
      case 3:
        if (tokenVector.at(0).back() == ':') {
          map<string, int>::iterator tokenFound;
          string label;
          tokenVector.at(0).pop_back();
          label = tokenVector.at(0);

          // Vou procurar a label na symbolTable esperando nao achar
          tokenFound = symbolTable.find(label);
          if (tokenFound == symbolTable.end()) {
            // Checa e insere a label
            if (checkLabel(label, lineCount) == false) {
              isSuccess = false;
            }
            symbolTable.insert(pair<string, int>(label, addrCount));
          } else {
            printError(lineCount, "Redefinicao de label!", SEMANTIC_ERR_STR);
            isSuccess = false;
          }
          if (tokenVector.at(1) == CONST_STR) {
            addrCount += 1;
          } else if (checkInstruction(tokenVector.at(1).c_str()) == 2) {
            for (auto& x : useTable) {
              if (x.first == tokenVector.at(2)) {
                x.second.push_back(addrCount + 1);
              }
            }
            addrCount += 2;
          } else {
            // Nesse if, so pode ter CONST com label, nao sei o que eh isso
            printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
            isSuccess = false;
          }
        } else if (tokenVector.at(0) == COPY_STR) {
          for (auto& x : useTable) {
            if (x.first == tokenVector.at(1)) {
              x.second.push_back(addrCount + 1);
            } else if (x.first == tokenVector.at(2)) {
              x.second.push_back(addrCount + 2);
            }
          }
          addrCount += 3;
        } else {
          // Linha de 3 tokens sem label no comeco so pode ser COPY
          printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
          isSuccess = false;
        }
        break;
      case 4:
        if (tokenVector.at(0).back() == ':') {
          map<string, int>::iterator tokenFound;
          string label;
          tokenVector.at(0).pop_back();
          label = tokenVector.at(0);

          // Vou procurar a label na symbolTable esperando nao achar
          tokenFound = symbolTable.find(label);
          if (tokenFound == symbolTable.end()) {
            // Checa e insere a label
            if (checkLabel(label, lineCount) == false) {
              isSuccess = false;
            }
            symbolTable.insert(pair<string, int>(label, addrCount));
          } else {
            printError(lineCount, "Redefinicao de label!", SEMANTIC_ERR_STR);
            isSuccess = false;
          }
          if (tokenVector.at(1) == COPY_STR) {
            addrCount += 3;
          } else {
            // Nesse case, so pode ter COPY com label, nao sei o que eh isso
            printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
            isSuccess = false;
          }
        } else {
          // Linha de 4 tokens sem label no comeco nao existe
          printError(lineCount, "Instrucao desconhecida!", SYNTACTIC_ERR_STR);
          isSuccess = false;
        }
        break;
      default:
        printError(lineCount, "Mais que 4 tokens!", SYNTACTIC_ERR_STR);
        isSuccess = false;
        break;
    }
  }

  cout << endl << "Symbol Table:" << endl;
  for (auto& x : symbolTable) {
    cout << x.first << " : " << x.second << endl;
  }
  cout << endl << "Use Table:" << endl;
  for (auto& x : useTable) {
    cout << x.first << " ";
    for (unsigned i = 0; i < x.second.size(); i++) {
      cout << x.second.at(i) << " ";
    }
    cout << endl;
  }
  cout << endl << "Def Table:" << endl;
  for (unsigned i = 0; i < defTable.size(); i++) {
    cout << defTable.at(i) << endl;
  }

  inputFile.close();
  inputFile.open(fileNameIn, ifstream::in);
  if (inputFile.good() == false) {
    cout << "Arquivo de entrada " << fileNameIn << " nao pode ser lido!"
         << endl;
    return;
  }

  ofstream outputFile(fileNameOut, ofstream::out);
  if (outputFile.good() == false) {
    cout << "Arquivo de saida " << fileNameOut << " nao pode ser criado!"
         << endl;
    inputFile.close();
    return;
  }

  lineCount = 0;
  addrCount = 0;
  map<string, int>::iterator tokenFound;
  map<string, vector<int>>::iterator tokenFoundUse;

  if (hasBegin == true) {
    outputFile << "TABELA USO" << endl;
    for (auto& x : useTable) {
      outputFile << x.first << " ";
      for (unsigned i = 0; i < x.second.size(); i++) {
        outputFile << x.second.at(i) << " ";
      }
      outputFile << endl;
    }
    outputFile << endl;
    outputFile << "TABELA DEF" << endl;
    for (unsigned i = 0; i < defTable.size(); i++) {
      outputFile << defTable.at(i) << " ";
      for (auto& x : symbolTable) {
        if (x.first == defTable.at(i)) {
          outputFile << x.second << endl;
          break;
        }
      }
    }
    outputFile << endl;
  }

  while (getline(inputFile, line)) {
    istringstream stringStream(line);
    string token;
    tokenVector.clear();
    lineCount++;

    while (stringStream >> token) {
      tokenVector.push_back(token);
    }
    switch (tokenVector.size()) {
      case 1:
        if (tokenVector.at(0) == STOP_STR) {
          outputFile << getOpcode(tokenVector.at(0)) << " ";
        }
        break;
      case 2:
        if (tokenVector.at(0).back() == ':') {
          if (tokenVector.at(1) == STOP_STR) {
            outputFile << STOP_OP << " ";
          } else if (tokenVector.at(1) == SPACE_STR) {
            outputFile << "0 ";
          }
        } else if (checkInstruction(tokenVector.at(0).c_str()) == 2) {
          outputFile << getOpcode(tokenVector.at(0)) << " ";
          tokenFound = symbolTable.find(tokenVector.at(1));
          if (checkLabel(tokenVector.at(1), lineCount) == true) {
            if (tokenFound == symbolTable.end()) {
              tokenFoundUse = useTable.find(tokenVector.at(1));
              if (tokenFoundUse == useTable.end()) {
                printError(lineCount, "Label nao definida!", SEMANTIC_ERR_STR);
                isSuccess = false;
                outputFile << tokenVector.at(1) << " ";
              } else {
                outputFile << "0 ";
              }
            } else {
              outputFile << symbolTable.find(tokenVector.at(1))->second << " ";
            }
          } else {
            isSuccess = false;
          }
        }
        break;
      case 3:
        if (tokenVector.at(0).back() == ':') {
          if (checkInstruction(tokenVector.at(1).c_str()) == 2) {
            outputFile << getOpcode(tokenVector.at(1)) << " ";
            tokenFound = symbolTable.find(tokenVector.at(2));
            if (checkLabel(tokenVector.at(2), lineCount) == true) {
              if (tokenFound == symbolTable.end()) {
                tokenFoundUse = useTable.find(tokenVector.at(2));
                if (tokenFoundUse == useTable.end()) {
                  printError(lineCount, "Label nao definida!",
                             SEMANTIC_ERR_STR);
                  isSuccess = false;
                  outputFile << tokenVector.at(2) << " ";
                } else {
                  outputFile << "0 ";
                }
              } else {
                outputFile << symbolTable.find(tokenVector.at(2))->second
                           << " ";
              }
            } else {
              isSuccess = false;
            }
          } else if (tokenVector.at(1) == CONST_STR) {
            outputFile << tokenVector.at(2) << " ";
          }
        } else if (tokenVector.at(0) == COPY_STR) {
          outputFile << getOpcode(tokenVector.at(0)) << " ";
          tokenFound = symbolTable.find(tokenVector.at(1));
          if (checkLabel(tokenVector.at(1), lineCount) == true) {
            if (tokenFound == symbolTable.end()) {
              printError(lineCount, "Label nao definida!", SEMANTIC_ERR_STR);
              isSuccess = false;
              outputFile << tokenVector.at(1) << " ";
            } else {
              outputFile << symbolTable.find(tokenVector.at(1))->second << " ";
            }
          } else {
            isSuccess = false;
          }
          tokenFound = symbolTable.find(tokenVector.at(2));
          if (checkLabel(tokenVector.at(2), lineCount) == true) {
            if (tokenFound == symbolTable.end()) {
              printError(lineCount, "Label nao definida!", SEMANTIC_ERR_STR);
              isSuccess = false;
              outputFile << tokenVector.at(2) << " ";
            } else {
              outputFile << symbolTable.find(tokenVector.at(2))->second << " ";
            }
          } else {
            isSuccess = false;
          }
        }
        break;
      case 4:
        outputFile << getOpcode(tokenVector.at(1)) << " ";
        tokenFound = symbolTable.find(tokenVector.at(2));
        if (checkLabel(tokenVector.at(2), lineCount) == true) {
          if (tokenFound == symbolTable.end()) {
            printError(lineCount, "Label nao definida!", SEMANTIC_ERR_STR);
            isSuccess = false;
            outputFile << tokenVector.at(2) << " ";
          } else {
            outputFile << symbolTable.find(tokenVector.at(2))->second << " ";
          }
        } else {
          isSuccess = false;
        }
        tokenFound = symbolTable.find(tokenVector.at(3));
        if (checkLabel(tokenVector.at(3), lineCount) == true) {
          if (tokenFound == symbolTable.end()) {
            printError(lineCount, "Label nao definida!", SEMANTIC_ERR_STR);
            isSuccess = false;
            outputFile << tokenVector.at(3) << " ";
          } else {
            outputFile << symbolTable.find(tokenVector.at(3))->second << " ";
          }
        } else {
          isSuccess = false;
        }
        break;
      default:
        printError(lineCount, "Mais que 4 tokens!", SYNTACTIC_ERR_STR);
        isSuccess = false;
        break;
    }
  }

  inputFile.close();
  outputFile.close();
  if (isSuccess == true) {
    cout << "Montagem terminada com sucesso!" << endl;
  } else {
    cout << "Montagem terminada com erro(s)!" << endl;
  }
  return;
}

int getOpcode(const string& instruction) {
  if (instruction == ADD_STR) {
    return ADD_OP;
  } else if (instruction == SUB_STR) {
    return SUB_OP;
  } else if (instruction == MUL_STR) {
    return MULT_OP;
  } else if (instruction == DIV_STR) {
    return DIV_OP;
  } else if (instruction == JMP_STR) {
    return JMP_OP;
  } else if (instruction == JMPN_STR) {
    return JMPN_OP;
  } else if (instruction == JMPP_STR) {
    return JMPP_OP;
  } else if (instruction == JMPZ_STR) {
    return JMPZ_OP;
  } else if (instruction == COPY_STR) {
    return COPY_OP;
  } else if (instruction == LOAD_STR) {
    return LOAD_OP;
  } else if (instruction == STORE_STR) {
    return STORE_OP;
  } else if (instruction == INPUT_STR) {
    return INPUT_OP;
  } else if (instruction == OUTPUT_STR) {
    return OUTPUT_OP;
  } else if (instruction == STOP_STR) {
    return STOP_OP;
  }
  return -1;
}

bool checkLabel(const string& label, int lineNumber) {
  if (label.at(0) >= '0' && label.at(0) <= '9') {
    printError(lineNumber, "Labels nao podem comecar com numero!",
               LEXIC_ERR_STR);
    return false;
  }
  for (unsigned i = 0; i < label.size(); i++) {
    if (!((label.at(i) >= 'A' && label.at(i) <= 'Z') ||
          (label.at(i) >= '0' && label.at(i) <= '9') || label.at(i) == '_')) {
      printError(lineNumber, "Labels devem ter so letras, numeros, ou '_'!",
                 LEXIC_ERR_STR);
      return false;
    }
  }
  return true;
}

void printError(int lineNumber, const string& errorMsg,
                const string& errorType) {
  cout << "Erro linha " << lineNumber << ":" << endl;
  cout << "  " << errorMsg << endl;
  cout << "  " << errorType << "!" << endl;
  cout << endl;
  return;
}
