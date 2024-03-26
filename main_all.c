#include "restriction_evaluator/restriction_evaluator.h"
#include "libraries/metaheuristics/vns_s.h"
#include "libraries/metaheuristics/vns_p.h"
#include <unistd.h>

#define SHARED_MEMORY_LOG_INFOS "SHARED_MEMORY_LOG_INFOS.txt"
#define SHARED_MEMORY_LOG_DETAILS "SHARED_MEMORY_LOG_DETAILS.txt"

#define BEST_LOG_INFOS "BEST_LOG_INFOS.txt"
#define BEST_LOG_DETAILS "BEST_LOG_DETAILS.txt"

#define gvns_c "gvns"
#define vnsp_1_v1 "vnsp_1_v1"
#define vnsp_1_v2 "vnsp_1_v2"
#define vnsp_2 "vnsp_2"


int main(int argc, char **argv){
	time_t seed_rand = time(0);
	srand(seed_rand);
	char* algo = NULL;
	char* file_n = NULL;
	char* it = NULL;
	shared_memory = NULL;
	best_solution = NULL;
	used_local_search = OPERATORS;
	obj_value_constant = -1;
	second_cond = 1;
	double_way = 1;
	time_constant = -1.0;
	time_vnsp_2 = 1.0;
	int opt, h = 0, _gvns = 0, local_search = 0;

  	while((opt = getopt(argc, argv, "a:f:i:o:l:s:w:d:t:v:h")) != -1) {
    	switch (opt){
    		case 'a':
            	algo = optarg;
            	break;
        	case 'f':
            	file_n = optarg;
            	break;

        	case 'i':
        		it = optarg;
            	break;

        	case 'o':
            	used_local_search = atoi(optarg);
            	break;

            case 'l':
            	local_search = atoi(optarg);
            	break;

            case 's':
            	obj_value_constant = atoi(optarg);
            	break;
            
            case 'w':
            	second_cond = atoi(optarg);
            	break;
        	
        	case 'd':
            	double_way = atoi(optarg);
            	break;

        	case 't':
            	time_constant = atof(optarg);
            	break;

        	case 'v':
            	time_vnsp_2 = atof(optarg);
            	break;

        	case 'h':
        		printf("-a: algorithm that will be executed (gvns, vnsp_1_v1, vnsp_1_v2), by default is vnsp_1_v1.\n");
        		printf("-f: file to be read.\n");
        		printf("-i: iteration (1 ... 30)\n");
        		printf("-o: how many operator will be executed, by default this is 36.\n");
        		printf("-l: local search used at sequencial vns. (1: vnd; 2: local_search_1; 3: local_search_2).\n");
        		printf("-s: \n");
        		printf("-w: \n");
        		printf("-d: \n");
        		printf("-t: \n");
        		printf("-v: \n");
        		h = 1;
        		break;
		}
  	}
  	
	if( h == 0){
		//Dir and Log Files
		char* readAt = strcat(nameFile(INSTANCES, file_n), ".txt");	
		char* dir_logs = NULL;
		if(algo == NULL || strcmp(algo, vnsp_1_v1) == 0){
			used_vns_p = 1;
			dir_logs = createDirectory("vnsp_1_v1/", file_n, it);
			openKfiles(dir_logs, used_local_search);// open all files to be used.
			finished_functions = 0;
			assingLocalSearchFunctions_w0d1();
			//assingLocalSearchFunctions_w1d1();
			sem_init(&semaphore_shared_memory, 0, 1); // init semaphore
			sem_init(&semaphore_finished_functions, 0, 1);  // init semaphore
			sem_init(&semaphore_thread_executed, 0, 1);  // init semaphore
			pthread_mutex_init(&mutex_start, NULL); // init mutex
			pthread_mutex_init(&mutex_vns, NULL); // init mutex
			pthread_cond_init(&cond_start, NULL); //init conditional 
			pthread_cond_init(&cond_vns, NULL); //init conditional
			pthread_barrier_init(&barrier, NULL, used_local_search);  // init barrier
			s_t  = init_threads(); // init threads
		}
		else if(strcmp(algo,vnsp_1_v2) == 0){
			used_vns_p = 2;
			dir_logs = createDirectory("vnsp_1_v2/", file_n, it);
			openKfiles(dir_logs, used_local_search);// open all files to be used.
			finished_functions = 0;
			assingLocalSearchFunctions();
			sem_init(&semaphore_shared_memory, 0, 1); // init semaphore
			sem_init(&semaphore_finished_functions, 0, 1);  // init semaphore
		}
		else if(strcmp(algo,vnsp_2) == 0){
			used_vns_p = 3;
			if(time_constant != -1.0)
				time_vnsp_2 = time_constant;	
			//printf("time_constant %f\n", time_constant);
			printf("time_vnsp_2 %f\n", time_vnsp_2);

			dir_logs = createDirectory("vnsp_2/", file_n, it);
			openKfiles(dir_logs, used_local_search);// open all files to be used.
			finished_functions = 0;
			assingLocalSearchFunctions();
			sem_init(&semaphore_shared_memory, 0, 1); // init semaphore
			sem_init(&semaphore_finished_functions, 0, 1);  // init semaphore
		}
		else if(strcmp(algo,gvns_c) == 0){
			if(local_search == 0)
				local_search = 3;
			_gvns = 1;
			dir_logs = createDirectory("gvns_c/", file_n, it);
		}

		List* t = readFile(readAt);//read tasks
		//printList(TASK_LIST, 0 , 0, NULL);
		
		
		List** c = generate_layers(t);// generate layers
		//printf("LAYERS -- %d\n", LAYERS_SIZE);
		//printLayers(c);

		struct timeval t1, t2;
    	double elapsedTime;

		gettimeofday(&t1, NULL);
		Solution* initial_s = initialSolution(c);
		gettimeofday(&t2, NULL);
		elapsedTime = (t2.tv_sec - t1.tv_sec);
		//printSolution(shared_memory, NULL);
		//verify_restriction(shared_memory);

		
		#ifdef DEBUG 
			char* d = nameFile(dir_logs, "DEBUG");
			debug = openFile(d, "w");
			char* t_p = nameFile(dir_logs, "TIMEOUT");
			timeout = openFile(t_p, "w");

			printf("Initial Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n", initial_s->size_j, initial_s->f_obj, initial_s->f_cost, initial_s->duration);
			fprintf(debug, "Initial Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n", initial_s->size_j, initial_s->f_obj, initial_s->f_cost, initial_s->duration);
			fprintf(debug, "Time elapsed to build initial solution: %f seconds\n\n" , elapsedTime);
			fprintf(timeout, "rand seed: %ld\n", seed_rand);
			fprintf(timeout, "k; copy; shake; local_search; free\n");
		#endif

		char* n1 = nameFile(dir_logs, SHARED_MEMORY_LOG_INFOS);
		shared_memory_infos = openFile(n1, "w");
		fprintf(shared_memory_infos, "execution_time; local_search_id; cost_function; objective_function; number of journeys; objective function\n");
		writeFileInfos(shared_memory_infos, elapsedTime , -1, initial_s->f_cost, initial_s->f_obj, initial_s->size_j, "IS", 0, fo_count, -1);
		
		char* nBest = nameFile(dir_logs, BEST_LOG_INFOS);
		best_infos = openFile(nBest, "w");
		fprintf(best_infos, "execution_time; local_search_id; local_search_name; cost_function; objective_function; number_of_journeys; improved_at_second_while; count_of_time_that_objective_function_are_made; k_of_vns\n");
		writeFileInfos(best_infos, elapsedTime , -1, initial_s->f_cost, initial_s->f_obj, initial_s->size_j, "IS", 0, fo_count, -1);

		Solution* s = NULL;
		fo_count = 0;
		elapsedTime = 0.0;
		shared_memory = initial_s;
		
		if(_gvns){
			gettimeofday(&t1, NULL);
			s = vns(copySolution(initial_s), local_search);
			//s = shake(copySolution(initial_s), 2);
			gettimeofday(&t2, NULL);
		}else if(used_vns_p == 1){
			gettimeofday(&t1, NULL);
			vns_P(copySolution(initial_s));
			gettimeofday(&t2, NULL);
			s = best_solution;
		}else if(used_vns_p == 2){
			gettimeofday(&t1, NULL);
			vns_P_2(copySolution(initial_s));
			s = best_solution;
			gettimeofday(&t2, NULL);
		}else if(used_vns_p == 3){
			gettimeofday(&t1, NULL);
			vns_P_2(copySolution(initial_s));
			s = best_solution;
			gettimeofday(&t2, NULL);
		}
		
		
		elapsedTime = (t2.tv_sec - t1.tv_sec);
		writeFileInfos(shared_memory_infos, elapsedTime , -1, s->f_cost, s->f_obj, s->size_j, algo, 0, fo_count, -1);
		verify_restriction(s);
		
		calculeCostFunction(s);
		calculeDuration(s);
		
		printf("Obteined Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n", s->size_j, s->f_obj, s->f_cost, s->duration);
		#ifdef DEBUG
			fprintf(timeout, "all %s: %f \n\n", algo, elapsedTime);
			fprintf(debug, "Obteined Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n", s->size_j, s->f_obj, s->f_cost, s->duration);
		#endif
		

		/*writing solution of shared memory*/
		char* n2 = nameFile(dir_logs, SHARED_MEMORY_LOG_DETAILS);
		shared_memory_details = openFile(n2, "w");	
		printSolution(s, shared_memory_details);
		
		/*close local search log files*/
		closeFile(shared_memory_details, n2);
		closeFile(shared_memory_infos, n1);
		closeFile(debug, d);
		closeFile(timeout, t_p);
		
		if(used_vns_p == 1){
			closeKfiles(used_local_search);
			pthread_cond_destroy(&cond_start); // destroy conditional
			pthread_cond_destroy(&cond_vns); // destroy conditional
			pthread_mutex_destroy(&mutex_start);// destroy mutex
			pthread_mutex_destroy(&mutex_vns);// destroy mutex
			pthread_barrier_destroy(&barrier); // destroy barrier
			join_threads(s_t);
		}
		
		freeSolution(initial_s);
		free(initial_s);
		freeSolution(s);
		free(s);
		
		freeList(t);
		freeList(TASK_LIST);
		freeTaskVector();	
		freeLayers(c);
		free(readAt);
		free(dir_logs);
	}
	return 0;
}
