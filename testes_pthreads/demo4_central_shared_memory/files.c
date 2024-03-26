#include "files.h"

FILE* openFile(char* pwd, char* mode){
	FILE* file = fopen(pwd, mode);
	if(file == NULL)
   		printf("%s nao abriu\n", pwd);
	return file;
}

void closeFile(FILE* file){
	fclose(file);
}

char* nameFile(char* pwd, char* name){
	char* name_file = (char*) calloc(256,sizeof(char));
	name_file = strcat(name_file, pwd);
	name_file = strcat(name_file, name);
	return name_file;
}


