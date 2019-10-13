#include "../../include/lexer/lexer.h"
#include "../../include/e4c/e4c.h"
#include <stdlib.h>
#include <string.h>
E4C_DEFINE_EXCEPTION(MalformedString,"Malformed String",RuntimeException);
E4C_DEFINE_EXCEPTION(TooManyCharactors,"A charactor type only allows 1 charactor",RuntimeException);
const int incrementSize=64;

const char* invalidStringTerminators="\n";
U8* __lexerLexString(U8* input,U64* _length,U8 endChar,U64 maximumRuns) {
	U8* text=malloc(incrementSize);
	U8* where=text;
	U64 reservedLength=incrementSize;
	U64 actualLength=0;
	while(*input!=endChar) {
		char* invalidP=invalidStringTerminators;
		while(*invalidP!=0)
			if(*invalidP==0||*(invalidP++)==*where)
				throw(MalformedString,where);
		if(*(_length--)==0)
			throw(MalformedString,NULL);
		const char* sequencesPairs[][2]={
										{"\\\\","\\"},
										{"\\a","\a"},
										{"\\b","\b"},
										{"\\e","\e"},
										{"\\f","\f"},
										{"\\n","\n"},
										{"\\r","\r"},
										{"\\t","\t"},
										{"\\v","\v"},
										{"\\'","'"},
										{"\\\"","\""},
										{"\\?","\?"}
							 
		};
		const size_t count=sizeof(sequencesPairs)/sizeof(char*);
		void addText(char* literal) {
			int length=strlen(literal);
			if(reservedLength<length+actualLength) {
				U64 offset=where-text;
				text=realloc(text,actualLength+reservedLength);
				where=text+offset;
			}
			memcpy(where,literal,length);
			where+=length;
		}
		for(int i=0;i!=count;i++) {
			U8* sequence=sequencesPairs[i][0];
			if(0==strncmp(input,sequence,strlen(sequence))) {
				U8* literal=sequencesPairs[i][1];
				addText(literal);
				break;
			}
		}
		U64 getHexDigitsAndParse(U8 count) {
			U64 getDigitValue(U8 charactor) {
				if('0'<=charactor&&charactor<='9')
					return charactor-'0';
				if('a'<=charactor&&charactor<='f')
					return charactor-'a'+10;
				if('A'<=charactor&&charactor<='F')
					return charactor-'A'+10;
				return -1;
			}
			U64 multiplyBy=1;
			U64 value=0;
			for(U8 i=0;i!=count;i++) {
				U64 digit=getDigitValue(input[count]);
				if(digit==-1) {
					const U8* msg="%c: is not a hexidecimal digit\n\x00";
					const U64 msgSize=sizeof(msg);
					char text[msgSize+1];
					vsprintf(text,msg,input[count]);
					throw(LexicalError,text);
				}
				value+=multiplyBy*digit;
				multiplyBy*=16;
			}
		}
		//hex
		if(strncmp(input,"\\x",2)) {
			getHexDigitsAndParse(2);
			U8* toWrite[3];
			strncpy(toWrite,input,2);
			toWrite[2]=0;
			addText(toWrite);
			where+=2;
			continue;
		}
		//octal
		U64 octalGetDigits(U8 maxCount) {
			U8 getOctalDigit(U8 charactor) {
				if('0'<=charactor&&charactor<='7')
					return charactor-'0';
				return -1;
			}
			U64 i;
			U64 value=0;
			U64 multiplyBy=1;
			for(i=0;i!=maxCount;i++) {
				U64 digit=getOctalDigit(where[i]);
				if(-1==digit)
					break;
				value+=multiplyBy*digit;
				multiplyBy*=8;
			}
			if(i==0) {
				const U8* message="Expected an octal digit,instead got %c\n\x00";
				const U64 length=sizeof(message);
				const U8 errMsg[length];
				vsprintf(errMsg,message,where[i]);
				throw(LexicalError,errMsg);
			}
			where+=i;
			char toAdd[2];
			toAdd[1]=NULL;
			*toAdd=value;
			addText(toAdd);
		}
		//Heideciaml 4 digits
		const U64 OneByteUTF8Size=(1<<7)-1;
		const U64 TwoByetUTF8Size=(1<<(6+6))-1;
		const U64 ThreeByteUTF8Size=(1<<(5+6+6))-1;
		const U64 FoutByteUTF8Size=(1<<(4+6+6+6))-1;
	
		if(0==strncmp(input,"\\u",2)|0==strncmp(input,"\\U",2)) {
			U64 value;
			if(input[1]=='U')
				input=getHexDigitsAndParse(8);
			else
				input=getHexDigitsAndParse(4);

			if(value<=OneByteUTF8Size) {
				*(input+1)=value&(0xff>>1);
				continue;
			}
			U8 bytes=0;
			if(value<=TwoByetUTF8Size)
				bytes=2;
			if(value<=ThreeByteUTF8Size)
				bytes=3;
			U8 mask=0xff<<(8-bytes);
			char buffer[bytes+1];
			for(int i=bytes-1;i!=0;i--) {
				buffer[i]=value&0b00111111;
				value>>=6;
			}
			buffer[0]=(value)|mask;
			buffer[bytes]=NULL;
			addText(buffer);
			U64 inc=(input[1]=='U')?8:4;
			where+=bytes;
			input+=inc;
			continue;
		}
		//TODO improve me
		//char currentChar[2];
		//*currentChar=*input;
		//currentChar[1]=NULL;
		//addText(&currentChar);
		if(actualLength+1>=reservedLength) {
			U64 offset=where-text;
			text=realloc(text,reservedLength+incrementSize);
			where=text+offset;
		}
		*(where++)=input[0];
		input++;
	}
	*_length=where-text;
	return text;
}
U8* lexerLexString(U8* text,U64* length) {
	if(*text=='"') {
		U8* retVal=__lexerLexString(text,length,'"',-1);
		length[0]++;
		return retVal;
	}
	return NULL;
}
U8* lexerLexCharactor(U8* text,U64* length) {
	if(*text=='\'') {
		U8* retVal=__lexerLexString(text,length,'\'',1);
		if(strlen(retVal)!=1) {
			free(retVal);
			throw(MalformedString,NULL);
			return NULL;
		}
		length[0]++;
		return *retVal;
	}
	return NULL;
}