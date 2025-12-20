#ifndef TREE_FUNCS
#define TREE_FUNCS

#include "lexical_analysis.h"
#include "name_table_funcs.h"

struct Node
{
    Type type;
    Lexeme lexeme;

    Node* parent;
    Node* left;
    Node* right;
};

struct Tree
{
    size_t size;
    int code_err;
    Node* root;

    bool is_draw;
    NameTable* name_table;
};

Status TreeCtor(Tree* tree);

Node* NodeCtor(Node* parent, Token* token);

void TreeDtor(Tree* tree);

void DeleteNode(Tree* tree, Node* node);

Node* NewNode(Token token, Node* left, Node* right, Tree* tree);


#endif
