#include <TXLib.h>
#include <math.h>

#include "op_funcs.h"
#include "..\Frontend\dump_funcs.h"
#include "..\Frontend\hash_funcs.h"
#include "..\Frontend\tree_funcs.h"
#include "..\Frontend\lexical_analysis.h"

StructOperation all_op[NUM_OF_OP] =
{
{"+",      OP_ADD,     GetHash("+") ,      ADD_func},
{"-",      OP_SUB,     GetHash("-"),       SUB_func},
{"*",      OP_MUL,     GetHash("*"),       MUL_func},
{"/",      OP_DIV,     GetHash("/"),       DIV_func},
{"^",      OP_POW,     GetHash("^"),       POW_func}
};

StructOperation* GetStructOperationOfNode(Node* node)
{
    assert(node);

    for (size_t i = 0; i < NUM_OF_OP; ++i)
    {
        if (all_op[i].type == node->type)
            return &all_op[i];
    }

    //unreachebale
    assert(false);
    return NULL;
}

int ADD_func(ArgsValue args_value)
{
    return args_value.num1 + args_value.num2;
}

int SUB_func(ArgsValue args_value)
{
    return args_value.num1 - args_value.num2;
}

int MUL_func(ArgsValue args_value)
{
    return args_value.num1 * args_value.num2;
}

int DIV_func(ArgsValue args_value)
{

    if (args_value.num2 != 0)
        return args_value.num1 / args_value.num2;
    else
        fprintf(log_file, "Деление на ноль\n");

    return INT_MAX;
}

int POW_func(ArgsValue args_value)
{
    return (int)pow(args_value.num1, args_value.num2);
}


