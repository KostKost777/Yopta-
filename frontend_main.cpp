#include <TXLib.h>

#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "read_from_file_funcs.h"
#include "tree_funcs.h"
#include "dump_funcs.h"

const char* source_file_name = "source.txt";

int main()
{
    atexit(CloseLogFile);
    OpenLogFile();

    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    printf("BUFFER: %s \n", buffer.data);
    TokenArray tokens = {};
    TokenArrayCtor(&tokens);

    size_t pos = 0;

    MakeLexicalAnalysis(&buffer, &pos, &tokens);
    BufferDtor(&buffer);
    PrintTokenArray(&tokens);

    Tree tree = {};
    TreeCtor(&tree);

    MakeSyntacticAnalysis(&tree, &tokens);

    TreeDump(&tree);

    TokenArrayDtor(&tokens);
}
