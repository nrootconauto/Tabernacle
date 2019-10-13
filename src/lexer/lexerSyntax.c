#include "../../include/lexer/lexer.h"
#include <stdbool.h>
#include <string.h>
#define checkAndReturn(str,value) if(check(str)) return value;
lexerTokenTypes lexerLexSyntax(U8* string,U64* length) {
	bool check(const U8* compareTo) {
		U64 size=strlen(compareTo);
		*length=size;
		return 0==strncmp(string,compareTo,size);
	}
	checkAndReturn("==",LEXER_TYPE_COMP_EQUAL);
	checkAndReturn("!=",LEXER_TYPE_COMP_NOT_EQUAL);
	checkAndReturn(">=",LEXER_TYPE_COMP_EQUAL_GREATER);
	checkAndReturn("<=",LEXER_TYPE_COMP_EQUAL_LESSER);
	checkAndReturn("<",LEXER_TYPE_COMP_LESSER);
	checkAndReturn(">",LEXER_TYPE_COMP_GREATER);
	checkAndReturn("-",LEXER_TYPE_OP_MINUS);
	checkAndReturn("+",LEXER_TYPE_OP_PLUS);
	checkAndReturn("*",LEXER_TYPE_OP_MULTIPLY);
	checkAndReturn("/",LEXER_TYPE_OP_DIVIDE);
	checkAndReturn("%",LEXER_TYPE_OP_MODULUS);
	checkAndReturn("~",LEXER_TYPE_OP_BITWISE_NOT);
	checkAndReturn("!",LEXER_TYPE_OP_LOGICAL_NOT);
	checkAndReturn("&",LEXER_TYPE_OP_BITWISE_AND);
	checkAndReturn("|",LEXER_TYPE_OP_BITWISE_OR);
	checkAndReturn("^",LEXER_TYPE_OP_BITWISE_XOR);
	checkAndReturn("&&",LEXER_TYPE_OP_LOGICAL_AND);
	checkAndReturn("||",LEXER_TYPE_OP_LOGICAL_OR);
	checkAndReturn("(",LEXER_TYPE_LEFT_PARA);
	checkAndReturn(")",LEXER_TYPE_RIGHT_PARA);
	checkAndReturn("[",LEXER_TYPE_LEFT_BRACKET);
	checkAndReturn("]",LEXER_TYPE_RIGHT_BRACKET);
	*length=0;
	return LEXER_TYPE_NONE_FOUND;
}