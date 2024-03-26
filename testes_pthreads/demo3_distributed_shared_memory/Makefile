#any questions see: http://opensourceforu.com/2012/06/gnu-make-in-detail-for-beginners/

CC = gcc
CFLAGS = -Wall -g 
DEPS = 
OBJ = constants.c functions.c demo3.c -lpthread

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning up.."
	rm -rf *.o
	rm -rf libraries/*.o
	rm -rf libraries/PA/*.o
	rm -rf libraries/local_search/*.o
	rm -rf libraries/metaheuristics/*.o
	rm main

#go: libraries/dinamicList.c libraries/strings.c libraries/nspLib.c libraries/hungarian/hungarian.c main.c
#	g++ -o main libraries/dinamicList.c libraries/strings.c libraries/nspLib.c libraries/hungarian/hungarian.c main.c
