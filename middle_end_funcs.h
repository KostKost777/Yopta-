#ifndef MIDDLE_END_FUNCS
#define MIDDLE_END_FUNCS

#include "../Frontend/tree_funcs.h"

void OptimizeTree(Tree* tree);

void OptimizeNeutralElement(Node* node, Tree* tree);

void Optimize_ADD_NeutralElement(Node* node, Tree* tree);

void Optimize_SUB_NeutralElement(Node* node, Tree* tree);

void Optimize_MUL_NeutralElement(Node* node, Tree* tree);

void Optimize_DIV_NeutralElement(Node* node, Tree* tree);

void Optimize_POW_NeutralElement(Node* node, Tree* tree);

int OptimizeConstants(Node* node, Tree* tree);

void ExecuteOperationWithConstants(Node* node, Tree* tree);

void RemoveNeutralElement(Tree* tree, Node* node_parent, Node* neutral_node);

bool IsOp(Node* node);

void SonNeutralOptimize(Tree* tree, Node* node,
                        Node* son,  int el, bool* status);

void AbsorbOptimize(Tree* tree, Node* node,
                Node* son, int el, int new_el, bool* status);

#endif
