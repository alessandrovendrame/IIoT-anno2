/*
	Nome: SommaSensori.c
	Scopo: Si scriva un programma che legga da un file i dati contenuti relativi a delle rilevazioni (vedi esempio) e produca il totali per ciascun sensore.
	
			File di esempio:
			Sensore 1: 50
			Sensore 2: 25
			Sensore 3: 12
			Sensore 1: 20
			Sensore 1: 50
			Sensore 2: 15
			
			Output:
			Sensore 1: 120
			Sensore 2: 40
			Sensore 3: 12
			
	Autore: Vendrame Alessandro
	Data creazione: 27/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;														//puntatore al file
	int sensorsNumber[10],sensorsData[10]={0,0,0,0,0,0,0,0,0,0};	//vettori per la gestione dati dei sensori
	int sensorNumber,data;											//variabili d'appoggio per tenere i dati in memoria e per eseguire controlli
	int b=0;														//variabile che permette di capire se un numero è già stato inserito all'interno del vettore
	int i=0,k;														//indici dei vettori
	
	if((fp = fopen("sensors.dat","r"))== NULL){																	    //controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
		exit(1);																									//ritorno il codice di errore
	}else
	{
		while(!feof(fp)){
			for(k=0;k<7;k++){											//dato che all'inizio c'è sempre la parola "sensore" che ha 7 lettere e a noi non interessa
				fgetc(fp);												//uso la funzione fgetc() 7 volte per spostarmi alla fine della parola
			}
			
			fscanf(fp," %d: %d\n",&sensorNumber,&data);					//leggo i due dati dal file
			//printf("Sensore %d: %d\n", sensorNumber, data);
			
			for(k=0;k<i;k++)
			{
				if(sensorsNumber[k]==sensorNumber){						//controllo se sono già stati inseriti all'interno del vettore
					sensorsData[k]+=data;								//in caso sommo al valore esistente quello letto dal file
					b=1;
					//printf("Sensore %d: %d\n", sensorsNumber[k],sensorsData[k]);
				}
			}
			
			if(b==0)													//nel caso in cui non fosse presente all'interno del vettore
			{
				//printf("aggiungo sensore %d: %d in posizione %d\n", sensorNumber,data,i);
				sensorsNumber[i] = sensorNumber;						//aggiungo il numero nella posizione libera
				sensorsData[i]+=data;									//aggiungo il dato del sensore nella posizione libera
				
				i++;													//incremento il numero dei sensori
				b=0;													//riporto la variabile di controllo a 0
			}			
		}
		
		for(k=0; k<i; k++)
		{
			printf("Sensore %d: %d\n", sensorsNumber[k], sensorsData[k]);		//stampo il contenuto dei due vettori
		}
		
		return 0;
	}
}
