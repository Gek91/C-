CC=g++
CCFLAG=-Wall

			

prog:	LIST LISTC MAIN		
	$(CC) $(CCFLAG) -o prog LIST LISTC MAIN
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

LIST:	ListElem.cpp ListElem.h
	$(CC) $(CCFLAG) -c -o LIST ListElem.cpp

LISTC:	ListaConc.cpp ListaConc.h
	$(CC) $(CCFLAG) -c -o LISTC ListaConc.cpp

clean :				 
	rm LIST LISTC MAIN prog 
	echo “Eliminati i file oggetto”