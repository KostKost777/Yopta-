#include <TXLib.h>

#include "lexical_analysis.h"
#include "hash_funcs.h"

String keywords_arr[NUM_OF_KEYWORDS] =
{
{"внатуре",  GetHash("внатуре")},    //if
{"потрещим", GetHash("потрещим")},  //while
{"шухер",    GetHash("шухер")},        //return
{"йопта",    GetHash("йопта")},        //int
{"гыы",      GetHash("гыы")},          //(
{"жыы",      GetHash("жыы")},          //(
{"наx",      GetHash("нах")},          //;
{"шуры",     GetHash("шуры")},       // {
{"муры",     GetHash("муры")},       // {
};

String operator_arr[NUM_OF_OPERATORS] =
{
{"=", GetHash("=")},
{"==", GetHash("==")},
{"<=", GetHash("<=")},
{">=", GetHash(">=")},
{"<",   GetHash("<")},
{">",   GetHash(">")},
{"+",   GetHash("+")},
{"-",    GetHash("-")},
{"/",    GetHash("/")},
{"^",    GetHash("^")},
{"%",    GetHash("%")},
};

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

void MakeLexicalAnalysis(Buffer* buffer, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(tokens);

    while(*buffer->data != '\0')
    {
        size_t old_size = buffer->size;

        printf("BUFFER: %s\n", buffer->data);

        if (ParseNumber(buffer, tokens) == success)
            continue;

        if (ParseKeyWord(buffer, tokens) == success)
            continue;

        if (ParseOperator(buffer, tokens)== success)
            continue;

        if(ParseIdentifier(buffer, tokens) == success)
            continue;

        if (old_size == buffer->size && *buffer->data != '\0')
        {
            printf("ERROR on line: %llu on column: %llu\n",
                                              buffer->line,
                                              buffer->column);
        }
    }
}

Status ParseNumber(Buffer* buffer, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(tokens);

    int sign = GetSignOfNumber(buffer);
    if (sign == 0) return error;

    int num = 0;

    while(isdigit(*buffer->data))
    {
        num *= 10;
        num += (*buffer->data - '0');
        MoveBufferPointer(buffer, 1);
    }

    printf("NUM: %d\n", num);
    AddNumToken(tokens, buffer, NUM, num);
    SkipSpaces(buffer);

    return success;
}

Status ParseKeyWord(Buffer* buffer, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(tokens);

    char keyword_name[MAX_LEN_OF_WORD] = {};
    int len = 0;

    sscanf(buffer->data, "%s%n", keyword_name, &len);
    //printf("NAME: %s\n", keyword_name);

    if (len < 0) assert(false);

    size_t keyword_hash = GetHash(keyword_name);

    for (int i = 0; i < NUM_OF_KEYWORDS; ++i)
    {
        if (keywords_arr[i].hash == keyword_hash)
        {
            char* name_ptr = strdup(keyword_name);

            AddStringToken(tokens, buffer, KEY, name_ptr);

            MoveBufferPointer(buffer, (size_t)len);

            SkipSpaces(buffer);
            return success;
        }
    }

    return error;
}

Status ParseOperator(Buffer* buffer, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(tokens);

    char operator_name[MAX_LEN_OF_WORD] = {};
    int len = 0;

    sscanf(buffer->data, "%s%n", operator_name, &len);

    if (len < 0) assert(false);

    size_t operator_hash = GetHash(operator_name);

    for (int i = 0; i < NUM_OF_OPERATORS; ++i)
    {
        if (operator_arr[i].hash == operator_hash)
        {
            char* name_ptr = strdup(operator_name);

            AddStringToken(tokens, buffer, OP, name_ptr);

            MoveBufferPointer(buffer, (size_t)len);

            SkipSpaces(buffer);
            return success;
        }
    }
    return error;
}

Status ParseIdentifier(Buffer* buffer, TokenArray* tokens)
{
    assert(buffer);
    assert(buffer->data);
    assert(tokens);

    char identifier_name[MAX_LEN_OF_WORD] = {};
    int len = 0;

    sscanf(buffer->data, "%s%n", identifier_name, &len);

    if (len < 0) assert(false);

    char* name_ptr = strdup(identifier_name);

    AddStringToken(tokens, buffer, IDENT, name_ptr);

    MoveBufferPointer(buffer, (size_t)len);

    SkipSpaces(buffer);
    return success;
}

int GetSignOfNumber(Buffer* buffer)
{
    assert(buffer);
    assert(buffer->data);

    if (*buffer->data == '-' && isdigit (*(buffer->data + 1)))
    {
        MoveBufferPointer(buffer, 1);
        return -1;
    }
    else if (isdigit (*buffer->data) )
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

    tokens->arr[tokens->size].type = type;
    tokens->arr[tokens->size].lexeme.str.name = name;
    tokens->arr[tokens->size].lexeme.str.hash = GetHash(name);
    tokens->arr[tokens->size].line = buffer->line;
    tokens->arr[tokens->size].column = buffer->column;

    tokens->size++;
}

void MoveBufferPointer(Buffer* buffer, size_t offset)
{
    assert(buffer);
    assert(buffer->data);

    buffer->data += offset;
    buffer->column += offset;
}

void SkipSpaces(Buffer* buffer)
{
    assert(buffer);
    assert(buffer->data);

    while(isspace(*buffer->data))
    {
        switch(*buffer->data)
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

        buffer->data += 1;
    }
}

// bool IsRussianAlpha(char sym)
// {
//     unsigned char c = (unsigned char) sym;
//     return c >= 192 || c == 168 || c == 184;
// }
