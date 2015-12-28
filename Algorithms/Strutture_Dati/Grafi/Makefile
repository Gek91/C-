

CC=g++
CCFLAG=-Wall

			

prog:	GRAPH MAIN GRAPHM GRAPHL		
	$(CC) $(CCFLAG) -o prog GRAPH GRAPHL GRAPHM MAIN 

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

GRAPH:	Graph.cpp Graph.h
	$(CC) $(CCFLAG) -c -o GRAPH Graph.cpp

GRAPHM:	GraphMatrix.cpp GraphMatrix.h
	$(CC) $(CCFLAG) -c -o GRAPHM GraphMatrix.cpp

GRAPHL:	GraphList.cpp GraphList.h
	$(CC) $(CCFLAG) -c -o GRAPHL GraphList.cpp

clean :				 
	rm GRAPH GRAPHL GRAPHM MAIN prog 
	echo “Eliminati i file oggetto”