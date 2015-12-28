CC=g++
CCFLAG=-Wall

			

prog:	CODA MAIN		
	$(CC) $(CCFLAG) -o prog CODA MAIN
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

CODA:	Coda.cpp Coda.h
	$(CC) $(CCFLAG) -c -o CODA Coda.cpp

clean :				 
	rm CODA MAIN prog 
	echo “Eliminati i file oggetto”