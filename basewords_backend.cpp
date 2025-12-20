#include <TXLib.h>

#include "basewords_backend.h"
#include "../Frontend/lexical_analysis.h"
#include "../Frontend/hash_funcs.h"

BaseWord basewords_arr[NUM_OF_BASEWORDS] =
{
{KEY_IF,             "if",         GetHash("if")},    //if
{PARAM,              "PARAM",      GetHash("PARAM")},
{KEY_ELSE,           "else",       GetHash("else")},    //else
{KEY_WHILE,          "while",      GetHash("while")},           //while
{KEY_RETURN,         "return",     GetHash("return")},        //return
{KEY_INT,            "int",        GetHash("int")},        //int
{KEY_SEMICOLON,      ";",          GetHash(";")},        //;
{KEY_LBRACE,         "{",          GetHash("{")},         // {
{KEY_LBRACE,         "}",          GetHash("}")},         // }
{KEY_OUT,            "out",        GetHash("out")},    // out
{KEY_IN,             "in",         GetHash("in")},  // in
{KEY_END,            "end",        GetHash("end")},  // end
{KEY_DRAW,           "draw",       GetHash("draw")},  // draw
{OP_ASSIGNED,        "=",          GetHash("=")},
{OP_EQUAL,           "==",         GetHash("==")},
{OP_NOT_EQUAL,       "!=",         GetHash("!=")},
{OP_LESS_OR_EQUAL,   "<=",         GetHash("<=")},
{OP_BIGGER_OR_EQUAL, ">=",         GetHash(">=")},
{OP_LESS,            "<",          GetHash("<")},
{OP_BIGGER,          ">",          GetHash(">")},
{OP_OR,              "||",         GetHash("||")},
{OP_AND,             "&&",         GetHash("&&")},
{OP_ADD,             "+",          GetHash("+")},
{OP_SUB,             "-",          GetHash("-")},
{OP_MUL,             "*",          GetHash("*")},
{OP_DIV,             "/",          GetHash("/")},
{OP_POW,             "^",          GetHash("^")},
{OP_MOD,             "%",          GetHash("%")},
{OP_SQRT,            "sqrt",       GetHash("sqrt")}
};
