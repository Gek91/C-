CC=g++
CCFLAG=-Wall

			

prog:	ALBFSFD MAIN ALBFSFDE		
	$(CC) $(CCFLAG) -o prog ALBFSFD ALBFSFDE MAIN
 
MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

ALBFSFD:	AlberoFSFD.cpp AlberoFSFD.h
	$(CC) $(CCFLAG) -c -o ALBFSFD AlberoFSFD.cpp

ALBFSFDE:	AlberoFSFDElem.cpp AlberoFSFDElem.h
	$(CC) $(CCFLAG) -c -o ALBFSFDE AlberoFSFDElem.cpp

clean :				 
	rm ALBFSFD MAIN ALBFSFDE prog 
	echo “Eliminati i file oggetto”