#include <TXLib.h>

#include "orig_lexicon_of_lang.h"
#include "lexical_analysis.h"
#include "hash_funcs.h"

BaseLexeme keywords_arr[NUM_OF_KEYWORDS] =
{
{KEY_IF,        "внатуре",  GetHash("внатуре")},    //if
{KEY_WHILE,     "потрещим", GetHash("потрещим")},  //while
{KEY_RETURN,    "шухер",    GetHash("шухер")},        //return
{KEY_INT,       "йопта",    GetHash("йопта")},        //int
{KEY_LPAREN,    "гыы",      GetHash("гыы")},          //(
{KEY_RPAREN,    "жыы",      GetHash("жыы")},       //)
{KEY_END_OP,    "наx",      GetHash("нах")},        //;
{KEY_LBRACE,    "гоп",      GetHash("гоп")},         // {
{KEY_RBRACE,    "стоп",     GetHash("стоп")},       // }
};

BaseLexeme operator_arr[NUM_OF_OPERATORS] =
{
{OP_ASSIGNED,        "=",    GetHash("=")},
{OP_EQUAL,           "==",   GetHash("==")},
{OP_LESS_OR_EQUAL,   "<=",   GetHash("<=")},
{OP_BIGGER_OR_EQUAL, ">=",   GetHash(">=")},
{OP_LESS,            "<",    GetHash("<")},
{OP_BIGGER,          ">",    GetHash(">")},
{OP_ADD,             "+",    GetHash("+")},
{OP_SUB,             "-",    GetHash("-")},
{OP_DIV,             "/",    GetHash("/")},
{OP_POW,             "^",    GetHash("^")},
{OP_MOD,             "%",    GetHash("%")},
};
