#ifndef GLOBALVARS
#define GLOBALVARS

#define MAX_LINE_SIZE 400
#define WHITESPACE "\n\t "
#define MAX_TOKEN_SIZE 100

#define MACRO_STR "MACRO"
#define ENDMACRO_STR "ENDMACRO"
#define IF_STR "IF"
#define EQU_STR "EQU"
#define SPACE_STR "SPACE"
#define CONST_STR "CONST"

#define MACRO_STR_LOW "macro"
#define ENDMACRO_STR_LOW "endmacro"
#define IF_STR_LOW "if"
#define EQU_STR_LOW "equ"
#define SPACE_STR_LOW "space"
#define CONST_STR_LOW "const"

#define ADD_STR "ADD"
#define SUB_STR "SUB"
#define MUL_STR "MUL"
#define DIV_STR "DIV"
#define JMP_STR "JMP"
#define JMPN_STR "JMPN"
#define JMPP_STR "JMPP"
#define JMPZ_STR "JMPZ"
#define COPY_STR "COPY"
#define LOAD_STR "LOAD"
#define STORE_STR "STORE"
#define INPUT_STR "INPUT"
#define OUTPUT_STR "OUTPUT"
#define STOP_STR "STOP"

#define ADD_STR_LOW "add"
#define SUB_STR_LOW "sub"
#define MUL_STR_LOW "mul"
#define DIV_STR_LOW "div"
#define JMP_STR_LOW "jmp"
#define JMPN_STR_LOW "jmpn"
#define JMPP_STR_LOW "jmpp"
#define JMPZ_STR_LOW "jmpz"
#define COPY_STR_LOW "copy"
#define LOAD_STR_LOW "load"
#define STORE_STR_LOW "store"
#define INPUT_STR_LOW "input"
#define OUTPUT_STR_LOW "output"
#define STOP_STR_LOW "stop"

#define ADD_OP 1
#define SUB_OP 2
#define MULT_OP 3
#define DIV_OP 4
#define JMP_OP 5
#define JMPN_OP 6
#define JMPP_OP 7
#define JMPZ_OP 8
#define COPY_OP 9
#define LOAD_OP 10
#define STORE_OP 11
#define INPUT_OP 12
#define OUTPUT_OP 13
#define STOP_OP 14

int checkInstruction(char*);

char* toupperString(char*);

#endif  // GLOBALVARS
