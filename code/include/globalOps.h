#ifndef GLOBALVARS
#define GLOBALVARS

#define MAX_LINE_SIZE 400
#define WHITESPACE "\n\t "
#define MAX_TOKEN_SIZE 100

#define LEXIC_ERR_STR "Erro lexico"
#define SYNTACTIC_ERR_STR "Erro sintatico"
#define SEMANTIC_ERR_STR "Erro semantico"

#define SECTION_TEXT_STR "SECTION TEXT"
#define SECTION_DATA_STR "SECTION DATA"
#define SECAO_TEXTO_STR "SECAO TEXTO"
#define SECAO_DADOS_STR "SECAO DADOS"

#define BEGIN_STR "BEGIN"
#define END_STR "END"

#define EXTERN_STR "EXTERN"
#define PUBLIC_STR "PUBLIC"

#define MACRO_STR "MACRO"
#define ENDMACRO_STR "ENDMACRO"
#define IF_STR "IF"
#define EQU_STR "EQU"
#define SPACE_STR "SPACE"
#define CONST_STR "CONST"

#define ADD_STR "ADD"
#define SUB_STR "SUB"
#define MUL_STR "MULT"
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

int checkInstruction(const char*);
char* toUpperString(const char*);

#endif  // GLOBALVARS
