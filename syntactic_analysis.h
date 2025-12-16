#ifndef SYNTACTIC_ANALYSIS
#define SYNTACTIC_ANALYSIS

#include "tree_funcs.h"
#include "lexical_analysis.h"

Status MakeSyntacticAnalysis(Tree* tree, TokenArray* tokens);

Node* GetIdentifier(TokenArray* tokens, size_t* pos, Tree* tree);

Node* GetWord(TokenArray* tokens, size_t* pos, Tree* tree, Node* node);

Node* GetNumber(TokenArray* tokens, size_t* pos, Tree* tree);

Node* GetMostPreority(TokenArray* tokens, size_t* pos,
                      Tree* tree, Node* node);

Node* GetPowOp(TokenArray* tokens, size_t* pos, Tree* tree, Node* node);

Node* GetMulDivModOp(TokenArray* tokens, size_t* pos,
                     Tree* tree, Node* node);

Node* GetAddSubOp(TokenArray* tokens, size_t* pos, Tree* tree, Node* node);

Node* GetGrammer(TokenArray* tokens, size_t* pos, Tree* tree, Node* node);



#endif
