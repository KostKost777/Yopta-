#ifndef PARSE_TREE_IN_ASM_FUNCS
#define PARSE_TREE_IN_ASM_FUNCS

#include "../Frontend/tree_funcs.h"
#include "../Frontend/dump_funcs.h"

extern const char* asm_file_name;

const int SIZE_OF_FRAME = 5;
const int MAX_PTR = 1000;

void ParseAsmTreeInAsmFile(Tree* tree, Node* node);

void ParseAsmFunc(Tree* tree, Node* node);

void ParseAsmOperator(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmAssigned(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmReturn(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmIn(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmOut(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmIf(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmWhile(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmIfElse(Tree* tree, Node* node, Lexeme* func_info);

void ParseAsmExpression(Tree* tree, Node* node, Lexeme* func_info);

void PrintNodeInAsmFile(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmBigger(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmEqual(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmNotEqual(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmLess(Tree* tree, Node* node, Lexeme* func_info);

bool IsInvalidNum(int mem_ptr);

Status ParseAsmNumber(Tree* tree, Node* node);

void ParseAsmEnd(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmAnd(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmOr(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmADD(Tree* tree, Node* node);

Status ParseAsmSUB(Tree* tree, Node* node);

Status ParseAsmMUL(Tree* tree, Node* node);

Status ParseAsmDIV(Tree* tree, Node* node);

Status ParseAsmPOW(Tree* tree, Node* node);

Status ParseAsmSQRT(Tree* tree, Node* node);

Status ParseAsmPARAM(Tree* tree, Node* node);

void ParseAsmDraw(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmOutVar(Tree* tree, Node* node, Lexeme* func_info);

Status ParseAsmInVar(Tree* tree, Node* node, Lexeme* func_info);

int GetMemPtrOfVar(Node* node, NameTable* name_table, size_t start_index);

size_t GetIndexOfFuncInNameTable(NameTable* name_table, Lexeme* func_info);

Status ParseAsmCallFunc(Tree* tree, Node* node, Lexeme* func_info);

void PrintFuncName(NameTable* name_table, Lexeme* func_info);

void ParseMain(Tree* tree, Node* node, Lexeme* main);

Lexeme GetMainLexeme();

#endif
