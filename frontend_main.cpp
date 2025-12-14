#include <TXLib.h>

#include "lexical_analysis.h"
#include "read_from_file_funcs.h"

const char* source_file_name = "source.txt";
void PrintTokenArray(TokenArray* tokens);

int main()
{
    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    TokenArray tokens = {};
    TokenArrayCtor(&tokens);

    MakeLexicalAnalysis(&buffer, &tokens);

    PrintTokenArray(&tokens);

    TokenArrayDtor(&tokens);
}

void PrintTokenArray(TokenArray* tokens)
{
    for (size_t i = 0; i < tokens->size; ++i)
    {
        printf("TOKEN[%llu]:\n", i);

        if (tokens->arr[i].type == NUM)
            printf("NUM NAME: |%d| ", tokens->arr[i].lexeme.num);

        else
            printf("(%d) NAME: |%s| ", tokens->arr[i].type, tokens->arr[i].lexeme.str.name);

        printf(" LINE: %llu COLUMN: %llu",
                                   tokens->arr[i].line,
                                   tokens->arr[i].column);

        printf("\n----------------------------\n\n");
    }
}

