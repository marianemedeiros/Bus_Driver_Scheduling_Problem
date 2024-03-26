#include "local_search_s.h"

Solution* vnd(Solution* s, int k_line_max){
	//printf("VND: %f\n", s->f_obj);
	int improvement = 1, it = 0;
	struct timeval time_start_all, time_end_all;
	double time_all = 0.0;

	while(CONDITION(s->f_obj, time_all, improvement) != -1){
		gettimeofday(&time_start_all, NULL);
		Solution* s_line = NULL;
		int k = 1;
		it++;
		improvement = -1;
		while(k <= k_line_max){

			if(k == 1)
				s_line = pcr_continuous_improvement_backward(copySolution(s), 0, 0);
			else if(k == 2)
				s_line = pcr_continuous_improvement_foward(copySolution(s), 0, 0);
			else if(k == 3)
				s_line = pcr_best_improvement_backward(copySolution(s), 0, 0);
			else if(k == 4)
				s_line = pcr_best_improvement_foward(copySolution(s), 0, 0);
			else if(k == 5)
				s_line = pcr_first_improvement_backward(copySolution(s), 0, 0);
			else if(k == 6)
				s_line = pcr_first_improvement_foward(copySolution(s), 0, 0);
			else if(k == 7)
				s_line = kswap_continuous_improvement_backward(copySolution(s), 1, 0);
			else if(k == 8)
				s_line = kswap_continuous_improvement_foward(copySolution(s), 1, 0);
			else if(k == 9)
				s_line = kswap_best_improvement_backward(copySolution(s), 1, 0);
			else if(k == 10)
				s_line = kswap_best_improvement_foward(copySolution(s), 1, 0);
			else if(k == 11)
				s_line = kswap_first_improvement_backward(copySolution(s), 1, 0);
			else if(k == 12)
				s_line = kswap_first_improvement_foward(copySolution(s), 1, 0);
			else if(k == 13)
				s_line = kswap_continuous_improvement_backward(copySolution(s), 2, 0);
			else if(k == 14)
				s_line = kswap_continuous_improvement_foward(copySolution(s), 2, 0);
			else if(k == 15)
				s_line = kswap_best_improvement_backward(copySolution(s), 2, 0);
			else if(k == 16)
				s_line = kswap_best_improvement_foward(copySolution(s), 2, 0);
			else if(k == 17)
				s_line = kswap_first_improvement_backward(copySolution(s), 2, 0);
			else if(k == 18)
				s_line = kswap_first_improvement_foward(copySolution(s), 2, 0);
			else if(k == 19)
				s_line = kswap_continuous_improvement_backward(copySolution(s), 3, 0);
			else if(k == 20)
				s_line = kswap_continuous_improvement_foward(copySolution(s), 3, 0);
			else if(k == 21)
				s_line = kswap_best_improvement_backward(copySolution(s), 3, 0);
			else if(k == 22)
				s_line = kswap_best_improvement_foward(copySolution(s), 3, 0);
			else if(k == 23)
				s_line = kswap_first_improvement_backward(copySolution(s), 3, 0);
			else if(k == 24)
				s_line = kswap_first_improvement_foward(copySolution(s), 3, 0);
			else if(k == 25)
				s_line = kswap_continuous_improvement_backward(copySolution(s), 4, 0);
			else if(k == 26)
				s_line = kswap_continuous_improvement_foward(copySolution(s), 4, 0);
			else if(k == 27)
				s_line = kswap_best_improvement_backward(copySolution(s), 4, 0);
			else if(k == 28)
				s_line = kswap_best_improvement_foward(copySolution(s), 4, 0);
			else if(k == 29)
				s_line = kswap_first_improvement_backward(copySolution(s), 4, 0);
			else if(k == 30)
				s_line = kswap_first_improvement_foward(copySolution(s), 4, 0);
			else if(k == 31)
				s_line = kswap_continuous_improvement_backward(copySolution(s), 5, 0);
			else if(k == 32)
				s_line = kswap_continuous_improvement_foward(copySolution(s), 5, 0);
			else if(k == 33)
				s_line = kswap_best_improvement_backward(copySolution(s), 5, 0);
			else if(k == 34)
				s_line = kswap_best_improvement_foward(copySolution(s), 5, 0);
			else if(k == 35)
				s_line = kswap_first_improvement_backward(copySolution(s), 5, 0);
			else if(k == 36)
				s_line = kswap_first_improvement_foward(copySolution(s), 5, 0);
			
			if(OBJ(s->f_obj,s_line->f_obj)){
				printf("vnd k:: %d\n", k);
				freeSolution(s);
				free(s);
				s = s_line;
				k = 1;
				improvement = 1;
				#ifdef DEBUG
					fprintf(debug, "vnd::melhorei s_line: %f\n", s->f_obj);
				#endif
			}else{
				k++;
				freeSolution(s_line);
				free(s_line);
			}
		}
	gettimeofday(&time_end_all, NULL);
	time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
	}
return s;
}

Solution* free_s_line(Solution* s_line){
	Solution* aux_s = s_line;
	s_line = copySolution(s_line);
	freeSolution(aux_s);
	free(aux_s);
	return s_line;
}

Solution* local_search_1(Solution* s){
	int improvement = 1, it = 0;
	double time_all = 0.0;
	struct timeval time_start_all, time_end_all;
	
	while(CONDITION(s->f_obj, time_all, improvement) != -1){
		gettimeofday(&time_start_all, NULL);
		Solution* s_line = NULL;
		it++;
		printf("-- it: %d (improvement %d)\n", it , improvement);
		improvement = -1;
		s_line = pcr_continuous_improvement_backward(copySolution(s), 0, 0);
		//s_line = free_s_line(s_line);

		s_line = pcr_continuous_improvement_foward(s_line, 0, 0);
		//s_line = free_s_line(s_line);

		s_line = pcr_best_improvement_backward(s_line, 0, 0);
		//s_line = free_s_line(s_line);

		s_line = pcr_best_improvement_foward(s_line, 0, 0);
		//s_line = free_s_line(s_line);

		s_line = pcr_first_improvement_backward(s_line, 0, 0);
		//s_line = free_s_line(s_line);

		s_line = pcr_best_improvement_foward(s_line, 0, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_backward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_foward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_backward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_foward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_backward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_foward(s_line, 1, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_backward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_foward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_backward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_foward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_backward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_foward(s_line, 2, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_backward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_foward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_backward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_foward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_backward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_foward(s_line, 3, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_backward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_foward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_backward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_foward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_backward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_foward(s_line, 4, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_backward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_continuous_improvement_foward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_backward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_best_improvement_foward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_backward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		s_line = kswap_first_improvement_foward(s_line, 5, 0);
		//s_line = free_s_line(s_line);

		if(OBJ(s->f_obj,s_line->f_obj)){
			freeSolution(s);
			free(s);
			s = s_line;
			printf("-- local_search_1::melhorei s_line: %f\n", s->f_obj);
			improvement = 1;
			#ifdef DEBUG
				fprintf(debug, "local_search_1::melhorei s_line: %f\n", s->f_obj);
			#endif
		}else{
			freeSolution(s_line);
			free(s_line);
		}
	gettimeofday(&time_end_all, NULL);
	time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
	}
	return s;
}

Solution* local_search_body_s(Solution* (*fun_ptr)(Solution*,int, int), Solution* s, int k_swap, char* op_name){
	int improvement = 1, it = 0;
	double time_all = 0.0;
	struct timeval time_start_all, time_end_all;
	
	while(CONDITION(s->f_obj, time_all, improvement) != -1){
		gettimeofday(&time_start_all, NULL);
		it++;
		struct timeval time_s1, time_s2;
    	gettimeofday(&time_s1, NULL);
		Solution* s_line = (*fun_ptr)(copySolution(s), k_swap, 0);
		gettimeofday(&time_s2, NULL);
		double executed_t = (time_s2.tv_sec - time_s1.tv_sec);
		//printf("%s - %f\n", op_name, s_line->f_obj);
		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				writeFileInfos(shared_memory_infos, executed_t , -1, s_line->f_cost, s_line->f_obj, s_line->size_j, op_name, 0, fo_count, -1);
				//printf("-- local_search_::melhorei s_line: %f (%f)\n", s_line->f_obj, s->f_obj);
			#endif
			freeSolution(s);
			free(s);
			s = s_line;
			improvement = 1;
		}else{
			improvement = -1;
			freeSolution(s_line);
			free(s_line);
		}
	gettimeofday(&time_end_all, NULL);
	time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
	}
	return s;
}

Solution* verify_best(Solution* best, Solution* s_line, double* best_obj){
	if(s_line->f_obj < *best_obj){
		freeSolution(best);
		free(best);
		best = s_line;
		*best_obj = best->f_obj;
	}
	return best;
}

Solution* local_search_2(Solution* s){
	printf("S: %f\n", s->f_obj);
	Solution* s_line = NULL;
	s_line = local_search_body_s(&pcr_continuous_improvement_backward, s, 0, PCR_CN_B);
	s_line = local_search_body_s(&pcr_continuous_improvement_foward, s_line, 0, PCR_CN_F);

	s_line = local_search_body_s(&pcr_best_improvement_backward, s_line, 0, PCR_BS_B);
	s_line = local_search_body_s(&pcr_best_improvement_foward, s_line, 0, PCR_BS_F);
	s_line = local_search_body_s(&pcr_first_improvement_backward, s_line, 0, PCR_FI_B);
	s_line = local_search_body_s(&pcr_first_improvement_foward, s_line, 0, PCR_FI_F);

	s_line = local_search_body_s(&kswap_continuous_improvement_backward, s_line, 1, "1-SWAP_CN_B");
	s_line = local_search_body_s(&kswap_continuous_improvement_foward, s_line, 1, "1-SWAP_CN_F");
	s_line = local_search_body_s(&kswap_best_improvement_backward, s_line, 1, "1-SWAP_BS_B");
	s_line = local_search_body_s(&kswap_best_improvement_foward, s_line, 1, "1-SWAP_BS_F");
	s_line = local_search_body_s(&kswap_first_improvement_backward, s_line, 1, "1-SWAP_FI_B");
	s_line = local_search_body_s(&kswap_first_improvement_foward, s_line, 1, "1-SWAP_FI_F");

	s_line = local_search_body_s(&kswap_continuous_improvement_backward, s_line, 2, "2-SWAP_CN_B");
	s_line = local_search_body_s(&kswap_continuous_improvement_foward, s_line, 2, "2-SWAP_CN_F");
	s_line = local_search_body_s(&kswap_best_improvement_backward, s_line, 2, "2-SWAP_BS_B");
	s_line = local_search_body_s(&kswap_best_improvement_foward, s_line, 2, "2-SWAP_BS_F");
	s_line = local_search_body_s(&kswap_first_improvement_backward, s_line, 2, "2-SWAP_FI_B");
	s_line = local_search_body_s(&kswap_first_improvement_foward, s_line, 2, "2-SWAP_FI_F");

	s_line = local_search_body_s(&kswap_continuous_improvement_backward, s_line, 3, "3-SWAP_CN_B");
	s_line = local_search_body_s(&kswap_continuous_improvement_foward, s_line, 3, "3-SWAP_CN_F");
	s_line = local_search_body_s(&kswap_best_improvement_backward, s_line, 3, "3-SWAP_BS_B");
	s_line = local_search_body_s(&kswap_best_improvement_foward, s_line, 3, "3-SWAP_BS_F");
	s_line = local_search_body_s(&kswap_first_improvement_backward, s_line, 3, "3-SWAP_FI_B");
	s_line = local_search_body_s(&kswap_first_improvement_foward, s_line, 3, "3-SWAP_FI_F");

	s_line = local_search_body_s(&kswap_continuous_improvement_backward, s_line, 4, "4-SWAP_CN_B");
	s_line = local_search_body_s(&kswap_continuous_improvement_foward, s_line, 4, "4-SWAP_CN_F");
	s_line = local_search_body_s(&kswap_best_improvement_backward, s_line, 4, "4-SWAP_BS_B");
	s_line = local_search_body_s(&kswap_best_improvement_foward, s_line, 4, "4-SWAP_BS_F");
	s_line = local_search_body_s(&kswap_first_improvement_backward, s_line, 4, "4-SWAP_FI_B");
	s_line = local_search_body_s(&kswap_first_improvement_foward, s_line, 4, "4-SWAP_FI_F");

	s_line = local_search_body_s(&kswap_continuous_improvement_backward, s_line, 5, "5-SWAP_CN_B");
	s_line = local_search_body_s(&kswap_continuous_improvement_foward, s_line, 5, "5-SWAP_CN_F");
	s_line = local_search_body_s(&kswap_best_improvement_backward, s_line, 5, "5-SWAP_BS_B");
	s_line = local_search_body_s(&kswap_best_improvement_foward, s_line, 5, "5-SWAP_BS_F");
	s_line = local_search_body_s(&kswap_first_improvement_backward, s_line, 5, "5-SWAP_FI_B");
	s_line = local_search_body_s(&kswap_first_improvement_foward, s_line, 5, "5-SWAP_FI_F");
	
	return s_line;
}

Solution* adap_search_3(Solution* s){
	Solution* s_line = NULL;
	Solution* best = copySolution(s);
	double best_obj = best->f_obj, time_all = 0.0;
	int improvement = 1, it = 0;
	struct timeval time_start_all, time_end_all;

	while(CONDITION(s->f_obj, time_all, improvement) != -1){
		gettimeofday(&time_start_all, NULL);
		printf("it %d\n", it);
		it++;
		s_line = local_search_body_s(&pcr_continuous_improvement_backward, s, 0, PCR_CN_B);
		best = verify_best(best, s_line, &best_obj);

		s_line = local_search_body_s(&pcr_continuous_improvement_foward, s, 0, PCR_CN_F);
		best = verify_best(best, s_line, &best_obj);

		s_line = local_search_body_s(&pcr_best_improvement_backward, s, 0, PCR_BS_B);
		best = verify_best(best, s_line, &best_obj);

		s_line = local_search_body_s(&pcr_best_improvement_foward, s, 0, PCR_BS_F);
		best = verify_best(best, s_line, &best_obj);

		s_line = local_search_body_s(&pcr_first_improvement_backward, s, 0, PCR_FI_B);
		best = verify_best(best, s_line, &best_obj);

		s_line = local_search_body_s(&pcr_first_improvement_foward, s, 0, PCR_FI_F);
		best = verify_best(best, s_line, &best_obj);

		printf("oi\n");
		if(best->f_obj < s->f_obj)
			improvement = 1;
		else
			improvement = -1;
	gettimeofday(&time_end_all, NULL);
	time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
	}
	return best;
}