#include "local_search.h"

void assingLocalSearchFunctions(){
	for (int i = 0; i < used_local_search; i++){
		if(i == 0)
			p[0] = local_search1_P; /*pcr_first_improvement_foward ** */
		else if(i == 1)
			p[1] = local_search2_P; /*pcr_first_improvement_backward ** */
		else if(i == 2)
			p[2] = local_search3_P; /*pcr_best_improvement_foward ** */
		else if(i == 3)
			p[3] = local_search4_P; /*pcr_best_improvement_backward*/
		else if(i == 4)
			p[4] = local_search5_P; /*1 - kswap_first_improvement_foward */
		else if(i == 5)
			p[5] = local_search6_P; /*1 - kswap_first_improvement_backward ** */
		else if(i == 6)
			p[6] = local_search7_P; /*2 - kswap_first_improvement_foward ** */
		else if(i == 7)
			p[7] = local_search8_P;  /*2 - kswap_first_improvement_backward ** */
		else if(i == 8)
			p[8] = local_search9_P; /*3 - kswap_first_improvement_foward ** */
		else if(i == 9)
			p[9] = local_search10_P; /*3 - kswap_first_improvement_backward ** */
		else if(i == 10)
			p[10] = local_search11_P; /*4 - kswap_first_improvement_foward ** */
		else if(i == 11)
			p[11] = local_search12_P; /*4 - kswap_first_improvement_backward ** */
		else if(i == 12)
			p[12] = local_search13_P; /*5 - kswap_first_improvement_foward ** */
		else if(i == 13)
			p[13] = local_search14_P; /*5 - kswap_first_improvement_backward ** */
		else if(i == 14)
			p[14] = local_search15_P; /*1 - kswap_best_improvement_foward*/
		else if(i == 15)
			p[15] = local_search16_P; /*1 - kswap_best_improvement_backward*/
		else if(i == 16)
			p[16] = local_search17_P; /*2 - kswap_best_improvement_foward*/
		else if(i == 17)
			p[17] = local_search18_P; /*2 - kswap_best_improvement_backward*/
		else if(i == 18)
			p[18] = local_search19_P; /*3 - kswap_best_improvement_foward*/
		else if(i == 19)
			p[19] = local_search20_P; /*3 - kswap_best_improvement_backward*/
		else if(i == 20)
			p[20] = local_search21_P; /*4 - kswap_best_improvement_foward*/
		else if(i == 21)
			p[21] = local_search22_P; /*4 - kswap_best_improvement_backward*/
		else if(i == 22)
			p[22] = local_search23_P; /*5 - kswap_best_improvement_foward*/
		else if(i == 23)
			p[23] = local_search24_P; /*5 - kswap_best_improvement_backward*/
		else if(i == 24)
			p[24] = local_search25_P; /*pcr_continuous_improvement_foward ** */
		else if(i == 25)
			p[25] = local_search26_P; /*pcr_continuous_improvement_backward ** */
		else if(i == 26)
			p[26] = local_search27_P; /*1 - kswap_continuous_improvement_foward*/
		else if(i == 27)
			p[27] = local_search28_P; /*1 - kswap_continuous_improvement_backward*/
		else if(i == 28)
			p[28] = local_search29_P; /*2 - kswap_continuous_improvement_foward*/
		else if(i == 29)
			p[29] = local_search30_P; /*2 - kswap_continuous_improvement_backward*/
		else if(i == 30)
			p[30] = local_search31_P; /*3 - kswap_continuous_improvement_foward*/
		else if(i == 31)
			p[31] = local_search32_P; /*3 - kswap_continuous_improvement_backward*/
		else if(i == 32)
			p[32] = local_search33_P; /*4 - kswap_continuous_improvement_foward*/
		else if(i == 33)
			p[33] = local_search34_P; /*4 - kswap_continuous_improvement_backward*/
		else if(i == 34)
			p[34] = local_search35_P; /*5 - kswap_continuous_improvement_foward*/
		else if(i == 35)
			p[35] = local_search36_P; /*5 - kswap_continuous_improvement_backward*/
	}
}

void assingLocalSearchFunctions_w0d0(){
	for (int i = 0; i < used_local_search; i++){
		if(i == 0)
			p[0] = local_search1_P; /*pcr_first_improvement_foward ** */
		else if(i == 1)
			p[1] = local_search2_P; /*pcr_first_improvement_backward ** */
		else if(i == 2)
			p[2] = local_search3_P; /*pcr_best_improvement_foward ** */
		else if(i == 3)
			p[3] = local_search5_P; /*1 - kswap_first_improvement_foward */
		else if(i == 4)
			p[4] = local_search6_P; /*1 - kswap_first_improvement_backward ** */
		else if(i == 5)
			p[5] = local_search7_P; /*2 - kswap_first_improvement_foward ** */
		else if(i == 6)
			p[6] = local_search8_P;  /*2 - kswap_first_improvement_backward ** */
		else if(i == 7)
			p[7] = local_search9_P; /*3 - kswap_first_improvement_foward ** */
		else if(i == 8)
			p[8] = local_search10_P; /*3 - kswap_first_improvement_backward ** */
		else if(i == 9)
			p[9] = local_search11_P; /*4 - kswap_first_improvement_foward ** */
		else if(i == 10)
			p[10] = local_search12_P; /*4 - kswap_first_improvement_backward ** */
		else if(i == 11)
			p[11] = local_search13_P; /*5 - kswap_first_improvement_foward ** */
		else if(i == 12)
			p[12] = local_search14_P; /*5 - kswap_first_improvement_backward ** */
		else if(i == 13)
			p[13] = local_search19_P; /*3 - kswap_best_improvement_foward*/
		else if(i == 14)
			p[14] = local_search23_P; /*5 - kswap_best_improvement_foward*/
		else if(i == 15)
			p[15] = local_search24_P; /*5 - kswap_best_improvement_backward*/
		else if(i == 16)
			p[16] = local_search25_P; /*pcr_continuous_improvement_foward ** */
		else if(i == 17)
			p[17] = local_search26_P; /*pcr_continuous_improvement_backward ** */
	}
	
}

void assingLocalSearchFunctions_w1d0(){
	for (int i = 0; i < used_local_search; i++){
		if(i == 0)
			p[0] = local_search1_P; /*pcr_first_improvement_foward ** */
		else if(i == 1)
			p[1] = local_search2_P; /*pcr_first_improvement_backward ** */
		else if(i == 2)
			p[2] = local_search3_P; /*pcr_best_improvement_foward ** */
		else if(i == 3)
			p[3] = local_search5_P; /*1 - kswap_first_improvement_foward */
		else if(i == 4)
			p[4] = local_search6_P; /*1 - kswap_first_improvement_backward ** */
		else if(i == 5)
			p[5] = local_search7_P; /*2 - kswap_first_improvement_foward ** */
		else if(i == 6)
			p[6] = local_search8_P;  /*2 - kswap_first_improvement_backward ** */
		else if(i == 7)
			p[7] = local_search9_P; /*3 - kswap_first_improvement_foward ** */
		else if(i == 8)
			p[8] = local_search10_P; /*3 - kswap_first_improvement_backward ** */
		else if(i == 9)
			p[9] = local_search11_P; /*4 - kswap_first_improvement_foward ** */
		else if(i == 10)
			p[10] = local_search12_P; /*4 - kswap_first_improvement_backward ** */
		else if(i == 11)
			p[11] = local_search13_P; /*5 - kswap_first_improvement_foward ** */
		else if(i == 12)
			p[12] = local_search14_P; /*5 - kswap_first_improvement_backward ** */
		else if(i == 13)
			p[13] = local_search15_P; /*1 - kswap_best_improvement_foward*/
		else if(i == 14)
			p[14] = local_search16_P; /*1 - kswap_best_improvement_backward*/
		else if(i == 15)
			p[15] = local_search17_P; /*2 - kswap_best_improvement_foward*/
		else if(i == 16)
			p[16] = local_search18_P; /*2 - kswap_best_improvement_backward*/
		else if(i == 17)
			p[17] = local_search19_P; /*3 - kswap_best_improvement_foward*/
		else if(i == 18)
			p[18] = local_search20_P; /*3 - kswap_best_improvement_backward*/
		else if(i == 19)
			p[19] = local_search23_P; /*5 - kswap_best_improvement_foward*/
		else if(i == 20)
			p[20] = local_search25_P; /*pcr_continuous_improvement_foward ** */
		else if(i == 21)
			p[21] = local_search26_P; /*pcr_continuous_improvement_backward ** */
	}}

void assingLocalSearchFunctions_w0d1(){
	for (int i = 0; i < used_local_search; i++){
		if(i == 0)
			p[0] = local_search1_P; /*pcr_first_improvement_foward ** */
		else if(i == 1)
			p[1] = local_search2_P; /*pcr_first_improvement_backward ** */
		else if(i == 2)
			p[2] = local_search3_P; /*pcr_best_improvement_foward ** */
		else if(i == 4)
			p[4] = local_search5_P; /*1 - kswap_first_improvement_foward */
		else if(i == 5)
			p[5] = local_search6_P; /*1 - kswap_first_improvement_backward ** */
		else if(i == 6)
			p[6] = local_search7_P; /*2 - kswap_first_improvement_foward ** */
		else if(i == 7)
			p[7] = local_search8_P;  /*2 - kswap_first_improvement_backward ** */
		else if(i == 8)
			p[8] = local_search9_P; /*3 - kswap_first_improvement_foward ** */
		else if(i == 9)
			p[9] = local_search10_P; /*3 - kswap_first_improvement_backward ** */
		else if(i == 10)
			p[10] = local_search11_P; /*4 - kswap_first_improvement_foward ** */
		else if(i == 11)
			p[11] = local_search12_P; /*4 - kswap_first_improvement_backward ** */
		else if(i == 12)
			p[12] = local_search13_P; /*5 - kswap_first_improvement_foward ** */
		else if(i == 13)
			p[13] = local_search14_P; /*5 - kswap_first_improvement_backward ** */
		else if(i == 14)
			p[14] = local_search15_P; /*1 - kswap_best_improvement_foward*/
		else if(i == 15)
			p[15] = local_search16_P; /*1 - kswap_best_improvement_backward*/
		else if(i == 16)
			p[16] = local_search22_P; /*4 - kswap_best_improvement_backward*/
		else if(i == 17)
			p[17] = local_search23_P; /*5 - kswap_best_improvement_foward*/
		else if(i == 18)
			p[18] = local_search24_P; /*5 - kswap_best_improvement_backward*/
		else if(i == 19)
			p[19] = local_search25_P; /*pcr_continuous_improvement_foward ** */
		else if(i == 20)
			p[20] = local_search26_P; /*pcr_continuous_improvement_backward ** */

	}
}

void assingLocalSearchFunctions_w1d1(){
	for (int i = 0; i < used_local_search; i++){
		if(i == 0)
			p[0] = local_search1_P; /*pcr_first_improvement_foward ** */
		else if(i == 1)
			p[1] = local_search2_P; /*pcr_first_improvement_backward ** */
		else if(i == 2)
			p[2] = local_search3_P; /*pcr_best_improvement_foward ** */
		else if(i == 4)
			p[4] = local_search5_P; /*1 - kswap_first_improvement_foward */
		else if(i == 5)
			p[5] = local_search6_P; /*1 - kswap_first_improvement_backward ** */
		else if(i == 6)
			p[6] = local_search7_P; /*2 - kswap_first_improvement_foward ** */
		else if(i == 7)
			p[7] = local_search8_P;  /*2 - kswap_first_improvement_backward ** */
		else if(i == 8)
			p[8] = local_search9_P; /*3 - kswap_first_improvement_foward ** */
		else if(i == 9)
			p[9] = local_search10_P; /*3 - kswap_first_improvement_backward ** */
		else if(i == 10)
			p[10] = local_search11_P; /*4 - kswap_first_improvement_foward ** */
		else if(i == 11)
			p[11] = local_search12_P; /*4 - kswap_first_improvement_backward ** */
		else if(i == 12)
			p[12] = local_search13_P; /*5 - kswap_first_improvement_foward ** */
		else if(i == 13)
			p[13] = local_search14_P; /*5 - kswap_first_improvement_backward ** */
		else if(i == 14)
			p[14] = local_search15_P; /*1 - kswap_best_improvement_foward*/
		else if(i == 15)
			p[15] = local_search16_P; /*1 - kswap_best_improvement_backward*/
		else if(i == 16)
			p[16] = local_search17_P; /*2 - kswap_best_improvement_foward*/
		else if(i == 17)
			p[17] = local_search18_P; /*2 - kswap_best_improvement_backward*/
		else if(i == 18)
			p[18] = local_search19_P; /*3 - kswap_best_improvement_foward*/
		else if(i == 19)
			p[19] = local_search20_P; /*3 - kswap_best_improvement_backward*/
		else if(i == 20)
			p[20] = local_search23_P; /*5 - kswap_best_improvement_foward*/
		else if(i == 21)
			p[21] = local_search25_P; /*pcr_continuous_improvement_foward ** */
		else if(i == 22)
			p[22] = local_search26_P; /*pcr_continuous_improvement_backward ** */


	}
}