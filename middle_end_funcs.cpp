#include <TXLib.h>

#include "middle_end_funcs.h"
#include "op_funcs.h"
#include "..\Frontend\tree_funcs.h"
#include "..\Frontend\lexical_analysis.h"

void OptimizeTree(Tree* tree)
{
    size_t old_size = 0;

    while(old_size != tree->size)
    {
       old_size = tree->size;

       OptimizeConstants(tree->root, tree);
       OptimizeNeutralElement(tree->root, tree);
    }
}

void OptimizeNeutralElement(Node* node, Tree* tree)
{
    assert(tree);

    if (node == NULL)
        return;

    if (node->type == OP_ADD)
        Optimize_ADD_NeutralElement(node, tree);

    else if (node->type == OP_SUB)
        Optimize_SUB_NeutralElement(node, tree);

    else if (node->type == OP_MUL)
        Optimize_MUL_NeutralElement(node, tree);

    else if (node->type == OP_DIV)
        Optimize_DIV_NeutralElement(node, tree);

    else if (node->type == OP_POW)
        Optimize_POW_NeutralElement(node, tree);

    if (node != NULL)
        OptimizeNeutralElement(node->left, tree);

    if (node != NULL)
        OptimizeNeutralElement(node->right, tree);
}

void Optimize_ADD_NeutralElement(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);
    bool status = true;

    SonNeutralOptimize(tree, node, node->right,  0, &status);
    SonNeutralOptimize(tree, node, node->left,  0, &status);
}

void Optimize_SUB_NeutralElement(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);
    bool status = true;

    SonNeutralOptimize(tree, node, node->right,  0, &status);
}

void Optimize_MUL_NeutralElement(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);
    bool status = true;

    SonNeutralOptimize(tree, node, node->right,  1, &status);
    SonNeutralOptimize(tree, node, node->left,  1, &status);

    AbsorbOptimize(tree, node, node->right, 0, 0, &status);
    AbsorbOptimize(tree, node, node->left, 0, 0, &status);
}

void Optimize_DIV_NeutralElement(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);
    bool status = true;

    SonNeutralOptimize(tree, node, node->right,  1,&status);

    AbsorbOptimize(tree, node, node->left, 0, 0, &status);
}

void Optimize_POW_NeutralElement(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);
    bool status = true;

    SonNeutralOptimize(tree, node, node->right,  1, &status);

    AbsorbOptimize(tree, node, node->right, 0, 1, &status);
}

int OptimizeConstants(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);

    if (node->type == NUM)
        return node->lexeme.num;

    if (node->type == IDENT)
        return INT_MAX;

    if (IsOp(node))
        ExecuteOperationWithConstants(node, tree);

    if (node->left != NULL)
        OptimizeConstants(node->left, tree);

    if (node->right != NULL)
        OptimizeConstants(node->right, tree);

    return INT_MAX;
}

void ExecuteOperationWithConstants(Node* node, Tree* tree)
{
    assert(tree);
    assert(node);

    StructOperation* now_op = GetStructOperationOfNode(node);

    int left_res = OptimizeConstants(node->left, tree);
    int right_res = OptimizeConstants(node->right, tree);

    if (left_res == INT_MAX || right_res == INT_MAX)
        return;

    free(node->left);
    free(node->right);

    node->left = NULL;
    node->right = NULL;

    tree->size -= 2;

    ArgsValue args_value = {left_res, right_res};

    node->type = NUM;
    node->lexeme.num = now_op->op_func(args_value);
}

void RemoveNeutralElement(Tree* tree, Node* node_parent, Node* neutral_node)
{
    assert(node_parent);
    assert(neutral_node);

    Node* node_second_son = NULL;

    if (neutral_node == node_parent->right)
        node_second_son = node_parent->left;
    else
        node_second_son = node_parent->right;

    if (node_parent->parent == NULL)
    {
        tree->root = node_second_son;
        node_second_son->parent = NULL;
    }

    else if (node_parent->parent->left == node_parent)
    {
        node_parent->parent->left = node_second_son;
        node_second_son->parent = node_parent->parent;
    }

    else
    {
        node_parent->parent->right = node_second_son;
        node_second_son->parent = node_parent->parent;
    }

    free(neutral_node);
    neutral_node = NULL;

    free(node_parent);
    node_parent = NULL;

    tree->size -= 2;
}

bool IsOp(Node* node)
{
    assert(node);

    Type type = node->type;

    return type == OP_ADD || type == OP_SUB || type == OP_MUL ||
           type == OP_DIV || type == OP_POW;

}

void SonNeutralOptimize(Tree* tree, Node* node,
                        Node* son,  int el, bool* status)
{
    assert(tree);

    if (node != NULL && *status && son!= NULL && son->type == NUM
        && son->lexeme.num == el)
    {                                                                                                           \
        if (son == node->right ) OptimizeNeutralElement(node->left, tree);
        if (son == node->left ) OptimizeNeutralElement(node->right, tree);
        RemoveNeutralElement(tree, node, son);
        *status = false;
    }
}

void AbsorbOptimize(Tree* tree, Node* node,
                    Node* son, int el, int new_el, bool* status)
{
    assert(tree);

    if (node != NULL && *status && son != NULL && son->type == NUM
            && son->lexeme.num == el)
    {
        DeleteNode(tree, node);
        node->type = NUM;
        node->lexeme.num = new_el;
        *status = false;
    }
}
