#include "globalOps.h"

#include <cstring>

bool checkIfInstruction(char* token) {
  if (strcmp(token, ADD_STR) == 0 || strcmp(token, ADD_STR_LOW) == 0 ||
      strcmp(token, SUB_STR) == 0 || strcmp(token, SUB_STR_LOW) == 0 ||
      strcmp(token, MUL_STR) == 0 || strcmp(token, MUL_STR_LOW) == 0 ||
      strcmp(token, DIV_STR) == 0 || strcmp(token, DIV_STR_LOW) == 0 ||
      strcmp(token, JMP_STR) == 0 || strcmp(token, JMP_STR_LOW) == 0 ||
      strcmp(token, JMPN_STR) == 0 || strcmp(token, JMPN_STR_LOW) == 0 ||
      strcmp(token, JMPP_STR) == 0 || strcmp(token, JMPP_STR_LOW) == 0 ||
      strcmp(token, JMPZ_STR) == 0 || strcmp(token, JMPZ_STR_LOW) == 0 ||
      strcmp(token, COPY_STR) == 0 || strcmp(token, COPY_STR_LOW) == 0 ||
      strcmp(token, LOAD_STR) == 0 || strcmp(token, LOAD_STR_LOW) == 0 ||
      strcmp(token, STORE_STR) == 0 || strcmp(token, STORE_STR_LOW) == 0 ||
      strcmp(token, INPUT_STR) == 0 || strcmp(token, INPUT_STR_LOW) == 0 ||
      strcmp(token, OUTPUT_STR) == 0 || strcmp(token, OUTPUT_STR_LOW) == 0 ||
      strcmp(token, STOP_STR) == 0 || strcmp(token, STOP_STR_LOW) == 0) {
    return true;
  }
  return false;
}

bool checkIfInstructionOf2Ops(char* token) {
  if (strcmp(token, ADD_STR) == 0 || strcmp(token, ADD_STR_LOW) == 0 ||
      strcmp(token, SUB_STR) == 0 || strcmp(token, SUB_STR_LOW) == 0 ||
      strcmp(token, MUL_STR) == 0 || strcmp(token, MUL_STR_LOW) == 0 ||
      strcmp(token, DIV_STR) == 0 || strcmp(token, DIV_STR_LOW) == 0 ||
      strcmp(token, JMP_STR) == 0 || strcmp(token, JMP_STR_LOW) == 0 ||
      strcmp(token, JMPN_STR) == 0 || strcmp(token, JMPN_STR_LOW) == 0 ||
      strcmp(token, JMPP_STR) == 0 || strcmp(token, JMPP_STR_LOW) == 0 ||
      strcmp(token, JMPZ_STR) == 0 || strcmp(token, JMPZ_STR_LOW) == 0 ||
      strcmp(token, LOAD_STR) == 0 || strcmp(token, LOAD_STR_LOW) == 0 ||
      strcmp(token, STORE_STR) == 0 || strcmp(token, STORE_STR_LOW) == 0 ||
      strcmp(token, INPUT_STR) == 0 || strcmp(token, INPUT_STR_LOW) == 0 ||
      strcmp(token, OUTPUT_STR) == 0 || strcmp(token, OUTPUT_STR_LOW) == 0) {
    return true;
  }
  return false;
}
