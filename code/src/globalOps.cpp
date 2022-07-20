#include "globalOps.h"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

int checkInstruction(const char* token) {
  std::string stringToken(toUpperString(token));
  if (stringToken == ADD_STR || stringToken == JMPP_STR ||
      stringToken == SUB_STR || stringToken == JMPZ_STR ||
      stringToken == MUL_STR || stringToken == INPUT_STR ||
      stringToken == DIV_STR || stringToken == LOAD_STR ||
      stringToken == JMP_STR || stringToken == STORE_STR ||
      stringToken == JMPN_STR || stringToken == OUTPUT_STR) {
    return 2;
  } else if (stringToken == COPY_STR) {
    return 3;
  } else if (stringToken == STOP_STR) {
    return 1;
  } else
    return -1;
}

char* toUpperString(const char* stringIn) {
  std::string stringToken(stringIn);
  for (auto& character : stringToken) {
    character = toupper(character);
  }

  char* auxString = new char[stringToken.length() + 1];
  strcpy(auxString, stringToken.c_str());
  return auxString;
}
