#indef LEXER_H
#define LEXER_H
#include <stdint.h>
//unsinged of Holy C
typedef void U0;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
//signed of Holy C
typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;
//floats
typedef double F64;

//exceptions
#include "../../include/e4c/e4c.h"
E4C_DEFINE_EXCEPTION(LexicalError,"LexicalError",RuntimeException);

//numbers
I64 lexerLexSignedInt(U8* text,U8* length);
U64 lexerLexUnSignedInt(U8* text,U8* length);
F64 lexerLexFloat(U8* text,U8* length);

//string
U8* lexerLexString(U8* text,U64* length); //src/lexer/lexerString.c
#endif
