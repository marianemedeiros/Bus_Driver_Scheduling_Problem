#include "files.h"

char* createDirectory(char* algo_dir, char* file_name, char* it){
	char* p_dir = (char*) calloc(256,sizeof(char));
	p_dir = strcat(p_dir, PWD); // concat path
	
	mkdir(p_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	p_dir = strcat(p_dir, algo_dir); // concat path
	
	mkdir(p_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	p_dir = strcat(p_dir, file_name);// concar file name

	if(it != NULL){//concat it if it's not null
		p_dir = strcat(p_dir, "_");
		p_dir = strcat(p_dir, it);		
	}


	p_dir = strcat(p_dir, "/");// concat "/"


	mkdir(p_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	//if(status == -1)
	//	printf("Cannot open <<%s>> directory. \n", p_dir);

	return p_dir;
}

char* nameFile(char* pwd, char* name){
	char* name_file = (char*) calloc(256,sizeof(char));
	name_file = strcat(name_file, pwd);
	name_file = strcat(name_file, name);
	return name_file;
}

FILE* openFile(char* pwd, char* mode){
	FILE* file = fopen(pwd, mode);
	if(file == NULL)
   		printf("%s nao abriu\n", pwd);
   	return file;
}

void closeFile(FILE* file, char* pwd){
	fclose(file);
	free(pwd);
}

void writeFileInfos(FILE* file, double executed_m , int id, double f_cost, double f_obj, int size_j, 
	char* ls_name, int while_, int fo_count, int thr_choosed){
	fprintf(file, "%f; %d; %s; %f; %f; %d; %d; %d; %d\n", executed_m, id, ls_name, f_cost, f_obj, size_j, 
		while_, fo_count, thr_choosed);
}

void writeFileDetails(FILE* file, int id, int size_j){
	fprintf(file, "%d; \n %d \n\n", id, size_j);
}

char* getFileName(int i){
	if(i == 0)
		return LS1_INFOS;
	else if(i == 1)
		return LS2_INFOS;
	else if(i == 2)
		return LS3_INFOS;
	else if(i == 3)
		return LS4_INFOS;
	else if(i == 4)
		return LS5_INFOS;
	else if(i == 5)
		return LS6_INFOS;
	else if(i == 6)
		return LS7_INFOS;
	else if(i == 7)
		return LS8_INFOS;
	else if(i == 8)
		return LS9_INFOS;
	else if(i == 9)
		return LS10_INFOS;
	else if(i == 10)
		return LS11_INFOS;
	else if(i == 11)
		return LS12_INFOS;
	else if(i == 12)
		return LS13_INFOS;
	else if(i == 13)
		return LS14_INFOS;
	else if(i == 14)
		return LS15_INFOS;
	else if(i == 15)
		return LS16_INFOS;
	else if(i == 16)
		return LS17_INFOS;
	else if(i == 17)
		return LS18_INFOS;
	else if(i == 18)
		return LS19_INFOS;
	else if(i == 19)
		return LS20_INFOS;
	else if(i == 20)
		return LS21_INFOS;
	else if(i == 21)
		return LS22_INFOS;
	else if(i == 22)
		return LS23_INFOS;
	else if(i == 23)
		return LS24_INFOS;
	else if(i == 24)
		return LS25_INFOS;
	else if(i == 25)
		return LS26_INFOS;
	else if(i == 26)
		return LS27_INFOS;
	else if(i == 27)
		return LS28_INFOS;
	else if(i == 28)
		return LS29_INFOS;
	else if(i == 29)
		return LS30_INFOS;
	else if(i == 30)
		return LS31_INFOS;
	else if(i == 31)
		return LS32_INFOS;
	else if(i == 32)
		return LS33_INFOS;
	else if(i == 33)
		return LS34_INFOS;
	else if(i == 34)
		return LS35_INFOS;
	else if(i == 35)
		return LS36_INFOS;

	return NULL;
}

void openKfiles(char* p, int k){
	for (int i = 0; i < k; i++){
		pwds[i] = nameFile(p, getFileName(i));
		vet_files[i] = openFile(pwds[i], "w");
	}
}

void closeKfiles(int k){
	for (int i = 0; i < k; i++){
		fclose(vet_files[i]);
		free(pwds[i]);
	}
}










