#include "../../include/lexer/lexer.h"
void lexerTokenPrint(lexerToken* token) {
	switch(token->type) {
		case LEXER_TYPE_INT:
			printf("LEXER_TYPE_INT:%li\n",token->value._I);
			return;
		case LEXER_TYPE_UINT:
			printf("LEXER_TYPE_UINT:%lu\n",token->value._U);
			return;
		case LEXER_TYPE_STRING:
			printf("LEXER_TYPE_STRING:%s\n",token->value._str);
			return;
		case LEXER_TYPE_CHAR:
			printf("LEXER_TYPE_CHAR:%c\n",token->value._U);
			return;
		case LEXER_TYPE_TOKEN_NAME:
			printf("LEXER_TYPE_TOKEN_NAME:%s\n",token->value._tokenName);
			return;
		default:
			printf("Implement Me\n");
	}
}