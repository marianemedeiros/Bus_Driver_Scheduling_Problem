#include "cut.h"

void printCutJounerys(Journey** j1, Journey** j2, Journey** j3, int size){
	printf("-------------------------------J1:::\n");
	for (int i = 0; i < size; i++){
		if(j1[i] != NULL){
			printf("\nj1[%d] <<%f>>\n", i, j1[i]->_obj);
			printJourney(&j1[i], NULL);
		}
	}
	printf("-------------------------------J2:::\n");
	for (int i = 0; i < size; i++){
		if(j2[i] != NULL){
			printf("\nj2[%d] <<%f>>\n", i, j2[i]->_obj);
			printJourney(&j2[i], NULL);
		}
	}
	if(j3 != NULL){
		printf("-------------------------------J3:::\n");
		for (int i = 0; i < size; i++){
			if(j3[i] != NULL){
				printf("\nj3[%d] <<%f>>\n", i, j3[i]->_obj);
				printJourney(&j3[i], NULL);
			}
		}
	}

}

//gerar locais de corte nas tarefas T, que foram combinadas e geraram a solução inicial.
//Na dissertação do Allanclair esta que pra essa função deve ser passado a solução, no entanto n]ao é necessário
//a solução em si, mas sim as tarefas ordenadas de forma crescente de tempo de inicio das tarefas que compoem a solução inicial,
// que é o conjunto T. O retorno desta função será os locais de corte para a soluçao. (ver pag 48)
int* generate_cut_places(){
	int* K = (int*) calloc(LAYERS_SIZE, sizeof(int));
	int step = NUMBER_TASKS / LAYERS_SIZE;
	//printf("stp: %d\n", step);
	for (int i = 1; i < LAYERS_SIZE+1; i++){
		K[i-1] = task_vector[step*i]->start_time->hours2minutes;
		//printf("%d - %d\n", step*i, task_vector[step*i]->start_time->hours2minutes);
	}
	return K;
}

int generate_cut_places_shake(Solution* s, int shake2){
	//printf("min_start_time: %d; min_end_time: %d\n", min_start_time, min_end_time);
	int sliceN = 0;
	int st = min_start_time;// first task
	int et = 0;
	if(shake2)
		et = min_end_time - 60;//last task
	else 
		et = min_end_time;

	sliceN = st + rand() % (et + 1 - st);
	return sliceN;
}

void verifyCutPlace(Solution* s, int k, int* s1_i, int* s2_i){
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < s->size_j; i++){
		if(flag1)
			(*s1_i)++;
		if(flag2)
			(*s2_i)++;

		flag1 = 0; flag2 = 0;
		
		Node* aux = s->j[i]->tasks->first;
		while(aux != NULL){
			if(aux->data->start_time->hours2minutes <= k){// vai para s1
				flag1 = 1;
			}else if(aux->data->start_time->hours2minutes > k){//vai pra s2
				flag2 = 1;
			}
			aux = aux->next;
		}
	}

	if(flag1)
		(*s1_i)++;
	
	if(flag2)
		(*s2_i)++;
	//printf("verifyCutPlace: sj1: %d; sj2: %d\n", *s1_i, *s2_i);
}

void cut2places(Journey** j, int size_j, int k1, int k2,Journey** j1, Journey** j2, Journey** j3, int* s1_i, int* s2_i, int* s3_i){
	int flag1 = 0, flag2 = 0, flag3 = 0;
	for (int i = 0; i < size_j; i++){
		if(flag1)
			(*s1_i)++;
		if(flag2)
			(*s2_i)++;
		if(flag3)
			(*s3_i)++;

		flag1 = 0; flag2 = 0; flag3 = 0;
		Node* aux = j[i]->tasks->first;
		while(aux != NULL){
			if(aux->data->start_time->hours2minutes <= k1){// vai para s1
				flag1 = 1;
				if(j1[i] == NULL){
					j1[i] = inicializeJourney();
					j1[i]->key = i;
				}
				Task* t = inicializeTask();
				t = copyTask(&aux->data, &t);
				addLastList(j1[i]->tasks, t);
			}else if(aux->data->start_time->hours2minutes > k1 && aux->data->start_time->hours2minutes < k2){//vai pra s2
				flag2 = 1;
				if(j2[i] == NULL){
					j2[i] = inicializeJourney();
					j2[i]->key = i;
				}
				Task* t = inicializeTask();
				t = copyTask(&aux->data, &t);
				addLastList(j2[i]->tasks, t);
			}else if(aux->data->start_time->hours2minutes >= k2){//vai pra s3
				flag3 = 1;
				if(j3[i] == NULL){
					j3[i] = inicializeJourney();
					j3[i]->key = i;
				}
				Task* t = inicializeTask();
				t = copyTask(&aux->data, &t);
				addLastList(j3[i]->tasks, t);
			}			
			aux = aux->next;
		}
	}

	if(flag1)
		(*s1_i)++;

	if(flag2)
		(*s2_i)++;

	if(flag3)
		(*s3_i)++;

	for (int i = 0; i < size_j; i++) {
		if(j1[i] != NULL)
			j1[i]->_obj = j1[i]->obj_function(j1[i]);
	}

	for (int i = 0; i < size_j; i++) {
		if(j2[i] != NULL)
			j2[i]->_obj = j2[i]->obj_function(j2[i]);
	}

	for (int i = 0; i < size_j; i++) {
		if(j3[i] != NULL)
			j3[i]->_obj = j3[i]->obj_function(j3[i]);
	}
	//printCutJounerys(j1, j2, j3, size_j);
}

void cut(Journey** j, int size_j, int k, Journey** j1, Journey** j2, int* s1_i, int* s2_i){
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < size_j; i++){
		if(flag1)
			(*s1_i)++;
		if(flag2)
			(*s2_i)++;

		flag1 = 0; flag2 = 0;
		//if(j[i] != NULL){
			Node* aux = j[i]->tasks->first;
			while(aux != NULL){
				if(aux->data->start_time->hours2minutes <= k){// vai para s1
					flag1 = 1;
					if(j1[i] == NULL){
						j1[i] = inicializeJourney();
						j1[i]->key = i;
					}

					Task* t = inicializeTask();
					t = copyTask(&aux->data, &t);
					addLastList(j1[i]->tasks, t);
				}else if(aux->data->start_time->hours2minutes > k){//vai pra s2
					flag2 = 1;
					if(j2[i] == NULL){
						j2[i] = inicializeJourney();
						//printf("j2: %d\n", i);
						j2[i]->key = i;
					}

					Task* t = inicializeTask();
					t = copyTask(&aux->data, &t);
					addLastList(j2[i]->tasks, t);
				}			
				aux = aux->next;
			}
		//}
	}

	if(flag1)
		(*s1_i)++;

	if(flag2)
		(*s2_i)++;

	for (int i = 0; i < size_j; i++) {
		if(j1[i] != NULL)
			j1[i]->_obj = j1[i]->obj_function(j1[i]);
	}

	for (int i = 0; i < size_j; i++) {
		if(j2[i] != NULL)
			j2[i]->_obj = j2[i]->obj_function(j2[i]);
	}
	//printf("j1: %d; j2: %d\n", *s1_i, *s2_i);
	//printCutJounerys(j1, j2, NULL, size_j);
}

/*este cut, coloca de forma sequencial no vetor de jornadas as diferentes soluções geradas.
 Através desta função, s1 e s2, terão tamanhos diferentes,
referente a quantidade de jornadas que possuem jornadas menores que o valor de corte. 
Ela é opcional a função cut, porém para usar ela devemos modificar a forma
construir a matriz de custos.*/
void cut2(Journey** j, int size_j, int k, Journey** j1, Journey** j2, int* s1_i, int* s2_i){
	int flag1 = 0, flag2 = 0;
	
	for (int i = 0; i < size_j; i++){
		if(flag1)
			(*s1_i)++;
		if(flag2)
			(*s2_i)++;

		flag1 = 0; flag2 = 0;
		Node* aux = j[i]->tasks->first;
		while(aux != NULL){
			//printf("%d : %d --- %d\n", aux->data->key, aux->data->start_time->hours2minutes, k);
			//showDateTime(aux->data->start_time);
			if(aux->data->start_time->hours2minutes <= k){// vai para s1
				flag1 = 1;
				//printf("%d : %d --- %d (%d)\n", aux->data->key, aux->data->start_time->hours2minutes, k, *s1_i);
				if(j1[(*s1_i)] == NULL){
					//printf("ccccc: %d \n", *s1_i);
					j1[(*s1_i)] = inicializeJourney();
					//printf("zzzzz\n");
					j1[(*s1_i)]->key = (*s1_i);
					//printf("ddd\n");
					//s1_i++;
				}
				Task* t = inicializeTask();
				t = copyTask(&aux->data, &t);
				//printf("dddd: %d \n", *s1_i);
				/*if(j1[(*s1_i)] == NULL){
					printf("j1[(*s1_i)] é NULL\n");
				}
				else if(j1[(*s1_i)]->tasks == NULL){
					printf("j1[(*s1_i)]->tasks é NULL\n");
				}
				else if(t == NULL){
					printf("t é NULL\n");
				}*/
				addLastList(j1[(*s1_i)]->tasks, t);
			}else if(aux->data->start_time->hours2minutes >= k){//vai pra s2
				//printf("----> vai pra s2 (%d)\n", *s2_i);
				flag2 = 1;
				if(j2[(*s2_i)] == NULL){
					j2[(*s2_i)] = inicializeJourney();
					//printf("zzzzz\n");
					j2[(*s2_i)]->key = (*s2_i);
					//printf("dddd\n");
					//s2_i++;
				}
				Task* t = inicializeTask();
				t = copyTask(&aux->data, &t);
				addLastList(j2[(*s2_i)]->tasks, t);
				//printf("<<<<< %d (%d)>>>>>>\n", st->s2->j[s2_i]->tasks->last->data->key, s2_i);
			}
			aux = aux->next;
		}
	}

	if(flag1){
		(*s1_i)++;
		//Journey** tmp = (Journey**) realloc(j1, (*s1_i)* sizeof(Journey*));
		//if(tmp != NULL)
		//	j1 = tmp;
	}

	if(flag2){
		(*s2_i)++;
		//Journey** tmp = (Journey**) realloc(j2, (*s2_i)* sizeof(Journey*));
		//if(tmp != NULL)
		//	j1 = tmp;
	}
	
	for (int i = 0; i < *s1_i; i++) {
		j1[i]->_obj = j1[i]->obj_function(j1[i]);
	}

	for (int i = 0; i < *s2_i; i++) {
		j2[i]->_obj = j2[i]->obj_function(j2[i]);
	}

}