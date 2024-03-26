#any questions see: http://opensourceforu.com/2012/06/gnu-make-in-detail-for-beginners/

CC = gcc
CFLAGS = -Wall -g -pg -O3 -DDEBUG -DDEBUG_VNS -DDEBUG_LS -DDEBUG_OP -DDEBUG_SM
DFLAGS = -DDEBUG -DDEBUG_SM  -DDEBUG_VNS -DDEBUG_LS -DDEBUG_OP -DDEBUG_CG_SOLUTION
DEPS = libraries/readInstances.h libraries/doublyLinkedDynamicList.h libraries/construtivePhase.h libraries/datetime.c libraries/journey.h libraries/task.h libraries/PA/apc.c  libraries/solution.c  libraries/shake.c libraries/cut.c libraries/operators/operators.c libraries/operators/pcr.c libraries/operators/kswap.c restriction_evaluator/restriction_evaluator.c libraries/vector.h libraries/metaheuristics/vns.h libraries/metaheuristics/vns_s.h libraries/metaheuristics/vns_p.h libraries/threads/threads.h libraries/threads/ls_first_improv.h libraries/threads/ls_best_improv.h libraries/threads/ls_continuous_improv.h libraries/threads/local_search.h libraries/threads/files.h libraries/metaheuristics/local_search_s.h

OBJ = main_all.o libraries/readInstances.o libraries/doublyLinkedDynamicList.o libraries/construtivePhase.o libraries/datetime.o libraries/journey.o libraries/task.o libraries/PA/apc.o libraries/solution.o libraries/shake.o libraries/cut.o libraries/operators/operators.o libraries/operators/pcr.o libraries/operators/kswap.o restriction_evaluator/restriction_evaluator.o libraries/vector.o libraries/metaheuristics/vns.o libraries/metaheuristics/vns_s.o libraries/metaheuristics/vns_p.o libraries/threads/threads.o libraries/threads/ls_first_improv.o libraries/threads/ls_best_improv.o  libraries/threads/ls_continuous_improv.o libraries/threads/local_search.o libraries/threads/files.o libraries/metaheuristics/local_search_s.o -lpthread

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#debug: $(OBJ)
#	@echo "Debug mode.."
#	$(CC) $(DFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<



clean:
	@echo "Cleaning up.."
	rm -rf *.o
	rm -rf libraries/*.o
	rm -rf libraries/PA/*.o
	rm -rf libraries/operators/*.o
	rm -rf libraries/local_search/*.o
	rm -rf libraries/metaheuristics/*.o
	rm -rf libraries/threads/*.o
	rm -rf restriction_evaluator/*.o
	rm main

clean_log:
	@echo "Cleaning up log files.."
	rm -rf logs/*
	rm -rf logs/vnsp_1_v1/*
	rm -rf logs/vnsp_1_v2/*
	rm -rf logs/vnsp_2/*
	rm -rf logs/gnvs/*

	rm -rf logs_gprof/*
	rm -rf logs_gprof/vns_p1/*
	rm -rf logs_gprof/vns_p2/*
	rm -rf logs_gprof/gvns/*
	
	rm -rf logs_perf/*
	rm -rf logs_perf/vns_p1/*
	rm -rf logs_perf/vns_p2/*
	rm -rf logs_perf/gvns/*

#go: libraries/dinamicList.c libraries/strings.c libraries/nspLib.c libraries/hungarian/hungarian.c main.c
#	g++ -o main libraries/dinamicList.c libraries/strings.c libraries/nspLib.c libraries/hungarian/hungarian.c main.c
