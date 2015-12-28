DIR_BIN = $(dir $(lastword $(MAKEFILE_LIST)))/../bin

help:
	@ echo 
	@ echo "Istruzioni"	
	@ echo " make compila : compila il programma"
	@ echo " make installa : sposta il file eseguibile da src a bin"
	@ echo " make elimina : elimina il file eseguibile da bin"
	@ echo
	@ echo "Il file eseguibile dopo la funzione installa si troverà nella cartella bin"
	@ echo 
compila: 
	gcc -g -Wall -o eseguibile.out main.c
	@ echo
	@ echo " FILE COMPILATO"
	@ echo 
installa:
	sudo mv eseguibile.out $(DIR_BIN)
	@ echo
	@ echo " INSTALLAZIONE COMPLETATA"
	@ echo 
elimina:
	rm -f $(DIR_BIN)/eseguibile.out
	@ echo
	@ echo " ELIMINAZIONE FILE COMPLETATA"
	@ echo 
