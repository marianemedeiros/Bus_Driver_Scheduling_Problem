#include "vns_s.h"


//k_max = quantidade de shakes diferentes (4)
Solution* vns(Solution* s, int bl){
	struct timeval t_i_copy, t_o_copy, t_i_shake, t_o_shake, time_start_all, time_end_all;
	Solution* s_line, *cp;
	int stop_c = 1, k = 1, it = 0;
	double time_all = 0.0;

	while(k <= K_MAX && stop_c != -1){
		gettimeofday(&time_start_all, NULL);
		#ifdef DEBUG
			fprintf(debug, "\n(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, s->f_obj, time_all);
			printf("\n(vns k: %d) (s->f_obj: %f) (time: %f)\n", k, s->f_obj, time_all);
		#endif

		gettimeofday(&t_i_copy, NULL);
		cp = copySolution(s);
		gettimeofday(&t_o_copy, NULL);
		double copy_executed = (t_o_copy.tv_sec - t_i_copy.tv_sec);

		//if(it > 0){
			gettimeofday(&t_i_shake, NULL);
			s_line = shake(cp, k);
			gettimeofday(&t_o_shake, NULL);
			double shake_executed = (t_o_shake.tv_sec - t_i_shake.tv_sec);
		//}else{
		//	s_line = cp;
		//}

		Solution* s_t_line = NULL;
		struct timeval t_i_vnd, t_o_vnd;
		if(bl == 1){
			gettimeofday(&t_i_vnd, NULL);
			s_t_line = vnd(copySolution(s_line), OPERATORS);
			gettimeofday(&t_o_vnd, NULL);
		}else if(bl == 2){
			gettimeofday(&t_i_vnd, NULL);
			s_t_line = local_search_1(copySolution(s_line));
			gettimeofday(&t_o_vnd, NULL);
		}else if(bl  == 3){
			gettimeofday(&t_i_vnd, NULL);
			s_t_line = local_search_2(copySolution(s_line));
			gettimeofday(&t_o_vnd, NULL);
		}else if(bl  == 4){
			gettimeofday(&t_i_vnd, NULL);
			s_t_line = adap_search_3(copySolution(s_line));
			gettimeofday(&t_o_vnd, NULL);
		}
		double vnd_executed = (t_o_vnd.tv_sec - t_i_vnd.tv_sec);

		struct timeval t_i_free, t_o_free;
		gettimeofday(&t_i_free, NULL);
		freeSolution(s_line);
		free(s_line);		
		gettimeofday(&t_o_free, NULL);
		double free_executed = (t_o_free.tv_sec - t_i_free.tv_sec);		

		#ifdef DEBUG
			fprintf(timeout, "%d; %f; %f; %f; %f\n", k, copy_executed, shake_executed, vnd_executed, free_executed);
		#endif

		printf("VNS s': %f\n", s_t_line->f_obj);
		if(OBJ(s->f_obj, s_t_line->f_obj)){
			#ifdef DEBUG_VNS
				printObjVNS(k, s_t_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_t_line;
			writeFileInfos(shared_memory_infos, vnd_executed , k, s->f_cost, s->f_obj, s->size_j, "VNS", 0, fo_count, -1);
			k = 1;
		}else{
			k++; 
			freeSolution(s_t_line);
			free(s_t_line);
		}
		gettimeofday(&time_end_all, NULL);
		it++;
		time_all = (time_end_all.tv_sec - time_start_all.tv_sec);
		stop_c = CONDITION(s->f_obj, time_all, 1);
	}

	printf("Antes::: %f\n", s->f_obj);
	calculeObjectiveFunction(s);
	printf("Depois::: %f\n", s->f_obj);
		
	return s;
}

