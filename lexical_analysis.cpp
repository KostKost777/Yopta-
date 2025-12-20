#include <TXLib.h>

#include "lexical_analysis.h"
#include "orig_lexicon_of_lang.h"
#include "hash_funcs.h"

void TokenArrayCtor(TokenArray* tokens)
{
    assert(tokens);
    tokens->arr = (Token*)calloc(DEFAULT_TOKEN_ARR_SIZE, sizeof(Token));
    tokens->size = 0;
}

void TokenArrayDtor(TokenArray* tokens)
{
    assert(tokens);

    for (size_t i = 0; i < tokens->size; ++i)
    {
        if (tokens->arr[i].type != NUM)
        {
           free(tokens->arr[i].lexeme.str.name);
           tokens->arr[i].lexeme.str.name = NULL;
           tokens->arr[i].lexeme.str.hash = 0;
        }
    }

    free(tokens->arr);
    tokens->arr = NULL;

    tokens->size = 0;
}

Status MakeLexicalAnalysis(Buffer* buffer, size_t* pos, TokenArray* tokens)
{
    assert(buffer);
    assert(pos);
    assert(buffer->data);
    assert(tokens);

    while(buffer->data[*pos] != '\0')
    {
        size_t old_size = buffer->size;

        // printf("---------------------------------\n");
        // printf("BUFFER: %s\n\n", buffer->data);
        // printf("POS: %llu\n", *pos);
        // printf("---------------------------------\n\n");
        ;

        if (ParseNumber(buffer, pos, tokens) == success)
            continue;

        if (ParseKeyWord(buffer, pos, tokens) == success)
            continue;

        if (ParseOperator(buffer, pos, tokens)== success)
            continue;

        if(ParseIdentifier(buffer, pos, tokens) == success)
            continue;

        if (old_size == buffer->size && buffer->data[*pos] != '\0')
        {
            printf("ERROR on line: %llu on column: %llu\n",
                                              buffer->line,
                                              buffer->column);
            return error;
        }
    }

    AddStringToken(tokens, buffer, END, buffer->data + *pos);

    return success;
}

Status ParseNumber(Buffer* buffer, size_t* pos, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);
    assert(tokens);

    int len = 0;
    int num = 0;

    int status = sscanf(buffer->data + *pos, "%d%n", &num, &len);

    if (status == 0) return error;

    MoveBufferPointer(buffer, pos, (size_t)len);

    //printf("NUM: %d\n", num);
    AddNumToken(tokens, buffer, NUM, num);
    SkipSpaces(buffer, pos);

//     int sign = GetSignOfNumber(buffer, pos);
//     if (sign == 0) return error;
//
//     int num = 0;
//
//     while(isdigit(buffer->data[*pos]))
//     {
//         num *= 10;
//         num += (buffer->data[*pos] - '0');
//         MoveBufferPointer(buffer, pos, 1);
//     }
//
//     //printf("NUM: %d\n", num);
//     AddNumToken(tokens, buffer, NUM, num);
//     SkipSpaces(buffer, pos);

    return success;
}

Status ParseKeyWord(Buffer* buffer, size_t* pos, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);
    assert(tokens);

    char keyword_name[MAX_LEN_OF_WORD] = {};
    int len = 0;

    sscanf(buffer->data + *pos, "%s%n", keyword_name, &len);

    if (len < 0) assert(false);

    BaseLexeme* key_word_ptr = FindInKeyWordArr(keyword_name)

    if (key_word_ptr == NULL) return error;

    AddStringToken(tokens, buffer, key_word_ptr.type, keyword_name);
    MoveBufferPointer(buffer, pos, (size_t)len);
    SkipSpaces(buffer, pos);
}

Status ParseOperator(Buffer* buffer, size_t* pos, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);
    assert(tokens);

    char operator_name[MAX_LEN_OF_WORD] = {};
    int len = 0;

    sscanf(buffer->data + *pos, "%s%n", operator_name, &len);

    if (len < 0) assert(false);

    BaseLexeme* op_word_ptr = FindInKeyWordArr(operator_name)

    if (op_word_ptr == NULL) return error;

    AddStringToken(tokens, buffer, op_word_ptr.type, operator_name);
    MoveBufferPointer(buffer, pos, (size_t)len);
    SkipSpaces(buffer, pos);
}

Status ParseIdentifier(Buffer* buffer, size_t* pos, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);
    assert(tokens);

    size_t len = 0;
    char identifier_name[MAX_LEN_OF_WORD] = {};

    while(true)
    {
        if (   !((len != 0 && isdigit(buffer->data[*pos]))
            || IsSymInIdentifierName(buffer->data[*pos]))
            || isspace(buffer->data[*pos]))
            break;

        identifier_name[len] = buffer->data[*pos];

        len++;
        MoveBufferPointer(buffer, pos, 1);
        //printf("ABOBA: %s\n", identifier_name);
    }

    AddStringToken(tokens, buffer, IDENT, identifier_name);

    SkipSpaces(buffer, pos);
    return success;
}

int GetSignOfNumber(Buffer* buffer, size_t* pos)
{
    assert(buffer);
    assert(pos);
    assert(buffer->data);

    if (buffer->data[*pos] == '-' && isdigit (*(buffer->data + 1)))
    {
        MoveBufferPointer(buffer, pos, 1);
        return -1;
    }
    else if (isdigit (buffer->data[*pos]) )
        return 1;

    return 0;
}

void AddNumToken(TokenArray* tokens, Buffer* buffer,
                 Type type, int num)
{
    assert(tokens);
    assert(buffer);

    tokens->arr[tokens->size].type = type;
    tokens->arr[tokens->size].lexeme.num = num;
    tokens->arr[tokens->size].line = buffer->line;
    tokens->arr[tokens->size].column = buffer->column;

    tokens->size++;
}

void AddStringToken(TokenArray* tokens, Buffer* buffer,
                    Type type, char* name)
{
    assert(tokens);
    assert(buffer);
    assert(name);

    tokens->arr[tokens->size].type = type;
    tokens->arr[tokens->size].lexeme.str.name = strdup(name);
    tokens->arr[tokens->size].lexeme.str.hash = GetHash(name);
    tokens->arr[tokens->size].line = buffer->line;
    tokens->arr[tokens->size].column = buffer->column;

    tokens->size++;
}

void MoveBufferPointer(Buffer* buffer, size_t* pos,  size_t offset)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);

    *pos += offset;
    buffer->column += offset;
}

void SkipSpaces(Buffer* buffer, size_t* pos)
{
    assert(buffer);
    assert(buffer->data);
    assert(pos);

    while(isspace(buffer->data[*pos]))
    {
        switch(buffer->data[*pos])
        {
            case ' ': buffer->column++;
                      break;

            case '\t': buffer->column += 4;
                       break;

            case '\n': buffer->column = 1;
                       buffer->line++;
                       break;

            default: break;
        }

        *pos += 1;
    }
}

bool IsSymInIdentifierName(char sym)
{
    unsigned char c = (unsigned char)sym;
    return isalpha(c) || c == '_'
           || c >= 192 || c == 168 || c == 184;
}

// bool IsRussianAlpha(char sym)
// {
//     unsigned char c = (unsigned char) sym;
//     return c >= 192 || c == 168 || c == 184;
// }

BaseLexeme* FindInKeyWordArr(char* name, size_t hash)
{
    assert(name);

    size_t hash = GetHash(name);

    for (int i = 0; i < NUM_OF_KEYWORDS; ++i)
    {
        if (keywords_arr[i].hash == hash &&
            strcmp(keywords_arr[i].name, name) == 0)
        {
            return &keywords_arr[i];
        }
    }

    return NULL;
}

BaseLexeme* FindInOpArr(char* name)
{
    assert(name);

    size_t hash = GetHash(name)

    for (int i = 0; i < NUM_OF_OERATORS; ++i)
    {
        if (operator_arr[i].hash == hash &&
            strcmp(operator_arr[i].name, name) == 0)
        {
            return &operator_arr[i];
        }
    }

    return NULL;
}
