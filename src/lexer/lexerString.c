#include "../../include/lexer/lexer.h"
#include <stdlib.h>
#include <string.h>
const int incrementSize=64;
U8* lexerLexString(U8* input,U8* err) {
	u8* text=malloc(incrementSize);
	int reservedLength=incrementSize;
	int actualLength=0;
	const char* sequencesPairs[][]={
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
	for(int i=0;i!=count;i++) {
		U8* sequence=sequencesPairs[i][0];
		if(strncmp(input,sequence,strlen(sequences))) {
			U8* literal=sequencesPairs[i][1];
			int length=strlen(literal);
			if(reservedLength<length+actualLength) {
				text=realloc(text,actualLength+reservedLength);
			}
			memcpy(text,literal);
			break;
		}
	}
	U64 getHexDigits(int count) {
	};
	//hex
	if(strncmp(input,"\\x")) {
	}
}
