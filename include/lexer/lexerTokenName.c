#include "../../include/lexer/lexer.h"
#include <stdbool.h>
const char* tokenOtherValidChars="$_";
U8* lexerLexTokenName(U8* text, U64* length) {
	bool isLetter() {
		return ('a'<=*text&&*text>='z')||('A'<=*text&&*text>='Z');
	}
	bool isNumber() {
		return '0'<=*text&&*text<='9';
	};
	bool isOther() {
		for(int i=0;i!=sizeof(tokenOtherValidChars);i++)
			if(*text==tokenOtherValidChars[i])
				return true;
		return false;
	}
	U8* original=text;
	for(;;) {
		if(isLetter()||isNumber()||isOther()) {
			text++;
			continue;
		}
		break;
	}
	*length=text-original;
	if(*length==0)
		return NULL;
	U8* retVal=malloc(length);
	memcpy(retVal,original,*length);
	return retVal;
}