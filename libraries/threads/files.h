#ifndef FILES_H
#define FILES_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTANCES "instancias/"
#define PWD "logs/"

#define OPERATORS 36

#define PCR_FI_F "PCR_FI_F"
#define PCR_FI_B "PCR_FI_B"
#define PCR_BS_F "PCR_BS_F"
#define PCR_BS_B "PCR_BS_B"
#define PCR_CN_F "PCR_CN_F"
#define PCR_CN_B "PCR_CN_B"

#define KSWAP_FI_F "-SWAP_FI_F"
#define KSWAP_FI_B "-SWAP_FI_B"
#define KSWAP_BS_F "-SWAP_BS_F"
#define KSWAP_BS_B "-SWAP_BS_B"
#define KSWAP_CN_F "-SWAP_CN_F"
#define KSWAP_CN_B "-SWAP_CN_B"

#define LS1_INFOS "local_search1_infos.txt"
#define LS2_INFOS "local_search2_infos.txt"
#define LS3_INFOS "local_search3_infos.txt"
#define LS4_INFOS "local_search4_infos.txt"
#define LS5_INFOS "local_search5_infos.txt"
#define LS6_INFOS "local_search6_infos.txt"

#define LS7_INFOS "local_search7_infos.txt"
#define LS8_INFOS "local_search8_infos.txt"
#define LS9_INFOS "local_search9_infos.txt"
#define LS10_INFOS "local_search10_infos.txt"
#define LS11_INFOS "local_search11_infos.txt"
#define LS12_INFOS "local_search12_infos.txt"
#define LS13_INFOS "local_search13_infos.txt"
#define LS14_INFOS "local_search14_infos.txt"
#define LS15_INFOS "local_search15_infos.txt"
#define LS16_INFOS "local_search16_infos.txt"

#define LS17_INFOS "local_search17_infos.txt"
#define LS18_INFOS "local_search18_infos.txt"
#define LS19_INFOS "local_search19_infos.txt"
#define LS20_INFOS "local_search20_infos.txt"
#define LS21_INFOS "local_search21_infos.txt"
#define LS22_INFOS "local_search22_infos.txt"
#define LS23_INFOS "local_search23_infos.txt"
#define LS24_INFOS "local_search24_infos.txt"
#define LS25_INFOS "local_search25_infos.txt"
#define LS26_INFOS "local_search26_infos.txt"

#define LS27_INFOS "local_search27_infos.txt"
#define LS28_INFOS "local_search28_infos.txt"
#define LS29_INFOS "local_search29_infos.txt"
#define LS30_INFOS "local_search30_infos.txt"
#define LS31_INFOS "local_search31_infos.txt"
#define LS32_INFOS "local_search32_infos.txt"
#define LS33_INFOS "local_search33_infos.txt"
#define LS34_INFOS "local_search34_infos.txt"
#define LS35_INFOS "local_search35_infos.txt"
#define LS36_INFOS "local_search36_infos.txt"

FILE* debug;
FILE* timeout;

FILE* shared_memory_infos;
FILE* shared_memory_details;

FILE* best_infos;
FILE* best_details;

FILE* vet_files[OPERATORS];
char* pwds[OPERATORS];

char* createDirectory(char* algo_dir, char* file_name, char* it);
FILE* openFile(char* pwd, char* mode);
void closeFile(FILE* file, char* pwd);
char* nameFile(char* pwd, char* name);

void writeFileInfos(FILE* file, double executed_m , int id, double f_cost, double f_obj, int size_j, char* ls_name, int while_, int fo_count, int thr_choosed);
void writeFileDetails(FILE* file, int id, int size_J);

char* getFileName(int i);
void openKfiles(char* p, int k);
void closeKfiles(int k);

#endif