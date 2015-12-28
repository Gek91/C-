CC=g++
CCFLAG=-Wall

			

prog:	PM MAIN				
	$(CC) $(CCFLAG) -o prog MAIN PM

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

PM:	PM.cpp PM.h
	$(CC) $(CCFLAG) -c -o PM PM.cpp




clean :				 
	rm PM MAIN prog 
	echo “Eliminati i file oggetto”