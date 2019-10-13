#include "../../include/lexer/lexer.h"
E4C_DEFINE_EXCEPTION(LexicalError,"LexicalError",RuntimeException);
E4C_DEFINE_EXCEPTION(NoTokenFound,"No Token Found",LexicalError);
void lexerTokenDestroy(lexerToken* token) {
	if(token->type==LEXER_TYPE_STRING)
		free(token->value._str);
};
lexerToken lexerTokenGetNextToken(U8* string,U64* length) {
	lexerToken retVal;
	retVal.value._F=lexerLexFloat(string,length);
	if(*length!=0) {
		retVal.type=LEXER_TYPE_FLOAT;
		return retVal;
	}
	retVal.value._I=lexerLexSignedInt(string,length);
	if(*length!=0) {
		retVal.type=LEXER_TYPE_INT;
		return retVal;
	}
	retVal.value._str=lexerLexString(string,length);
	if(*length!=0) {
		retVal.type=LEXER_TYPE_STRING;
		return retVal;
	}
	retVal.value._U=lexerLexUnSignedInt(string,length);
	if(*length!=0) {
		retVal.type=LEXER_TYPE_UINT;
		return retVal;
	}
	retVal.value._U=lexerLexCharactor(string,length);
	if(*length!=0) {
		retVal.type=LEXER_TYPE_UINT;
		return retVal;
	}
	retVal.type=lexerLexKeyword(string,length);
	if(*length!=0) {
		return retVal;
	}
	retVal.type=lexerLexSyntax(string,length);
	if(*length!=0)
		return retVal;
	throw(NoTokenFound,NULL);
}