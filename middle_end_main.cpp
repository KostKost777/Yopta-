#include <TXLib.h>

#include "../Frontend/dump_funcs.h"
#include "../Frontend/tree_funcs.h"
#include "../Frontend/read_from_file_funcs.h"
#include "middle_end_funcs.h"
#include "op_funcs.h"
#include "../Backend/parse_tree_from_buffer_funcs.h"
#include "../Backend/basewords_backend.h"
#include "../Frontend/write_tree_in_file_funcs.h"
#include "../Frontend/name_table_funcs.h"
#include "../Frontend/hash_funcs.h"

const char* source_file_name = "../Examples/srcfile.txt";
const char* out_file_name = "../Examples/outfile.txt";

int main (const int argc, const char** argv)
{
    atexit(CloseLogFile);
    OpenLogFile();

    if (argc > 1) source_file_name = argv[1];
    if (argc > 2) out_file_name = argv[2];

    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    Tree tree = {};

    TreeCtor(&tree);

    char* cur_pos = buffer.data;
    tree.root = FillNodeDataFromBuffer(&cur_pos, &tree.size, tree.root);

    printf("BUFFER: %s", cur_pos);

    FillNameTableFromBuffer(tree.name_table, cur_pos);

    TreeDump(&tree);

    OptimizeTree(&tree);

    TreeDump(&tree);

    WriteTreeInFile(&tree, out_file_name);

    NameTableDtor(tree.name_table);
    TreeDtor(&tree);
    BufferDtor(&buffer);
}
