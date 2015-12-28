CC=g++
CCFLAG=-Wall

prog:	HEAP MAIN		
	$(CC) $(CCFLAG) -o prog HEAP MAIN

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

HEAP:	Heap.cpp Heap.h
	$(CC) $(CCFLAG) -c -o HEAP Heap.cpp

clean :				 
	rm HEAP MAIN prog 
	echo “Eliminati i file oggetto”