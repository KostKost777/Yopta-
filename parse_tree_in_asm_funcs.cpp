#include <TXLib.h>

#include "parse_tree_in_asm_funcs.h"
#include "../Frontend/tree_funcs.h"
#include "../Frontend/lexical_analysis.h"
#include "../Frontend/dump_funcs.h"
#include "../Frontend/hash_funcs.h"

const char* asm_file_name = "../Examples/outfile.asm";
FILE* asm_file = NULL;

void ParseAsmTreeInAsmFile(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    fprintf(log_file, "Âûçîâ ParseAsmTreeInAsmFile\n");

    asm_file = fopen(asm_file_name, "w");

    Lexeme main = GetMainLexeme();
    ParseMain(tree, node, &main);

    while(node->type == KEY_LBRACE)
    {
        ParseAsmFunc(tree, node->left);
        node = node->right;
    }

    fclose(asm_file);
    printf("\nEND");
}

void ParseMain(Tree* tree, Node* node, Lexeme* main)
{
    assert(tree);
    assert(node);
    assert(main);

    while(node->type == KEY_LBRACE)
        node = node->right;

    ParseAsmOperator(tree, node, main);

    if (tree->is_draw)
        fprintf(asm_file, "DRAW\n");
    fprintf(asm_file, "HLT\n\n");
}

void ParseAsmFunc(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    fprintf(log_file, "Âûçîâ ParseAsmFunc\n");

    Lexeme func_info = node->lexeme;

    PrintFuncName(tree->name_table,  &func_info);

    ParseAsmOperator(tree, node->right, &func_info);
}

void ParseAsmOperator(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(func_info);

    while (node != NULL)
    {
        fprintf(log_file, "Âûçîâ ParseAsmOperator\n");

        if (node->type == KEY_END)
        {
            ParseAsmEnd(tree, node, func_info);
            return;
        }

        if (node->left->type == KEY_DRAW)
            ParseAsmDraw(tree, node->left, func_info);

        if (node->left->type == OP_ASSIGNED)
            ParseAsmAssigned(tree, node->left, func_info);

        if (node->left->type == KEY_IF && node->left->right->type == KEY_ELSE)
            ParseAsmIfElse(tree, node->left, func_info);

        if (node->left->type == KEY_IF && node->left->right->type != KEY_ELSE)
            ParseAsmIf(tree, node->left, func_info);

        if (node->left->type == KEY_WHILE)
            ParseAsmWhile(tree, node->left, func_info);

        if (node->left->type == KEY_IN)
            ParseAsmIn(tree, node->left, func_info);

        if (node->left->type == KEY_OUT)
            ParseAsmOut(tree, node->left, func_info);

        if (node->left->type == KEY_RETURN)
            ParseAsmReturn(tree, node->left, func_info);

        node = node->right;
    }
}

void ParseAsmAssigned(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmAssigned\n");

    ParseAsmExpression(tree, node->right, func_info);

    ParseAsmInVar(tree, node->left, func_info);
}

void ParseAsmDraw(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmDraw\n");

    ParseAsmOutVar(tree, node->left, func_info);

    fprintf(asm_file, "\nPOPREG BX\n");
    fprintf(asm_file, "PUSH 255\n");
    fprintf(asm_file, "POPM [BX]\n");

    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, "PUSHREG BX\n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG BX\n");
    fprintf(asm_file, "PUSH 128\n");
    fprintf(asm_file, "POPM [BX]\n");

    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, "PUSHREG BX\n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG BX\n");
    fprintf(asm_file, "PUSH 255\n");
    fprintf(asm_file, "POPM [BX]\n");

    tree->is_draw = true;
}

void ParseAsmEnd(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmEnd\n");

    if (tree->is_draw)
        fprintf(asm_file, "DRAW\n");

    fprintf(asm_file, "HLT\n");
}

void ParseAsmReturn(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmReturn\n");

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "\n\nPOPREG AX    ;×ÅÐÅÇ AX ÂÎÇÂÀÐÀÙÀÅÌ ÇÍÀ×ÅÍÈß\n");
    fprintf(asm_file, "PUSHREG HX\n");
    fprintf(asm_file, "PUSH %d     ;ÐÀÇÌÅÐ ÑÒÅÊÎÂÎÃÎ ÔÐÅÉÌÀ\n", SIZE_OF_FRAME);
    fprintf(asm_file, "SUB\n");
    fprintf(asm_file, "POPREG HX\n");
    fprintf(asm_file, "RET\n\n");
}

void ParseAsmIn(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmIn\n");


    fprintf(asm_file, "IN\n");

    ParseAsmInVar(tree, node->left, func_info);
}

void ParseAsmOut(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmOut\n");

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "OUT\n");
}

void ParseAsmIf(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmIf\n");

    static int counter = 0;

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "\nPUSH 0\n");
    fprintf(asm_file, "JE :endif_%d\n", counter);

    ParseAsmOperator(tree, node->right, func_info);

    fprintf(asm_file, ":endif_%d\n\n", counter);

    counter++;
}

void ParseAsmWhile(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmWhile\n");

    static int counter = 0;

    fprintf(asm_file, "\n:begin_while_%d\n", counter);

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "\nPUSH 0\n");
    fprintf(asm_file, "JE :endwhile_%d\n\n", counter);

    ParseAsmOperator(tree, node->right, func_info);

    fprintf(asm_file, "\nJMP :begin_while_%d\n", counter);

    fprintf(asm_file, "\n:endwhile_%d\n\n", counter);

    counter++;
}

void ParseAsmIfElse(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmIfElse\n");

    static int counter = 0;

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "\nPUSH 0\n");
    fprintf(asm_file, "JE :endif_with_else_%d\n\n", counter);

    ParseAsmOperator(tree, node->right->left, func_info);

    fprintf(asm_file, "\n:endif_with_else_%d\n", counter);

    ParseAsmOperator(tree, node->right->right, func_info);

    fprintf(asm_file, "\n\n");

    counter++;
}

void ParseAsmExpression(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ ParseAsmExpression\n");

    if (node->left != NULL && node->left->type != PARAM)
        ParseAsmExpression(tree, node->left, func_info);

    if (node->right != NULL)
        ParseAsmExpression(tree, node->right, func_info);

    PrintNodeInAsmFile(tree, node, func_info);
}

void PrintNodeInAsmFile(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Âûçîâ PrintNodeInAsmFile\n");

    if (ParseAsmPARAM(tree, node) == success) return;
    if (ParseAsmNumber(tree, node) == success) return;
    if (ParseAsmADD(tree, node) == success) return;
    if (ParseAsmSUB(tree, node) == success) return;
    if (ParseAsmMUL(tree, node) == success) return;
    if (ParseAsmDIV(tree, node) == success) return;
    if (ParseAsmPOW(tree, node) == success) return;
    if (ParseAsmSQRT(tree, node) == success) return;
    if (ParseAsmAnd(tree, node, func_info) == success) return;
    if (ParseAsmOr(tree, node, func_info) == success) return;
    if (ParseAsmOutVar(tree, node, func_info) == success) return;
    if (ParseAsmBigger(tree, node, func_info) == success) return;
    if (ParseAsmLess(tree, node, func_info) == success) return;
    if (ParseAsmEqual(tree, node, func_info) == success) return;
    if (ParseAsmNotEqual(tree, node, func_info) == success) return;
    if (ParseAsmCallFunc(tree, node, func_info) == success) return;
}

Status ParseAsmOr(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    static int counter = 0;

    if (node->type != OP_OR)
        return error;

    fprintf(log_file, "Âûçîâ ParseAsmAnd\n");

    fprintf(asm_file, "\nADD\n");
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, "JE :O_or_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":O_or_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nADD\n");
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, "JNE :O_n_or_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":O_n_or_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmAnd(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    static int counter = 0;

    if (node->type != OP_AND)
        return error;

    fprintf(log_file, "Âûçîâ ParseAsmAnd\n");

    fprintf(asm_file, "\nMUL\n");
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, "JE :A_and_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":A_and_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nMUL\n");
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, "\nJNE :A_n_and_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":A_n_and_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmPARAM(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == PARAM) return success;
    return error;
}

Status ParseAsmBigger(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    static int counter = 0;

    if (node->type != OP_BIGGER)
        return error;

    fprintf(log_file, "Âûçîâ ParseAsmBigger\n");

    fprintf(asm_file, "\nJA :B_bigger_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":B_bigger_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nJB :B_less_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":B_less_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_EQUAL)
        return error;

    fprintf(log_file, "Âûçîâ ParseAsmEqual\n");

    static int counter = 0;

    fprintf(asm_file, "\nJE :E_equal_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":E_equal_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nJNE :E_not_equal_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":E_not_equal_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmNotEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_NOT_EQUAL)
        return error;

    static int counter = 0;

    fprintf(log_file, "Âûçîâ ParseAsmNotEqual\n");

    fprintf(asm_file, "\nJNE :NE_equal_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":NE_equal_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nJE :NE_not_equal_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":NE_not_equal_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmLess(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_LESS)
        return error;

    static int counter = 0;

    fprintf(log_file, "Âûçîâ ParseAsmLess\n");

    fprintf(asm_file, "\nJB :L_less_%d\n", counter);
    fprintf(asm_file, "PUSH 0\n");
    fprintf(asm_file, ":L_less_%d\n\n", counter);

    ParseAsmExpression(tree, node->left, func_info);
    ParseAsmExpression(tree, node->right, func_info);

    fprintf(asm_file, "\nJA :L_bigger_%d\n", counter);
    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, ":L_bigger_%d\n\n", counter);

    counter++;

    return success;
}

Status ParseAsmNumber(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == NUM)
    {
        fprintf(log_file, "Âûçîâ ParseAsmNumber\n");
        fprintf(asm_file, "PUSH %d\n", node->lexeme.num);
        return success;
    }

    return error;
}

Status ParseAsmADD(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_ADD)
    {
        fprintf(log_file, "Âûçîâ ParseAsmADD\n");
        fprintf(asm_file, "ADD\n");
        return success;
    }

    return error;
}

Status ParseAsmSUB(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_SUB)
    {
        fprintf(log_file, "Âûçîâ ParseAsmSUB\n");
        fprintf(asm_file, "SUB\n");
        return success;
    }

    return error;
}

Status ParseAsmMUL(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_MUL)
    {
        fprintf(log_file, "Âûçîâ ParseAsmMUL\n");
        fprintf(asm_file, "MUL\n");
        return success;
    }

    return error;
}

Status ParseAsmDIV(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_DIV)
    {
        fprintf(log_file, "Âûçîâ ParseAsmDIV\n");
        fprintf(asm_file, "DIV\n");
        return success;
    }

    return error;
}

Status ParseAsmPOW(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_POW)
    {
        fprintf(log_file, "Âûçîâ ParseAsmPOW\n");
        fprintf(asm_file, "POW\n");
        return success;
    }

    return error;
}

Status ParseAsmSQRT(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == OP_SQRT)
    {
        fprintf(log_file, "Âûçîâ ParseAsmSQRT\n");
        fprintf(asm_file, "SQVRT\n");
        return success;
    }

    return error;
}

Status ParseAsmOutVar(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    size_t start_index = GetIndexOfFuncInNameTable(tree->name_table,
                                                     func_info);

    int mem_ptr = GetMemPtrOfVar(node, tree->name_table, start_index);

    if (IsInvalidNum(mem_ptr))
        return error;

    fprintf(log_file, "Âûçîâ ParseAsmOutVar\n");

    fprintf(asm_file, "\nPUSH %d  ;ÂÛÂÎÄ ÇÍÀ×ÅÍÈß ÏÅÐÅÌÅÍÍÎÉ |%s|\n",
            mem_ptr, node->lexeme.str.name);
    fprintf(asm_file, "PUSHREG HX \n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG GX\n");
    fprintf(asm_file, "PUSHM [GX]\n\n");

    return success;
}

Status ParseAsmInVar(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    if (node->type == KEY_INT) node = node->left;

    size_t start_index = GetIndexOfFuncInNameTable(tree->name_table,
                                                     func_info);

    int mem_ptr = GetMemPtrOfVar(node, tree->name_table, start_index);

    if (IsInvalidNum(mem_ptr))
    {
        fprintf(log_file, "Íå íàøåë ïåðåìåííîé |%s|", node->lexeme.str.name);
        return error;
    }

    fprintf(log_file, "Âûçîâ ParseAsmInVar\n");

    fprintf(asm_file, "\nPUSH %d  ;ÂÂÎÄ ÇÍÀ×ÅÍÈß ÏÅÐÅÌÅÍÍÎÉ |%s|\n",
            mem_ptr, node->lexeme.str.name);

    fprintf(asm_file, "PUSHREG HX \n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG GX\n");
    fprintf(asm_file, "POPM [GX]\n\n");

    return success;
}

int GetMemPtrOfVar(Node* node, NameTable* name_table, size_t start_index)
{
    assert(name_table);

    for (size_t i = start_index; i < name_table->size; ++i)
    {
        if (   node->lexeme.str.hash == name_table->arr[i].hash
            && strcmp(node->lexeme.str.name, name_table->arr[i].name) == 0)
            return (int)name_table->arr[i].address;
    }

    return -1;
}

size_t GetIndexOfFuncInNameTable(NameTable* name_table, Lexeme* func_info)
{
    assert(name_table);
    assert(func_info);

    size_t i = 0;

    for (; i < name_table->size; ++i)
    {
        //printf("NOW_FUNC: %s  -  SRC_FUNC: %s\n", func_info->str.name,name_table->arr[i].name);
        //printf("HASH_NOW_FUNC: %llu  -  HASH_SRC_FUNC: %llu\n", func_info->str.hash, name_table->arr[i].hash);
        if (   func_info->str.hash == name_table->arr[i].hash
            && strcmp(func_info->str.name, name_table->arr[i].name) == 0)
            return i;
    }

    //unreachable
    assert(false);
    return 0;
}

Status ParseAsmCallFunc(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(node);
    assert(tree);
    assert(func_info);

    if (node->type != IDENT) return error;

    fprintf(log_file, "Âûçîâ ParseAsmCallFunc\n");

    Lexeme now_func = node->lexeme;
    //printf("LEXEME: %s\n", node->lexeme.str.name);
    size_t index = GetIndexOfFuncInNameTable(tree->name_table, &now_func);

    ParseAsmExpression(tree, node->left->right, func_info);

    fprintf(asm_file, "CALL :%s\n", tree->name_table->arr[index].func_ptr);
    fprintf(asm_file, "PUSHREG AX\n");

    return success;
}

void PrintFuncName(NameTable* name_table, Lexeme* func_info)
{
    assert(name_table);
    assert(func_info);

    size_t index = GetIndexOfFuncInNameTable(name_table, func_info);

    fprintf(asm_file, ":%s\n", name_table->arr[index].func_ptr);

    //ïîêà äëÿ îäíîé ïåðåìåííîé
    size_t var_addres = name_table->arr[index + 1].address;

    //âûäåëÿåì íîâûé ñòåêîâûé ôðåéì
    fprintf(asm_file, "\nPUSH %d     ;ÐÀÇÌÅÐ ÑÒÅÊÎÂÎÃÎ ÔÐÅÉÌÀ\n", SIZE_OF_FRAME);
    fprintf(asm_file, "PUSHREG HX\n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG HX\n");


    fprintf(asm_file, "PUSH %llu  ;ÂÂÎÄ ÇÍÀ×ÅÍÈß ÏÅÐÅÌÅÍÍÎÉ |%s|\n",
            var_addres, name_table->arr[index + 1].name);

    fprintf(asm_file, "PUSHREG HX \n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG GX\n");
    fprintf(asm_file, "POPM [GX]\n\n");


}

Lexeme GetMainLexeme()
{
    Lexeme main = {};
    main.str.name = strdup("main");
    main.str.hash = GetHash("main");
    return main;
}

bool IsInvalidNum(int mem_ptr)
{
    return mem_ptr < 0 || mem_ptr > MAX_PTR;
}

