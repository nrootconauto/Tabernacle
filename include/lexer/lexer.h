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

//numbers
I64 lexerLexIntSigned(U8* text,U8* err);
U64 lexerLexUnsignedInt(U8* text,U8* err);
F64 lexerLexFloat(U8* text,U8* err);

//string
U8* lexerLexString(U8*,U8*err);
#endif
