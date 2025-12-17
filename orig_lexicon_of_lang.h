#ifndef ORIG_LEXICON_OF_LANG
#define ORIG_LEXICON_OF_LANG

#include "lexical_analysis.h"

const int NUM_OF_KEYWORDS = 11;
const int NUM_OF_OPERATORS = 12;

struct BaseLexeme
{
    Type type;
    const char* name;
    size_t hash;
};

extern BaseLexeme keywords_arr[NUM_OF_KEYWORDS];

extern BaseLexeme operator_arr[NUM_OF_OPERATORS];

#endif

