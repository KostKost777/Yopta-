#include <TXLib.h>

#include "orig_lexicon_of_lang.h"
#include "lexical_analysis.h"
#include "hash_funcs.h"

#define KEY_DECL_(kwd, name)        \
{ KEY_##kwd, name, GetHash (name) },\
{ KEY_##kwd, #kwd, GetHash (#kwd) } \

#define OP_DECL_(op, name)            \
{ OP_##op, name, GetHash (name) },    \
{ OP_##op, #op, GetHash (#op) }       \


BaseLexeme keywords_arr[] =
{
KEY_DECL_(IF,        "вилкойвглаз"),    //if
KEY_DECL_(ELSE,      "иливжопураз"),    //else
KEY_DECL_(WHILE,     "потрещим"),      //while
KEY_DECL_(WHILE,     "побазарим"),           //while
KEY_DECL_(RETURN,    "шухер"),        //return
KEY_DECL_(INT,       "братуха"),        //int
KEY_DECL_(INT,       "кент"),        //int
KEY_DECL_(LPAREN,    "гыы"),        //int
KEY_DECL_(LPAREN,    "хыы"),        //int
KEY_DECL_(LPAREN,    "хаха"),        //int
KEY_DECL_(RPAREN,    "жыы"),        //int
KEY_DECL_(RPAREN,    "ыыы"),        //int
KEY_DECL_(SEMICOLON, "нах"),        //int
KEY_DECL_(LBRACE,    "гоп"),        //int
KEY_DECL_(RBRACE,    "cтоп"),        //int
KEY_DECL_(COMMA,     ","),        //int
KEY_DECL_(OUT,       "малевать"),        //int
KEY_DECL_(IN,        "вечервхату"),        //int
KEY_DECL_(DRAW,      "рисовать"),        //int
KEY_DECL_(END,       "откинуться")        //int
};

BaseLexeme operator_arr[] =
{
OP_DECL_(ASSIGNED,            "="),
OP_DECL_(EQUAL,               "=="),
OP_DECL_(NOT_EQUAL,           "!="),
OP_DECL_(LESS_OR_EQUAL,      "<="),
OP_DECL_(BIGGER_OR_EQUAL,     ">="),
OP_DECL_(LESS,                "<"),
OP_DECL_(BIGGER,              "<"),
OP_DECL_(OR,                  "||"),
OP_DECL_(AND,                 "&&"),
OP_DECL_(ADD,                 "+"),
OP_DECL_(SUB,                 "-"),
OP_DECL_(MUL,                 "*"),
OP_DECL_(DIV,                 "/"),
OP_DECL_(POW,                 "^"),
OP_DECL_(MOD,                 "%"),
OP_DECL_(SQRT,                "sqrt")
};
