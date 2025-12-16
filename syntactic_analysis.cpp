#include <TXLib.h>

#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "dump_funcs.h"
#include "tree_funcs.h"


Status MakeSyntacticAnalysis(Tree* tree, TokenArray* tokens)
{
    assert(tree);
    assert(tokens);

    size_t pos = 0;
    tree->root = GetGrammer(tokens, &pos, tree, tree->root);

    return success;
}

Node* GetGrammer(TokenArray* tokens, size_t* pos, Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>ВызовGetGeneral</strong>\n");

    node = GetAddSubOp(tokens, pos, tree, node);

    if (tokens->arr[*pos].type != END)
    {
        fprintf(log_file, "<strong>TokenArray во время ошибки: </strong>\n");
        PrintTokenArray(tokens);
    }

    return node;
}

Node* GetAddSubOp(TokenArray* tokens, size_t* pos, Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>Вызов GetAddSubOp</strong>\n");

    node = GetMulDivModOp(tokens, pos, tree, node);

    while (  tokens->arr[*pos].type == OP_ADD
          || tokens->arr[*pos].type == OP_SUB)
    {
        fprintf(log_file, "<strong>Обнаружил</strong>\n\n");

        Token op = tokens->arr[*pos];

        *pos += 1;

        node = NewNode(op, node,
                       GetMulDivModOp(tokens, pos, tree, node), tree);
    }

    return node;
}

Node* GetMulDivModOp(TokenArray* tokens, size_t* pos,
                     Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>ВызовGetMulDivModOp</strong>\n");

    node = GetPowOp(tokens, pos, tree, node);

    while (   tokens->arr[*pos].type == OP_MUL
           || tokens->arr[*pos].type == OP_DIV
           || tokens->arr[*pos].type == OP_MOD)
    {
        fprintf(log_file, "<strong>Обнаружил </strong>\n\n");

        Token op = tokens->arr[*pos];

        *pos += 1;

        node = NewNode(op, node,
                       GetPowOp(tokens, pos, tree, node), tree);
    }

    return node;
}

Node* GetPowOp(TokenArray* tokens, size_t* pos, Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>Вызов GetPowOp</strong>\n");

    node = GetMostPreority(tokens, pos, tree, node);

    while (tokens->arr[*pos].type == OP_POW)
    {
        Token op = tokens->arr[*pos];

        *pos += 1;

        node = NewNode(op, node,
                       GetMostPreority(tokens, pos, tree, node), tree);
    }

    return node;
}

Node* GetMostPreority(TokenArray* tokens, size_t* pos,
                      Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>Вызов GetMostPreority</strong>\n");

    if (tokens->arr[*pos].type == KEY_LPAREN)
    {
        fprintf(log_file, "<strong>Обнаружил\"(\": </strong>\n\n");
        *pos += 1;

        node = GetAddSubOp(tokens, pos, tree, node);

        if (tokens->arr[*pos].type == KEY_RPAREN)
        {
            *pos += 1;
            fprintf(log_file, "<strong>Обнаружил \")\"</strong>\n\n");
            return node;
        }

        fprintf(log_file, "<strong>Не обнаружил \")\"</strong>\n\n");
    }

    node = GetNumber(tokens, pos, tree);
    if (node != NULL)
    {
        *pos += 1;
        fprintf(log_file, "<strong>Нашел числа\n\n");
        return node;
    }

    node = GetWord(tokens, pos, tree, node);
    if (node != NULL)
    {
        fprintf(log_file, "<strong>Нашел слова</strong>\n\n");
        return node;
    }

    return NULL;
}

Node* GetNumber(TokenArray* tokens, size_t* pos, Tree* tree)
{
    fprintf(log_file, "<strong>Вызов GetNumber</strong>\n");

    if (tokens->arr[*pos].type == NUM)
    {
        fprintf(log_file, "<strong>Обнаружил число</strong>\n\n");
        return NewNode(tokens->arr[*pos], NULL, NULL, tree);
    }

    return NULL;
}

Node* GetWord(TokenArray* tokens, size_t* pos, Tree* tree, Node* node)
{
    fprintf(log_file, "<strong>Вызов GetWord</strong>\n");

//     node = GetFunction(tokens, pos, tree, node);
//
//     if (node != NULL)
//     {
//         fprintf(log_file, "<strong>Нашел функцию</strong>\n\n");
//         return node;
//     }

    node = GetIdentifier(tokens, pos, tree);

    if (node != NULL)
    {
        fprintf(log_file, "<strong>Нашел индификатор</strong>\n\n");
        return node;
    }

    return NULL;
}

Node* GetIdentifier(TokenArray* tokens, size_t* pos, Tree* tree)
{
    fprintf(log_file, "<strong>Вызов GetIdentifier</strong>\n");

    if (tokens->arr[*pos].type == IDENT)
    {
        fprintf(log_file, "<strong>Нашел индефикатор</strong>\n\n");
        return NewNode(tokens->arr[*pos], NULL, NULL, tree);
    }

    return NULL;
}
