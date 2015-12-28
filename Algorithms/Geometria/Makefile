CC=g++
CCFLAG=-Wall

			

prog:	PUN SEG GEO MAIN EVE			
	$(CC) $(CCFLAG) -o prog PUN SEG GEO MAIN EVE

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

GEO:	Geometria.cpp Geometria.h
	$(CC) $(CCFLAG) -c -o GEO Geometria.cpp

EVE:	Evento.h Evento.cpp		 
	$(CC) $(CCFLAG) -c -o EVE evento.cpp

SEG:	Segmento.h Segmento.cpp
	$(CC) $(CCFLAG) -c -o SEG Segmento.cpp

PUN:	Punto.h Punto.cpp
	$(CC) $(CCFLAG) -c -o PUN Punto.cpp

SPAZ:	Spazzola.h Spazzola.cpp
	$(CC) $(CCFLAG) -c -o SPAZ Spazzola.cpp

SPAE:	SpazzolaElem.h SpazzolaElem.cpp
	$(CC) $(CCFLAG) -c -o SPAE SpazzolaElem.cpp


clean :				 
	rm PUN SPAE SPAZ SEG EVE GEO MAIN prog 
	echo “Eliminati i file oggetto”