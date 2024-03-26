#include "vns_p.h"

Solution_Thread** init_threads(){
	Solution_Thread** solutions_t = (Solution_Thread**) calloc(used_local_search, sizeof(Solution_Thread*));
	for(int i = 0; i < used_local_search; i++){
		solutions_t[i] = inicialize_Solution_thread(i+1);
		pthread_create(&(threads[i]), NULL, p[i], solutions_t[i]);
	}
	return solutions_t;	
}

void join_threads(Solution_Thread** solutions_t){
	for (int i = 0; i < used_local_search; i++){
		pthread_join(threads[i], NULL);
		free_Solution_thread(solutions_t[i]);
	}
	free(solutions_t);
}

//k_max = quantidade de shakes diferentes (4)
void vns_P(Solution* s){
	vns_not_end = 1;
	k = 1;
	s_shake = NULL;
	obj_sm = 0.0;

	//thread 1 will control the iteration of vns
	//while(k <= k_max){
		//printf("\nk: %d\n", k);
		//start_time = clock();
		obj_sm = s->f_obj;
		
		#ifdef DEBUG
			//printf("\n(vns k: %d) (s->f_obj: %f)\n", k, shared_memory->f_obj);
			fprintf(debug, "\n(vns k: %d) (s->f_obj: %f)\n", k, s->f_obj);
		#endif
		
		gettimeofday(&t1_copy, NULL);
		Solution* cp = copySolution(s);
		gettimeofday(&t2_copy, NULL);
		copy_executed = (t2_copy.tv_sec - t1_copy.tv_sec);

		gettimeofday(&t1_shake, NULL);
		s_shake = shake(cp, k);
		gettimeofday(&t2_shake, NULL);
		shake_executed = (t2_shake.tv_sec - t1_shake.tv_sec);

		// signal to all threads execute their functions
		pthread_mutex_lock(&mutex_start);
		// printf("Signal to cond_start\n");
		pthread_cond_broadcast(&cond_start);
		pthread_mutex_unlock(&mutex_start);

		// cond wait to vns
		//printf("VNS Waiting ...\n");
		pthread_mutex_lock(&mutex_vns);
		pthread_cond_wait(&cond_vns, &mutex_vns);
		pthread_mutex_unlock(&mutex_vns);
	//}
}

//k_max = quantidade de shakes diferentes (4)
void vns_P_2(Solution* s){
	struct timeval time_start_all, time_end_all;
	double time_all = 0.0;
	k = 1;
	int stop_c = 1, it = 0;
	double obj_sm = s->f_obj;
	while(k <= K_MAX && stop_c != -1){
		gettimeofday(&time_start_all, NULL);
		finished_functions = 0;
		#ifdef DEBUG
			printf("\n(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, s->f_obj, time_all);
			fprintf(debug, "\n(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, s->f_obj, time_all);
		#endif
		
		gettimeofday(&t1_copy, NULL);
		Solution* cp = copySolution(s);
		gettimeofday(&t2_copy, NULL);
		copy_executed = (t2_copy.tv_sec - t1_copy.tv_sec);
		
		if(it > 0){
			gettimeofday(&t1_shake, NULL);
			s_shake = shake(cp, k);
			gettimeofday(&t2_shake, NULL);
			shake_executed = (t2_shake.tv_sec - t1_shake.tv_sec);
		}else{
			s_shake = cp;
		}
		it++;
		shared_memory = NULL;
		gettimeofday(&t1_thr_ex, NULL);
		Solution_Thread** s_t  = init_threads();
		join_threads(s_t);
		gettimeofday(&t2_thr_ex, NULL);
		double thread_executed = (t2_thr_ex.tv_sec - t1_thr_ex.tv_sec);		

		struct timeval t1_free, t2_free;
		gettimeofday(&t1_free, NULL);
		freeSolution(s_shake);
		free(s_shake);		
		s_shake = NULL;		
		gettimeofday(&t2_free, NULL);
		double free_executed = (t2_free.tv_sec - t1_free.tv_sec);		

		#ifdef DEBUG
			fprintf(timeout, "%d; %f; %f; %f; %f\n", k, copy_executed, shake_executed, thread_executed, free_executed);
		#endif

		if(OBJ(obj_sm, shared_memory->f_obj)){
			#ifdef DEBUG_VNS
				printObjVNS(k, shared_memory->f_obj);
			#endif
			k = 1;
			s = shared_memory;
			obj_sm = shared_memory->f_obj;
		}else{
			k++; 	
		}
		gettimeofday(&time_end_all, NULL);
		time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
		stop_c = CONDITION(shared_memory->f_obj, time_all, 1);
	}
}