/*
	Nome: Mirror.c
	Scopo: Il file mirror1.dat (da creare) rappresenta un'immagine bitmap in cui ogni pixel e` rappresentato da un numero intero compreso tra 0 e 255. 
		   Nella prima riga del file c’e` scritto il numero di righe e il numero di colonne della matrice (inferiore a 100x100). 
		   Il resto del file contiene, in ogni riga, una linea di pixel dell'immagine. Si scriva il programma mirror.c per generare il file mirror2.dat che contiene l'immagine speculare 
		   (in orizzontale, cioe` ottenibile da uno specchio posto in posizione verticale) di quella originale.
			
			3 5
			23	 7     45      179    12 
			22   7     56      2      0 
			88   7     123     32     99
			
	Autore: Vendrame Alessandro
	Data creazione: 27/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

//Funzione che restituisce la dimensione dell'array di char

int getDimension(char v[]){		
	int count=0;
	while(v[count] != '\0'){
		count++;
	}
	
	return count;
}

//programma principale

int main()
{
	//dichiarazione delle variabili 
	
	FILE *fp,*fp2;					//puntatori a file
	int giri = 1;					//contatore del numero delle righe nel file
	int matx,maty;					//variabili per salvare le dimensioni della matrice
	char stringa[100];				//variabile per salvare la stringa letta dal file
	char stringaSpecchiata[100];	//vettore sul quale verrà specchiata la stringa
	int i,k=0,dimVet;				//contatori dei cicli e dimensione del vettore
	
	if((fp = fopen("mirror1.dat","r")) == NULL){							//controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");		//in caso contrario ritorno il messaggio di errore 
		exit(1);
	}else
	{
		fp2 = fopen ("mirror2.dat", "w");									//apro il file in scrittura
		
		while(!feof(fp)){
			if(giri == 1){													//leggo la prima riga che contiene le dimensioni della matrice
				fscanf(fp,"%d %d\n",&matx,&maty);
				fprintf(fp2,"%d %d\n", maty, matx);
				printf("%d %d\n", maty,matx);
			}else
			{
				if(fgets(stringa,100,fp) != NULL){							//controllo che la riga letta non sia vuota
					dimVet = getDimension(stringa);							//prendo le dimensioni della stringa
					printf("stringa: %s",stringa);							//stampo la stringa
					printf("dimvet: %d\n", dimVet);							//stampo le dimensioni del vettore
				
					for(i=dimVet-2; i >= 0; i--)							//specchio la stringa
					{
						stringaSpecchiata[k++] = stringa[i]; 
					}
					stringaSpecchiata[k] = '\0';							//aggiungo il valore di fine stringa per poterla poi stampare utilizzando l'fputs
					printf("stringa specchiata: %s\n", stringaSpecchiata);
					fputs(stringaSpecchiata, fp2);							//scrivo la stringa nel file
					k=0;
					fputc('\n', fp2);										//vado a capo
				}
			}
			printf("giri: %d\n", giri);
			giri++;
		}
		
		fclose(fp);															//chiusura del file in lettura
		fclose(fp2);														//chiusura del file in scrittura
		
		return 0;
	}
}
