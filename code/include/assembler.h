#ifndef ASSEMBLER
#define ASSEMBLER

#include <string>

void assembleCode(char*, char*);
void printError(int, const std::string&, const std::string&);
bool checkLabel(const std::string&, int);
int getOpcode(const std::string&);

#endif  // ASSEMBLER
