#include <TXLib.h>

#include "../Frontend/dump_funcs.h"
#include "../Frontend/tree_funcs.h"
#include "../Frontend/read_from_file_funcs.h"
#include "parse_tree_from_buffer_funcs.h"
#include "parse_tree_in_asm_funcs.h"

const char* source_file_name = "../Examples/outfile.txt";

int main (const int argc, const char** argv)
{
    atexit(CloseLogFile);
    OpenLogFile();

    if (argc > 1) source_file_name = argv[1];
    if (argc > 2) asm_file_name = argv[2];

    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    Tree tree = {};

    TreeCtor(&tree);

    char* cur_pos = buffer.data;
    tree.root = FillNodeDataFromBuffer(&cur_pos, &tree.size, tree.root);

    printf("BUFFER: %s", cur_pos);

    FillNameTableFromBuffer(tree.name_table, cur_pos);
    PrintNameTableInAsm(tree.name_table);

    TreeDump(&tree);

    ParseAsmTreeInAsmFile(&tree, tree.root);

    NameTableDtor(tree.name_table);
    TreeDtor(&tree);
    BufferDtor(&buffer);
}
