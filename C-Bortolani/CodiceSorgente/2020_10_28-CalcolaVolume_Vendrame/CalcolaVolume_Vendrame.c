/*
	Nome: CalcolaVolume.c
	Scopo: Si scriva un programma che legga da un file le misure di base di un certo numero di solidi (sfere, cilindri e parallelepipedi retti a base triangolare) e stampi il volume totale.
		   Il file sia organizzato per righe, una per ogni solido, che iniziano con un codice (“sf”, “cb”, “pr”) e che contengono le misure del solido.
		   sf 2.3
		   cb 4.0
		   pr 5.1 3.2 1.3
		   sf 1.7
			
	Autore: Vendrame Alessandro
	Data creazione: 27/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
	
	FILE *fp; 																										//Puntatore al file
	char formaGeo[2];
	int i = 0;
	float raggio;
	float altezza;
	float base;
	float altezza2;
	float volume, volumeTot=0;
																	
	
	if((fp = fopen("volume.dat","r"))== NULL){																	    //controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
		exit(1);																									//ritorno il codice di errore
	}else
	{
		while(!feof(fp)){												//finchè il file non è finito continuerà a ciclare
			for(i=0;i<2;i++){
				formaGeo[i] = fgetc(fp);								//prendo i primi due caratteri e li metto all'interno del vettore
			}
			
			if(strcmp(formaGeo,"sf") == 0){								//controllo se i caratteri corrispondono a "sf" 
			
				printf("%s ", formaGeo);								//stampo "sf" 
				fscanf(fp," %f\n", &raggio);							//leggo la lunghezza del raggio
				printf("%f\n",raggio);
				volume = (4*(3.14*(raggio*raggio*raggio)))/3;			//calcolo il volume della sfera
				volumeTot += volume;									//sommo al volume totale il volume della sfera
					
				printf("Il volume della sfera e': %f\n",volume);		//stampo il volume della sfera
				
			}else if(strcmp(formaGeo,"cb") == 0){						//controllo che i caratteri corrispondano a "cb"
				
				printf("%s ", formaGeo);								//stampo "cb"
				fscanf(fp," %f %f\n", &raggio,&altezza);				//leggo dal file le dimensioni del raggio e l'altezza del cilindro
				printf("%f %f\n",raggio,altezza);						//stampo il raggio e l'altezza
				volume = raggio*raggio*3.14*altezza;					//calcolo il volume del cilindro
				volumeTot += volume;									//sommo il volume del cilindro al volume totale
				
				printf("Il volume del cilindro e': %f\n",volume);		//stampo il volume del cilindro
				
			}else if(strcmp(formaGeo,"pr") == 0){						//controllo che i caratteri corrispondano a "pr"
				
				printf("%s ", formaGeo);								//stampo "pr"
				fscanf(fp," %f %f %f\n", &base,&altezza,&altezza2);		//leggo dal file le dimensioni del parallelepipedo
				printf("%f %f %f\n",base,altezza,altezza2);				//stampo le dimensioni del parallelepipedo
				volume = ((base*altezza)/2) * altezza2;					//calcolo il volume del parallelepipedo
				volumeTot += volume;									//sommo il volume del parallelepipedo al volume totale
				
				printf("Il volume del parallelepipedo e': %f\n",volume);	//stampo il volume del parallelepipedo
				
			}
		}
		
		printf("\n\nIl volume totale e': %f", volumeTot);				//stampo il volume totale
	}
	
	return 0;															//ritorno 0
	
}
