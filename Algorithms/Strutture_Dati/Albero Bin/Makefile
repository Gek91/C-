CC=g++
CCFLAG=-Wall

			

prog:	ALBBIN MAIN ALBBEL		
	$(CC) $(CCFLAG) -o prog ALBBIN ALBBEL MAIN
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

ALBBIN:	AlberoBin.cpp AlberoBin.h
	$(CC) $(CCFLAG) -c -o ALBBIN AlberoBin.cpp

ALBBEL:	AlberoBinElem.cpp AlberoBinElem.h
	$(CC) $(CCFLAG) -c -o ALBBEL AlberoBinElem.cpp

clean :				 
	rm ALBBIN MAIN ALBBEL prog 
	echo “Eliminati i file oggetto”