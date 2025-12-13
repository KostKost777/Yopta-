#ifndef LEXICAL_ANALYSIS
#define LEXICAL_ANALYSIS

#include "read_from_file_funcs.h"

const int NUM_OF_KEYWORDS = 9;

const int NUM_OF_OPERATORS = 11;

const int DEFAULT_TOKEN_ARR_SIZE = 100;

const int MAX_LEN_OF_WORD = 100;

enum Status
{
    success,
    error
};

enum Type
{
    KEY,
    OP,
    IDENT,
    NUM,
};

struct String
{
    char* name;
    size_t hash;
};

union Lexeme
{
    int num;
    String str;
};

struct Token
{
    Type type;
    Lexeme lexeme;
    size_t line;
    size_t column;
};

struct TokenArray
{
    Token* arr;
    size_t size;
};

void TokenArrayCtor(TokenArray* tokens);

void TokenArrayDtor(TokenArray* tokens);

void MakeLexicalAnalysis(Buffer* buffer, TokenArray* tokens);

void MoveBufferPointer(Buffer* buffer, size_t offset);

Status ParseKeyWord(Buffer* buffer, TokenArray* tokens);

Status ParseNumber(Buffer* buffer, TokenArray* tokens);

Status ParseIdentifier(Buffer* buffer, TokenArray* tokens);

Status ParseOperator(Buffer* buffer, TokenArray* tokens);

int GetSignOfNumber(Buffer* buffer);

void AddNumToken(TokenArray* tokens, Buffer* buffer,
                 Type type, int num);

void AddStringToken(TokenArray* tokens, Buffer* buffer,
                    Type type, char* str);

void SkipSpaces(Buffer* buffer);

bool IsRussianAlpha(char sym);

#endif
