CC=g++
CCFLAG=-Wall

			

prog:	PILA MAIN		
	$(CC) $(CCFLAG) -o prog PILA MAIN
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

PILA:	Pila.cpp Pila.h
	$(CC) $(CCFLAG) -c -o PILA Pila.cpp

clean :				 
	rm PILA MAIN prog 
	echo “Eliminati i file oggetto”