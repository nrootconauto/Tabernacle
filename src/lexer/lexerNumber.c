#include "../../include/lexer/lexer.h"
#include "../../include/slre/slre.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
//TODO add size checks within x
U64 lexerLexUnSignedInt(U8* text,U64* length) {
	if(0==strncmp(text,"0x",2)) {
		text+=2;
		U64 getHexDigit(U8 charactor) {
			if('0'<=charactor&&charactor<='9')
				return charactor-'0';
			if('A'<=charactor&&charactor<='F')
				return charactor-'A'+10;
			if('a'<=charactor&&charactor<='f')
				return charactor-'a'+10;
			return -1;
		}
		U64 count=0;
		U64 value=0;
		U64 multiplyBy=1;
		for(;;count++) {
			U64 digit=getHexDigit(text[count]);
			if(digit!=-1) {
				if(count!=0)
					value*=16;
				value+=digit;
			} else
				break;
		}
		if(count==0) {
			const char* errMsg="Expected hexidecimal Digits after \"0x\"\n\x00";
			throw(LexicalError,errMsg);
		}
		*length=count+2;
		return value;
 	} else if(text[0]=='0') { //octal
		U64 getDigitOctal(U8 charactor) {
			if('0'<=charactor&&charactor<='7')
				return charactor-'0';
			return -1;
		}
		text++;
		U64 offset=0;
		U64 digit;
		U64 value=0;
		U64 multiplyBy=1;
		do {
			digit=getDigitOctal(text++[0]);
			offset++;
			if(digit==-1)
				break;
			if(offset!=1)
				value*=8;
			value+=digit;
			
		} while(true);
		*length=offset;
		return value;
	} else {
		U64 count=0;
		U64 value=0;
		U64 multiplyBy=1;
		while('0'<=*text&&*text<='9') {
			value+=(*text-'0')*multiplyBy;
			if(count!=0)
				value*=10;
			count++;
			text++;
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
		return -value;
	}
	return lexerLexUnSignedInt(text,length);
}
//const char* lexerFloatRegex1="([0-9]+\\.[0-9]*)";
//const char* lexerFloatRegex2="([0-9]*\\.[0-9]+)";
F64 lexerLexFloat(U8* where,U64* length) {
	U8* original=where;
	F64 sign=1;
	if(*where=='-') {
		sign=-1;
		where++;
	}
	U8* getDigits(U8* _where) {
		while('0'<=*_where&&*_where<='9') {
			_where++;
		}
		return _where;
	}
	//floats must have '.'
	U8* dot=getDigits(where);
	if(*dot!='.') {
		*length=0;
		return -1;
	}
	U8* afterDot=getDigits(dot+1);
	//if found dot with no digits no
	if(afterDot-dot==1&&dot-where==0) {
		*length=0;
		return -1;
	}
	F64 retVal;
	U8 buffer[afterDot-where+1];
	buffer[afterDot-where]=0;
	memcpy(buffer,original,afterDot-original);
	sscanf(buffer,"%lf",&retVal);
	*length=afterDot-original;
	return retVal*sign;
}
