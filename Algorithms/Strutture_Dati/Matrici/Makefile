

CC=g++
CCFLAG=-Wall

			

prog:	MATRIX MAIN SMATRIX		
	$(CC) $(CCFLAG) -o prog MATRIX MAIN SMATRIX

MAIN:	main.cpp
	$(CC) $(CCFLAG) -c -o MAIN main.cpp

MATRIX:	Matrix.cpp Matrix.h
	$(CC) $(CCFLAG) -c -o MATRIX Matrix.cpp
SMATRIX: SMatrix.cpp SMatrix.h
	$(CC) $(CCFLAG) -c -o SMATRIX SMatrix.cpp


clean :				 
	rm SMATRIX MATRIX MAIN prog 
	echo “Eliminati i file oggetto”