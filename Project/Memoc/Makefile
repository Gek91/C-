CC=g++
CCFLAG=



prog	: PUNTO SOL MOSSA TABU TSP main
	$(CC) $(CCFLAGS) -o prog main PUNTO TSP SOL TABU MOSSA  $(CPX_LDFLAGS)

main	: main.cpp 
	$(CC) $(CCFLAGS) -c main.cpp -o main 

TSP	: TSP.h TSP.cpp
	$(CC) $(CCFLAG) -c TSP.cpp -o TSP

SOL	:Solution.h Solution.cpp
	$(CC) $(CCFLAG) -c Solution.cpp -o SOL

PUNTO	: Punto.h Punto.cpp
	$(CC) $(CCFLAG) -c Punto.cpp -o PUNTO 

TABU	: TabuList.h TabuList.cpp
	$(CC) $(CCFLAG) -c TabuList.cpp -o TABU	

MOSSA	: Mossa.h Mossa.cpp
	$(CC) $(CCFLAG) -c Mossa.cpp -o MOSSA

clean	:
	rm main SOL MOSSA TSP PUNTO TABU prog archi.txt nodi.txt esercitazione.sol
	echo “Eliminati i file oggetto”