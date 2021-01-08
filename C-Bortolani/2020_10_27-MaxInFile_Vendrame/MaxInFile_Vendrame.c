/*
	Nome: FilesNotes.c
	Scopo: Leggere da un file .dat una serie di numeri e stampare a video il numero massimo
	Autore: Vendrame Alessandro
	Data creazione: 27/10/2020
*/

/*
	----------------APPUNTI PER LEGGERE E SCRIVERE DA FILE----------------
	
	Lettura:
		
		int fgetc ( FILE *fp );
		int fgets ( char *s, int nmax, FILE *fp );
		int fscanf ( FILE *fp, char *format, ... );
		
	Scrittura:
		
		int fputc ( int ch, FILE *fp );
		int fputs ( char *s, FILE *fp );
		int fprintf ( FILE *fp, char *format, ... );
	
	----------------------------------------------------------------------
	
*/

#include <stdlib.h>
#include <stdio.h>

int main(){
	
	FILE *fp; 																										//Puntatore al file
	int number,maxNumber = INT_MIN, numberOfTimes = 0;																//variabili per tenere in memoria i numeri
	
	if((fp = fopen("max_da_file.dat","r"))== NULL){																	//controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
		exit(1);																									//ritorno il codice di errore
	}else
	{
		while(!feof(fp)){																							//leggo il file finche non finisce
			fscanf(fp,"%d",&number);																				//leggo il numero
			printf("Numero letto: %d\n", number);																	//stampo il numero letto
			if(number > maxNumber)																					//controllo che sia maggiore del numero massimo
			{
				maxNumber = number;																					//nel caso lo sia assegno alla variabile il valore di quel numero
				numberOfTimes = 0;																					//inizializzo il numero delle volte che quel numero è presente nel file
			}
			if(number == maxNumber)																					//nel caso in cui il numero si ripresenti
			{
				numberOfTimes++;																					//incremento il numero delle volte
			}
		}
			
		fclose(fp);																									//chiudo il file
		printf("Il massimo numero all'interno del file e': %d.\nE compare %d volte/a", maxNumber, numberOfTimes);	//stampo il valore massimo e quante volte compare nel file
	}
}
