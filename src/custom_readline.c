#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void str_zero(char *str, unsigned int index) {
	if(!index) {
		index=0;
	}
	for(; index<strlen(str); index++) {
		str[index]='\0';
	}
}

char *readline(const char *prompt) {
	int c;
	unsigned int size=100, index=0;
	char *buffer=calloc(size*sizeof(char), sizeof(char));
	
	if(prompt!=NULL) printf("%s", prompt);
	while((c=getchar())!=EOF) {
		if((char)c=='\n') break;
		if(strlen(buffer)>=size) {
			size+=100;
			buffer=realloc(buffer, size*sizeof(char));
			str_zero(buffer, index);
		}
		buffer[index++]=(char)c;
	}
	return buffer;
}

