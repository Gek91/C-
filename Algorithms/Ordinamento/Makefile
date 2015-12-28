CC=g++
CCFLAG=-Wall
HEAP=../Strutture_Dati/Heap

			

prog:	ORD MAIN HEAP				
	$(CC) $(CCFLAG) -o prog MAIN ORD HEAP

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

ORD:	ORD.cpp ORD.h
	$(CC) $(CCFLAG) -c -o ORD ORD.cpp

HEAP:	$(HEAP)/Heap.h $(HEAP)/Heap.cpp
	$(CC) $(CCFLAG) -c -o HEAP $(HEAP)/Heap.cpp



clean :				 
	rm ORD MAIN HEAP prog 
	echo “Eliminati i file oggetto”