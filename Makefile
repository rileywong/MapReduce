# Define (atleast) the following targets: all, clean
# all must build the executable file named mapreduce.
# clean must remove all object files and executable files created.
# Look at the introduction doc for information on how make a Makefile.
# This make file must build according to the structure described in the
# introduction doc, if it doesn't you will get a ZERO!
#CFLAGS = -Wall -Werror
#BINS =  main map_reduce

#all: 	
#	$(BINS)
	
#main:
#	gcc $(CFLAGS) src/main.c -o main
#	gcc $(CFLAGS) src/map_reduce.c -o $@

#mapreduce:
#	gcc build/map_reduce.o
#	gcc build/main.o 
#	gcc $(CFLAGS) $^ -o /bin$@ -lm
#clean:
#	rm -f $(BINS)
CFLAGS = -Wall -Werror
BINS = dirs main.o map_reduce.o mapreduce

BU = build/
BI = bin/
 

all:
	mkdir -p $(BI)
	mkdir -p $(BU)
	make main.o
	make map_reduce.o
	make please

main.o: src/main.c
	gcc $(CFLAGS) -c $^ -I ./include -o $(BU)$@
map_reduce.o: src/map_reduce.c
	gcc $(CFLAGS) -c $^ -I ./include -o $(BU)$@

mapreduce: $(BU)map_reduce.o $(BU)main.o 
	gcc $(CFLAGS) $^ -o $(BI)$@ -lm
please:
	gcc $(CFLAGS) src/main.c -o bin/mapreduce
	

clean:
	rm -rf build/ bin/
