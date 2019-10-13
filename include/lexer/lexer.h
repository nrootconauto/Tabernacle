#ifndef LEXER_H
#define LEXER_H
#include <stdint.h>

//exceptions
#include "../../include/e4c/e4c.h"
#include "../../include/types/type.h"
E4C_DECLARE_EXCEPTION(LexicalError);

//numbers
I64 lexerLexSignedInt(U8* text,U64* length);
U64 lexerLexUnSignedInt(U8* text,U64* length);
F64 lexerLexFloat(U8* text,U64* length);

//string
U8* lexerLexString(U8* text,U64* length); //src/lexer/lexerString.c
U8* lexerLexCharactor(U8* text,U64* length);
U8* lexerLexTokenName(U8* text,U64* length);
//token types
typedef enum {
	LEXER_TYPE_TYPE,
	LEXER_TYPE_CHAR,
	LEXER_TYPE_STRING,
	LEXER_TYPE_INT,
	LEXER_TYPE_UINT,
	LEXER_TYPE_FLOAT,
	LEXER_TYPE_KEYWORD_IF,
	LEXER_TYPE_KEYWORD_ELSE,
	LEXER_TYPE_KEYWORD_WHILE,
	LEXER_TYPE_KEYWORD_FOR,
	LEXER_TYPE_KEYWORD_CONTINUE,
	LEXER_TYPE_KEYWORD_BREAK,
	LEXER_TYPE_KEYWORD_CLASS,
	LEXER_TYPE_KEYWORD_EXTERN,
	LEXER_TYPE_KEYWORD_IMPORT,
	LEXER_TYPE_KEYWORD_SWITCH,
	LEXER_TYPE_KEYWORD_CASE,
	LEXER_TYPE_KEYWORD_DEFAULT,
	LEXER_TYPE_KEYWORD__IMPORT,
	LEXER_TYPE_KEYWORD__EXTERN,
	LEXER_TYPE_NONE_FOUND,
	LEXER_TYPE_TOKEN_NAME,
	LEXER_TYPE_OP_PLUS,
	LEXER_TYPE_OP_MINUS,
	LEXER_TYPE_OP_MULTIPLY,
	LEXER_TYPE_OP_DIVIDE,
	LEXER_TYPE_OP_MODULUS,
	LEXER_TYPE_OP_BITWISE_OR,
	LEXER_TYPE_OP_BITWISE_AND,
	LEXER_TYPE_OP_BITWISE_XOR,
	LEXER_TYPE_OP_BITWISE_NOT,
	LEXER_TYPE_OP_LOGICAL_NOT,
	LEXER_TYPE_OP_LOGICAL_OR,
	LEXER_TYPE_OP_LOGICAL_AND,
	LEXER_TYPE_COMP_EQUAL,
	LEXER_TYPE_COMP_NOT_EQUAL,
	LEXER_TYPE_COMP_EQUAL_GREATER,
	LEXER_TYPE_COMP_EQUAL_LESSER,
	LEXER_TYPE_COMP_GREATER,
	LEXER_TYPE_COMP_LESSER,
	LEXER_TYPE_RIGHT_BRACKET,
	LEXER_TYPE_LEFT_BRACKET,
	LEXER_TYPE_LEFT_PARA,
	LEXER_TYPE_RIGHT_PARA		
} lexerTokenTypes;
lexerTokenTypes lexerLexKeyword(U8* where,U64* length);
typedef union {
	F64 _F;
	I64 _I;
	U64 _U;
	U8* _str;
	U8* _tokenName;
} lexerTokenValue;
typedef struct {
	lexerTokenValue value;
	lexerTokenTypes type;
} lexerToken;
void lexerTokenDestroy(lexerToken* token);
lexerToken lexerTokenGetNextToken(U8* string,U64* length);
void lexerTokenPrint(lexerToken* token);
#endif
