#include "readInstances.h"

void freeTaskVector(){
	for (int i = 0; i < index_task_vector; i++){
		freeTask(task_vector[i]);
		//free(task_vector[i]);
	}
	free(task_vector);
}

Task* readLine(char* line){
	Task* t = inicializeTask();
	int finish_h = 0;
	int finish_m = 0;
	int t_out = 0;
	int m_out = 0;

	int h_saida = 0;
	int m_saida = 0;
	int duracao = 0;
	int bus = 0;

	int flag_d = 0, j = 0;
	for (int i = 0; i < strlen(line); i++) {
		if(line[i] == ',')
			flag_d++;

		if(line[i] != ',' && line[i] != '\"' && flag_d == 0){//bus line
			t->bus_line[j] = line[i];
			j++;
		}
		if(line[i] != ',' && line[i] != '\"' && flag_d == 1){//origin
			t->origin = line[i];
		}
		if(line[i] != ',' && line[i] != '\"' && flag_d == 2){//destino
			t->destination = line[i];
		}

		if(line[i] != ',' && line[i] != '\"' && flag_d == 3){	//hora da saida
			if(line[i+1] != ','){
				char* aux = (char*) calloc(3, sizeof(char));
				aux[0] = line[i]; aux[1] = line[i+1];
				h_saida = atoi(aux);
				free(aux);
				i++;
			}else
				h_saida = atoi(&line[i]);
		}

		
		if(h_saida == 25)
			h_saida = 1;
		else if(h_saida == 26)
			h_saida = 2;
		else if(h_saida == 27)
			h_saida = 3;
		else if(h_saida == 28)
			h_saida = 4;
		else if(h_saida == 29)
			h_saida = 5;
		else if(h_saida == 30)
			h_saida = 6;
		

		if(line[i] != ',' && line[i] != '\"' && flag_d == 4){//minuto da saida
			if(line[i+1] != ','){
					char* aux = (char*) calloc(3, sizeof(char));
					aux[0] = line[i]; aux[1] = line[i+1];
					m_saida = atoi(aux);
					free(aux);
					i++;
			}else
				m_saida = atoi(&line[i]);

		}

		if(line[i] != ',' && line[i] != '\"' && flag_d == 5){//duracao
			//printf("line[i]: %c\n", line[i]);
			if(line[i+1] != ','){
					char* aux = (char*) calloc(4, sizeof(char));
					aux[0] = line[i]; aux[1] = line[i+1];
					if(line[i+2] != ','){
						aux[2] = line[i+2];
						//printf("tres casas decimais: %s\n", aux);
						i++;
					}
					duracao = atoi(aux);
					free(aux);
					i++;
			}else
				duracao = atoi(&line[i]);

			int aux = m_saida + duracao;
			finish_h = h_saida;
			finish_m = aux;
		}

		if(line[i] != ',' && line[i] != '\"' && flag_d == 6){//bus
			if(line[i+1] != LINE_FEED || line[i+1] != ENTER){
				char* aux = (char*) calloc(4, sizeof(char));
				aux[0] = line[i]; aux[1] = line[i+1];
				if(line[i+2] != LINE_FEED || line[i+2] != ENTER)
					aux[2] = line[i+2];
				bus = atoi(aux);
				free(aux);
			}else
				bus = atoi(&line[i]);
			i = strlen(line);
		}

		t_out = h_saida;
		m_out = m_saida;
		t->duration = duracao;
		t->bus_number = bus;

	}
	
	t->t_out = t_out;
	t->m_out = m_out;
	t->finish_h = finish_h;
	t->finish_m = finish_m;
	
	setData2DateTime(t->start_time, t_out, m_out);
	//printf("------- %d -- %d\n", finish_h, finish_m);
	setData2DateTime(t->end_time, finish_h, finish_m);
	//printf("----------------------\n");
	return t;
}

List* readFile(char* url){
FILE* arq = openFile(url, "rt");
char* line = (char*) calloc(1000, sizeof(char));
int n_line = 0, key = 0;
List* tasks = initializeList();

	if(!arq){
	     perror("Can't open file.");
 		exit(1);
	}else{
		while(!feof(arq)){
			if(fgets(line, 255, arq) != NULL){
				if(n_line == 1){
					NUMBER_TASKS = atoi(line);
				}
				if(n_line >= 2 && n_line <= NUMBER_TASKS+1){
					//verify task beginning to insert that at the corret place in list. The objective here is ordenate list by
					// start times.

					Task* newT = readLine(line);
					newT->key = key;
					key++;

					if(tasks->size == 0){
						addLastList(tasks, newT);
					}else{
						Node* aux = tasks->first;
						int index = 0, add = 0;
						while(aux != NULL){
							//if(newT->t_out < aux->data->t_out){
							if(compareDateTime(newT->start_time, aux->data->start_time)){
								addList(tasks, newT, index);
								add = 1;
								aux = tasks->last;
							}
							//else if(newT->t_out == aux->data->t_out && newT->m_out < aux->data->m_out){
							//	addList(tasks, newT, index);
							//	add = 1;
							//	aux = tasks->last;
							//}
							aux = aux->next;
							index++;
						}
						if(add == 0){
							addLastList(tasks, newT);
						}
					}
					//end
				}
				n_line++;
			}

   	 	}
	}
free(line);
fclose(arq);
NUMBER_OF_TASKS = tasks->size;

TASK_LIST = initializeList();
TASK_LIST = copyList(&tasks, &TASK_LIST); //make a copy of tasks list

index_task_vector = 0;
task_vector = (Task**) calloc(NUMBER_TASKS, sizeof(Task*));
Node* node = TASK_LIST->first;
	while(node != NULL){
		Task* aux = inicializeTask();
		aux = copyTask(&node->data, &aux);
		task_vector[index_task_vector] = aux;
		index_task_vector++;
		node = node->next;
	}
return tasks;
}



