#ifndef WOLFRAM_OP_FUNCS
#define WOLFRAM_OP_FUNCS

#include "../Frontend/lexical_analysis.h"
#include "../Frontend/tree_funcs.h"

struct ArgsValue
{
    int num1;
    int num2;
};

const int NUM_OF_OP = 5;

typedef int (*OpFuncPtr)(ArgsValue);

struct StructOperation
{
    const char* name;
    Type type;
    size_t hash;
    const OpFuncPtr op_func;
};

extern StructOperation all_op[];

//OP_FUNCS

StructOperation* GetStructOperationOfNode(Node* node);

int ADD_func(ArgsValue args_value);

int SUB_func(ArgsValue args_value);

int MUL_func(ArgsValue args_value);

int DIV_func(ArgsValue args_value);

int POW_func(ArgsValue args_value);

bool IsintEqual(int num1, int num2);

bool IsintBigger(int num1, int num2);

#endif
