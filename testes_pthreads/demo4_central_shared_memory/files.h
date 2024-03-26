#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PWD "logs/"

FILE* buffer_infos;
FILE* buffer_details;

FILE* openFile(char* pwd, char* mode);
void closeFile(FILE* file);
char* nameFile(char* pwd, char* name);
