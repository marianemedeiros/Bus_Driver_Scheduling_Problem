#include "threads.h"

Solution_Thread* inicialize_Solution_thread(int p_id){
	Solution_Thread* solution_thread = (Solution_Thread*) calloc(1, sizeof(Solution_Thread));
	solution_thread->thread_id = p_id;
	solution_thread->log_file = vet_files[solution_thread->thread_id-1];
	return solution_thread;
}

void free_Solution_thread(Solution_Thread* s){
	free(s);
}

Solution* acess_sharedMemory(Solution* x, int thread_id, double executed_t, char* ls_name, int while_){
	int flag = 0;
	if(shared_memory == NULL){
		#ifdef DEBUG_SM
			fprintf(debug, "---- THREAD %d updated first time sharedMemory to %f. \n" , thread_id, x->f_obj);
		#endif
		shared_memory = copySolution(x);
		flag = 1;
	}
	else if(OBJ(shared_memory->f_obj, x->f_obj)){//update shared memory
		#ifdef DEBUG_SM
			fprintf(debug, "---- THREAD %d update sharedMemory from %f to %f.\n" , thread_id, shared_memory->f_obj, x->f_obj);
		#endif

		freeSolution(shared_memory);
		free(shared_memory);
		shared_memory = copySolution(x);
		flag = 1;

	}else if(double_way && OBJ(x->f_obj, shared_memory->f_obj)){//update thread solution
		#ifdef DEBUG_SM
			fprintf(debug, "---- sharedMemory update solution of THREAD %d from %f to %f. \n" , thread_id, x->f_obj, shared_memory->f_obj);
		#endif
		freeSolution(x);
		free(x);
		x = copySolution(shared_memory);
	}

    if(best_solution == NULL || OBJ(best_solution->f_obj, shared_memory->f_obj)){
        if(best_solution != NULL){
            freeSolution(best_solution);
            free(best_solution);
        }
        best_solution = copySolution(shared_memory);
        writeFileInfos(best_infos, executed_t , thread_id, best_solution->f_cost, best_solution->f_obj, best_solution->size_j, ls_name, while_, fo_count, k);
    }

	//if flag == 1, write in shared memory log file informations about the solution in shared memory.
	if(flag)
		writeFileInfos(shared_memory_infos, executed_t , thread_id, shared_memory->f_cost, shared_memory->f_obj, shared_memory->size_j, ls_name, while_, fo_count, k);
    

	return x;
}

void update_vns_variables(){
	finished_functions = 0;
	
	struct timeval t_i_free, t_o_free;
	gettimeofday(&t_i_free, NULL);
	freeSolution(s_shake);
	free(s_shake);
	s_shake = NULL;
	gettimeofday(&t_o_free, NULL);
	double free_executed = (t_o_free.tv_sec - t_i_free.tv_sec);	


	if(OBJ(obj_sm, shared_memory->f_obj)){
		#ifdef DEBUG_VNS
			printObjVNS(k, shared_memory->f_obj);
		#endif
		k = 1;
	}else{
		k++; 	
	}

	int stop_c = CONDITION(shared_memory->f_obj, free_executed, 1);
	if(k <= K_MAX && stop_c){
		obj_sm = shared_memory->f_obj;

		#ifdef DEBUG
			//printf("(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, shared_memory->f_obj, thread_executed);
			fprintf(debug, "\n(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, shared_memory->f_obj, thread_executed);
		#endif
		struct timeval t_i_copy, t_o_copy;
		gettimeofday(&t_i_copy, NULL);
		Solution* cp = copySolution(shared_memory);
		gettimeofday(&t_o_copy, NULL);
		copy_executed = (t_o_copy.tv_sec - t_i_copy.tv_sec);	

		struct timeval t_i_shake, t_o_shake;
		gettimeofday(&t_i_shake, NULL);
		s_shake = shake(cp, k);
		gettimeofday(&t_o_shake, NULL);
		shake_executed = (t_o_shake.tv_sec - t_i_shake.tv_sec);
		#ifdef DEBUG
			fprintf(timeout, "%d; %f; %f; %f; %f\n", k, copy_executed, shake_executed, thread_executed, free_executed);
		#endif
	}else if(k > K_MAX || stop_c == -1){
		//printf("k > K_MAX || stop_c == -1\n");
		vns_not_end = 0;
	}
}

void option_1(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    Solution* s = NULL;
    pthread_mutex_lock(&mutex_start);
    pthread_cond_wait(&cond_start, &mutex_start);
    pthread_mutex_unlock(&mutex_start);
    //printf("THR %d started ... ", thread_id);
    int vns_it = 1, flag_while1 = 1, while_ = 1, aux_finish_functions = 0;
    struct timeval time_start_thr, time_end_thr, time_s, time_t;
    
    int it = 0;
    do{
    	if(vns_it == 1){
        	it = 0;
        	gettimeofday(&time_start_thr, NULL);
        	s = copySolution(s_shake);
        	vns_it = 0;
    	}
    	it++;
    	gettimeofday(&time_s, NULL);
    	Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
    	gettimeofday(&time_t, NULL);
	    double executed_t = (time_t.tv_sec - time_s.tv_sec);

    	//compare local search s with shared memory s.
    	sem_wait(&semaphore_shared_memory);
    	s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
    	sem_post(&semaphore_shared_memory);
        
    	//update log file of thread.	
    	writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_, fo_count, -1);

    	//compare s_line with local search s.
    	if(OBJ(s->f_obj, s_line->f_obj)){
        	freeSolution(s);
        	free(s);
        	s = s_line;
    	}else{
	        freeSolution(s_line);
	        free(s_line);

	        flag_while1 = 0;

	        sem_wait(&semaphore_finished_functions);
	        finished_functions++;
	        aux_finish_functions = finished_functions;
	        sem_post(&semaphore_finished_functions);

	        if(aux_finish_functions < used_local_search){
	        	//printf("THR %d while_2\n", thread_id);
	        	while_ = 2;
	        	Solution* copy = copySolution(s);
	        	freeSolution(s);
	        	s = shake(copy, k);	
	        }
	        else if(aux_finish_functions >= used_local_search){
	        	gettimeofday(&time_end_thr, NULL);
	        	sem_wait(&semaphore_thread_executed);
	        	thread_executed = (time_end_thr.tv_sec - time_start_thr.tv_sec);
	        	sem_post(&semaphore_thread_executed);
	        	vns_it = 1;
	        	flag_while1 = 1;
	        	aux_finish_functions = 0;
	        	pthread_barrier_wait(&barrier);

	        	if(thread_id == 1){
	            	update_vns_variables();
	            	if(CONDITION(shared_memory->f_obj, thread_executed, flag_while1) == -1){
	            		vns_not_end = 0;
	            	}
	        	}
	        	pthread_barrier_wait(&barrier);
	    	}
    	}
    }while((flag_while1 || aux_finish_functions < used_local_search) && vns_not_end);
    //printf("BARREIRA3 ... THR %d. \n", thread_id);
    pthread_barrier_wait(&barrier);
    if(thread_id == 1)
    	pthread_cond_signal(&cond_vns);
    freeSolution(s);
    free(s);
}

void option_2(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    Solution* s = NULL;
    pthread_mutex_lock(&mutex_start);
    pthread_cond_wait(&cond_start, &mutex_start);
    pthread_mutex_unlock(&mutex_start);
    int vns_it = 1, flag_while1 = 1, while_ = 1;
    struct timeval time_start_thr, time_end_thr, time_s, time_t;
    int it = 0;
    do{
    	if(vns_it == 1){
        	it = 0;
        	gettimeofday(&time_start_thr, NULL);
        	s = copySolution(s_shake);
        	vns_it = 0;
    	}
    	it++;
    	gettimeofday(&time_s, NULL);
    	Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
    	gettimeofday(&time_t, NULL);
	    double executed_t = (time_t.tv_sec - time_s.tv_sec);

    	//compare local search s with shared memory s.
    	sem_wait(&semaphore_shared_memory);
    	s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
    	sem_post(&semaphore_shared_memory);
        
    	//update log file of thread.	
    	writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_, fo_count, -1);

    	//compare s_line with local search s.
    	if(OBJ(s->f_obj, s_line->f_obj)){
        	freeSolution(s);
        	free(s);
        	s = s_line;
    	}else{
        	freeSolution(s_line);
        	free(s_line);
			flag_while1 = 0;

       		gettimeofday(&time_end_thr, NULL);
        	sem_wait(&semaphore_thread_executed);
        	thread_executed = (time_end_thr.tv_sec - time_start_thr.tv_sec);
        	sem_post(&semaphore_thread_executed);
        	vns_it = 1;
        	flag_while1 = 1;
            
        	pthread_barrier_wait(&barrier);
        	if(thread_id == 1){
        		update_vns_variables();
        		if(CONDITION(shared_memory->f_obj, thread_executed, flag_while1) == -1){
            		vns_not_end = 0;
        		}
        	}
        	pthread_barrier_wait(&barrier);
    	}
    }while((flag_while1) && vns_not_end);
    pthread_barrier_wait(&barrier);
    if(thread_id == 1)
    	pthread_cond_signal(&cond_vns);
    freeSolution(s);
    free(s);
}

void option_3(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    Solution* s = copySolution(s_shake);
    int improvement = 1;
    struct timeval time_s, time_t, time_s_all, time_t_all;
    double time_all = 0.0;
    //int it = 0;
    while(CONDITION(s->f_obj, time_all, improvement) != -1){
    	gettimeofday(&time_s_all, NULL);
    	//it++;
    	improvement = -1;
    	gettimeofday(&time_s, NULL);
    	Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
    	gettimeofday(&time_t, NULL);
	    double executed_t = (time_t.tv_sec - time_s.tv_sec);

    	//compare local search s with shared memory s.
    	sem_wait(&semaphore_shared_memory);
    	s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, 1);
    	sem_post(&semaphore_shared_memory);
    	
    	//compare s_line with local search s.
    	if(OBJ(s->f_obj, s_line->f_obj)){
        	freeSolution(s);
        	free(s);
       		s = s_line;
        	improvement = 1;
    	}else{
        	freeSolution(s_line);
        	free(s_line);
    	}
    	//update log file of thread.	
    	writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, op_name, 1, fo_count, -1);
    	gettimeofday(&time_t_all, NULL);
    	time_all = (time_t_all.tv_sec - time_s_all.tv_sec);
    }
    freeSolution(s);
    free(s);
    //printf("thread %d , made %d iterations..\n", thread_id, it);
}

void option_4(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    Solution* s = copySolution(s_shake);
    int improvement = 1, aux_finish_functions = 0, while_ = 1;
    struct timeval time_s, time_t, time_s_all, time_t_all;
    double time_all = 0.0;
    //int it = 0;
    while(CONDITION(s->f_obj, time_all, improvement) != -1 || aux_finish_functions < used_local_search){
    	gettimeofday(&time_s_all, NULL);
    	//it++;
    	improvement = -1;
    	gettimeofday(&time_s, NULL);
    	Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
    	gettimeofday(&time_t, NULL);
	    double executed_t = (time_t.tv_sec - time_s.tv_sec);
    	
    	//compare local search s with shared memory s.
    	sem_wait(&semaphore_shared_memory);
    	s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
    	sem_post(&semaphore_shared_memory);
    	
    	//compare s_line with local search s.
    	if(OBJ(s->f_obj, s_line->f_obj)){
        	freeSolution(s);
        	free(s);
        	s = s_line;
        	improvement = 1;
    	}else{
       		freeSolution(s_line);
        	free(s_line);

        	sem_wait(&semaphore_finished_functions);
        	finished_functions++;
        	aux_finish_functions = finished_functions;
        	sem_post(&semaphore_finished_functions);

        	if(aux_finish_functions < used_local_search){
        		while_ = 2;
        		Solution* copy = copySolution(s);
        		freeSolution(s);
        		s = shake(copy, k);
        	}
    	}
    	//update log file of thread.	
    	writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, op_name, while_, fo_count, -1);
    	gettimeofday(&time_t_all, NULL);
    	time_all = (time_t_all.tv_sec - time_s_all.tv_sec);
    }

    freeSolution(s);
    free(s);
    //printf("thread %d , made %d iterations..\n", thread_id, it);
}

void option_5(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    Solution* s = copySolution(s_shake);
    struct timeval time_s, time_t;
    struct timeval time_start_op, time_end_op;
    double time_all = 0.0;

    int improvement = 1, while_ = 1;
    while(CONDITION(s->f_obj, time_all, improvement) != -1){
    	gettimeofday(&time_start_op, NULL);
    	improvement = -1;
    	gettimeofday(&time_s, NULL);
    	Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
    	gettimeofday(&time_t, NULL);
	    double executed_t = (time_t.tv_sec - time_s.tv_sec);
    	 
    	
    	//compare local search s with shared memory s.
    	sem_wait(&semaphore_shared_memory);
    	s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
    	sem_post(&semaphore_shared_memory);
    	
    	//compare s_line with local search s.
    	if(OBJ(s->f_obj, s_line->f_obj)){
        	freeSolution(s);
        	free(s);
        	s = s_line;
        	improvement = 1;
    	}else{
        	freeSolution(s_line);
        	free(s_line);
    	}
    	//update log file of thread.	
    	writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, op_name, while_, fo_count, -1);
   		gettimeofday(&time_end_op, NULL);
   		time_all = (time_end_op.tv_sec - time_start_op.tv_sec);
    }

    //second search
    sm_vet[thread_id] = copySolution(s);
    improvement = 1;
    int pos = 0;
    do{
    	pos = 0 + rand() % ((used_local_search-1) + 1 - 0);
    }while(pos == thread_id);
    	if(sm_vet[pos] != NULL && sm_vet[pos]->f_obj != s->f_obj){
    		printf("POS::: %d; %f \n", pos, sm_vet[pos]->f_obj);
    		s = copySolution(sm_vet[pos]);
    		struct timeval time_start_op, time_end_op;
    		double time_all = 0.0;

	    	while(time_all < (double) time_vnsp_2){
		    	//while(improvement){
		        gettimeofday(&time_start_op, NULL);
		        improvement = -1;
		        gettimeofday(&time_s, NULL);
	    		Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
	    		gettimeofday(&time_t, NULL);
		    	double executed_t = (time_t.tv_sec - time_s.tv_sec);
		        
		        //compare local search s with shared memory s.
		        sem_wait(&semaphore_shared_memory);
		        s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		        sem_post(&semaphore_shared_memory);
		        
		        //compare s_line with local search s.
		        if(OBJ(s->f_obj, s_line->f_obj)){
		        	freeSolution(s);
		        	free(s);
		        	s = s_line;
		        	improvement = 1;
                    s = copySolution(sm_vet[pos]);
		        }else{
		        	freeSolution(s_line);
		        	free(s_line);
		        }
		        //update log file of thread.	
		        writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, op_name, while_, fo_count, pos);

		        gettimeofday(&time_end_op, NULL);
		        time_all = (time_end_op.tv_sec - time_start_op.tv_sec);
		        printf("time_all: %f; time_vnsp_2: %f (s %f)\n", time_all, time_vnsp_2, s->f_obj);
	    	}
    	}
    freeSolution(s);
    free(s);
}

void option_6(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
    //printf("VNSP_ALL\n");
    Solution* s = copySolution(s_shake);
    struct timeval time_s, time_t;
    struct timeval time_start_op, time_end_op;
    double time_all = 0.0;

    int improvement = 1, while_ = 1;
    while(CONDITION(s->f_obj, time_all, improvement) != -1){
        gettimeofday(&time_start_op, NULL);
        improvement = -1;
        gettimeofday(&time_s, NULL);
        Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, thread_id);
        gettimeofday(&time_t, NULL);
        double executed_t = (time_t.tv_sec - time_s.tv_sec);
         
        
        //compare local search s with shared memory s.
        sem_wait(&semaphore_shared_memory);
        s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
        sem_post(&semaphore_shared_memory);
        
        //compare s_line with local search s.
        if(OBJ(s->f_obj, s_line->f_obj)){
            freeSolution(s);
            free(s);

            //freeSolution(sm_vet[thread_id]);
            //free(sm_vet[thread_id]);            

            sm_vet[thread_id] = copySolution(s_line);

            int pos = 0;

            do{
                pos = 0 + rand() % ((used_local_search-1) + 1 - 0);
            }while(pos == thread_id || sm_vet[pos] == NULL);

            s = copySolution(sm_vet[pos]);

            improvement = 1;
        }else{
            freeSolution(s_line);
            free(s_line);
        }
        //update log file of thread.    
        writeFileInfos(log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, op_name, while_, fo_count, -1);
        gettimeofday(&time_end_op, NULL);
        time_all = (time_end_op.tv_sec - time_start_op.tv_sec);
    }

    freeSolution(s);
    free(s);
}

void local_search_body(Solution* (*fun_ptr)(Solution*, int, int), int thread_id, char* op_name, FILE* log_file, int k_swap){
	if(used_vns_p == 1 && second_cond == 1){
		option_1(fun_ptr, thread_id, op_name, log_file, k_swap);
	}
	else if(used_vns_p == 1 && second_cond == 0){
		option_2(fun_ptr, thread_id, op_name, log_file, k_swap);
	}
	else if(used_vns_p == 2 && second_cond == 0){
		option_3(fun_ptr, thread_id, op_name, log_file, k_swap);
	}
	else if(used_vns_p == 2 && second_cond == 1){
		option_4(fun_ptr, thread_id, op_name, log_file, k_swap);
	}
	//else if(used_vns_p == 3){
	//	option_5(fun_ptr, thread_id, op_name, log_file, k_swap);
	//}
    else if(used_vns_p == 3){
        option_6(fun_ptr, thread_id, op_name, log_file, k_swap);
    }

}

