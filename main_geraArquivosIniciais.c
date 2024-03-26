#include "restriction_evaluator/restriction_evaluator.h"
#include "libraries/metaheuristics/vns_s.h"
#include "libraries/metaheuristics/vns_p.h"
#include <unistd.h>

#define t_files 11

int file_numbers[t_files] = {130, 412, 761, 1000, 1517, 2313};

void generateInitialSolution2AllFiles(int dot, int i_sol, int infos){
	FILE *fp = NULL;
	FILE *fp_is = NULL;

	char* saveAt;

	if(infos){
		char* infosIS = (char*) calloc(256,sizeof(char));
		infosIS = strcat(infosIS, "resultados/infosIS.cvs");
		fp = fopen(infosIS, "w");

		if(fp == NULL)
   			printf("infoIS.cvs nao abriu\n");

   		fprintf(fp, "FileName; Objective Function; Cost Function; Number Journeys; Sched Duration; Time Elapsed\n");
	}
	
	for (int i = 0; i < t_files; i++){
		char* fileName = (char*) calloc(33,sizeof(char));
		sprintf(fileName, "V_TCCC%d", file_numbers[i]); // puts string into buffer
    	

    	if(dot){
    		saveAt = (char*) calloc(256,sizeof(char));
    		saveAt = strcat(saveAt, "resultados/dot_files/");
			saveAt = strcat(saveAt, fileName);
			saveAt = strcat(saveAt, "Initial_Solution.dot");
		}

		if(i_sol){
			char* initialSol_dir = (char*) calloc(256,sizeof(char));
			initialSol_dir = strcat(initialSol_dir, "resultados/initial_solutions/");
			initialSol_dir = strcat(initialSol_dir, fileName);

			fp_is = fopen(initialSol_dir, "w");

			if(fp_is == NULL)
   				printf("nao abriu\n");
		}


		char* readAt = (char*) calloc(256,sizeof(char));
		readAt = strcat(readAt, "instancias/");
		readAt = strcat(readAt, fileName);
		readAt = strcat(readAt, ".txt");	
		
		time_t tm;
		srand((unsigned) time(&tm));
		List* aux_t = initializeList();
		List* t = readFile(readAt);

		NUMBER_OF_TASKS = t->size;
		aux_t = copyList(&t, &aux_t); //desalocar este aux_t

		
		List** c = generate_layers(t);
		
		clock_t tic = clock();
		Solution* s = initialSolution(c);
		printf("obj:: %f; cost: %f\n", s->f_obj, s->f_cost);
		clock_t toc = clock();
		
		printSolution(s, NULL);
		
		double executed = (double)(toc - tic) / CLOCKS_PER_SEC;

		if(infos)
			fprintf(fp, "%s; %f; %f; %d; %f; %f\n", fileName, s->f_obj, s->f_cost, s->size_j, s->duration, executed);
		
		if(i_sol)
			printSolution(s, fp_is);
		

		printf("File %s read!\n", fileName);

		free(fileName);

		if(dot)
			free(saveAt);
		free(readAt);

		freeSolution(s);
		free(s);

		freeLayers(c);
		freeList(t);
		freeList(aux_t);
	}
   	fclose(fp);
   	fclose(fp_is);
}

int main(){
	generateInitialSolution2AllFiles(0,1,1);
	return 0;
}