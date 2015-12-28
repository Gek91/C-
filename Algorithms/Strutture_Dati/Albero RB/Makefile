CC=g++
CCFLAG=-Wall

			

prog:	ALBRBEL MAIN ALBRB		
	$(CC) $(CCFLAG) -o prog ALBRBEL MAIN ALBRB
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

ALBRB:	AlberoRB.cpp AlberoRB.h
	$(CC) $(CCFLAG) -c -o ALBRB AlberoRB.cpp

ALBRBEL:	AlberoRBElem.cpp AlberoRBElem.h
	$(CC) $(CCFLAG) -c -o ALBRBEL AlberoRBElem.cpp

clean :				 
	rm ALBRBEL MAIN ALBRB prog 
	echo “Eliminati i file oggetto”