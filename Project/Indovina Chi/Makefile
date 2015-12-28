CC=g++
CCFLAG=-Wall
GIOCATORE1=2		#1:Giocatore	2:IA
GIOCATORE2=2		#1:Giocatore	2:IA
N_PERSONE=24
N_CICLI=1
N_STEP=1
ALGORITMO=3			#valori accettati: minmax=1,minmaxpruning=2, depthlimited=3, breadthlimited=4;

DEFS=\
	-DN_PERSONE=$(N_PERSONE)		\
	-DN_CICLI=$(N_CICLI)			\
	-DALGORITMO=$(ALGORITMO)		\
	-DN_STEP=$(N_STEP)			\
	-DGIOCATORE1=$(GIOCATORE1)		\
	-DGIOCATORE2=$(GIOCATORE2)

prog : main
	$(CC) $(CCFLAG) -o prog.o main.o

main : main.cpp header.h Persona.h
	$(CC) $(CCFLAG) $(DEFS) -c main.cpp -o main.o


clean :
	rm *.o
	echo “Eliminati i file oggetto”