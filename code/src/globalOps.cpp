#include "globalOps.h"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

int checkInstruction(char* token) {
  std::string Stoken(toupperString(token));

  if (Stoken == ADD_STR || Stoken == JMPP_STR || Stoken == SUB_STR ||
      Stoken == JMPZ_STR || Stoken == MUL_STR || Stoken == INPUT_STR ||
      Stoken == DIV_STR || Stoken == LOAD_STR || Stoken == JMP_STR ||
      Stoken == STORE_STR || Stoken == JMPN_STR || Stoken == OUTPUT_STR) {
    return 2;
  } else if (Stoken == COPY_STR) {
    return 3;
  } else if (Stoken == STOP_STR) {
    return 1;
  } else
    return -1;
}

char* toupperString(char* stringIn) {
  std::string Stoken(stringIn);
  for (auto& character : Stoken) {
    character = toupper(character);
  }

  char* auxString = new char[Stoken.length() + 1];
  strcpy(auxString, Stoken.c_str());
  return auxString;
}
