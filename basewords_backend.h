#ifndef KEY_WORDS_BACKEND
#define KEY_WORDS_BACKEND

#include "../Frontend/lexical_analysis.h"

const int NUM_OF_BASEWORDS = 29;

struct BaseWord
{
    Type type;
    const char* name;
    size_t hash;
};

extern BaseWord basewords_arr[NUM_OF_BASEWORDS];

#endif
