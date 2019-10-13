#include "../../include/lexer/lexer.h"
#include <string.h>
lexerTokenTypes lexerLexKeyword(U8* where,U64* length) {
	U8 checkAt(const char* toCheck) {
		*length=strlen(toCheck);
		if(0==strncmp(where,toCheck,*length)) {
			return 1;
		}
		return 0;
	}
	if(checkAt("if"))
		return LEXER_TYPE_KEYWORD_IF;
	if(checkAt("else"))
		return LEXER_TYPE_KEYWORD_ELSE;
	if(checkAt("while"))
		return LEXER_TYPE_KEYWORD_WHILE;
	if(checkAt("for"))
		return LEXER_TYPE_KEYWORD_FOR;
	if(checkAt("continue"))
		return LEXER_TYPE_KEYWORD_CONTINUE;
	if(checkAt("break"))
		return LEXER_TYPE_KEYWORD_BREAK;
	if(checkAt("class"))
		return LEXER_TYPE_KEYWORD_CLASS;
	if(checkAt("extern"))
		return LEXER_TYPE_KEYWORD_EXTERN;
	if(checkAt("import"))
		return LEXER_TYPE_KEYWORD_IMPORT;
	if(checkAt("switch"))
		return LEXER_TYPE_KEYWORD_SWITCH;
	if(checkAt("case"))
		return LEXER_TYPE_KEYWORD_CASE;
	if(checkAt("default"))
		return LEXER_TYPE_KEYWORD_DEFAULT;
	if(checkAt("import"))
		return LEXER_TYPE_KEYWORD_IMPORT;
	if(checkAt("extern"))
		return LEXER_TYPE_KEYWORD_EXTERN;
	if(checkAt("_import"))
		return LEXER_TYPE_KEYWORD__IMPORT;
	if(checkAt("_extern"))
		return LEXER_TYPE_KEYWORD__EXTERN;
	*length=0;
	return LEXER_TYPE_NONE_FOUND;
}

