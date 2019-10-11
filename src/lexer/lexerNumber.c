#include "../../include/lexer/lexer.h"
//TODO add size checks within 
I64 lexerLexUnSigned(U8* text,U64* length) {
	if(text[0]=='0') { //octal
		U64 getDigitOctal(U8 charactor) {
			if('0'<=charactor&&charactor<='7')
				return charactor-'0';
			return -1;
		}
		text++;
		U64 offset=-1;\
		U64 digit;
		U64 value=0;
		U64 multiplyBy=1;
		do {
			digit=getDigitOctal(text++[0]);
			offset++;
			if(digit==-1)
				break;
			value+=multiplyBy*digit;
			multiplyBy*=8;
		} while(true);
		*length=offset;
		return value;
	} else if(0==strncmp(text,"0x",2)) {
		text+=2;
		U64 getHexDigit(U8 charactor) {
			if('0'<=charactor&&charactor<='9')
				return charactor-'0';
			if('A'<=charactor&&charactor<='F')
				return charactor-'A'+10;
			if('a'<=charactor&&charactor<='f')
				return charactor-'a'+10;
		}
		U64 count=0;
		U64 value=0;
		U64 multiplyBy=1;
		for(;;count++) {
			U64 digit=getHexDigit(text+count);
			if(digit==-1) {
				value+=multiplyBy*digit;
			} else
				break;
			multiplyBy*=16;
		}
		if(count==0) {
			const char* errMsg="Expected hexidecimal Digits after \"0x\"\n\x00";
			throw(LexicalError,errMsg);
		}
 	} else {
		U64 count=0;
		U64 value=0;
		U64 multiplyBy=1;
		while('0'<=*input&&*input<='9') {
			value+=(value-'0')*multiplyBy;
			multiplyBy*=10;
			count++;
			input++;
		}
		*length=count;
		return value;
	}
	*length=0;
	return -1;
}
I64 lexerLexSignedInt(U8* text,U64* length) {
	if(*text=='-') {
		U64 value=lexerLexUnSignedInt(text+1,length);
		length[0]++;
		return value;
	}
	return lexerLexUnSignedInt(text,length);
}
