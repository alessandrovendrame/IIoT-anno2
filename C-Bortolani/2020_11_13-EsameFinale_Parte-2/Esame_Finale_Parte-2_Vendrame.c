#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp1;
	FILE *fp2;
	char soggetto_y[7][10];
	int immagine1[100][100];
	char string[100];
	int x=0,y=0;
	int maxX=0, maxY=0;
	int i=0;
	if((fp1 = fopen("soggetto_y.dat","r"))== NULL){																//controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
		exit(1);																									//ritorno il codice di errore
	}else
	{
		do{
			for(x = 0; x<10; x++){
				char aux = fgetc(fp1);
				if(aux == ' '){
					soggetto_y[y][x] = '0';
				}else{
					soggetto_y[y][x] = '1';
				}
			}
			y ++;
		}while(fgets(string, 100, fp1) != NULL);
		
		if((fp2 = fopen("immagine1.dat","r"))== NULL){																//controllo che il file esista
			printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
			exit(1);																									//ritorno il codice di errore
		}else
		{
			y=0;
			while(!feof(fp2)){
				fgets(string,100,fp2); //Prendo in input la riga
				i=0;
				maxX=0;
				while(string[i] != '\n' && string[i] != '\0'){
					//leggo il carattere se è x inserisco 1 se è un altro carattere inserisc 0
					printf("Carattere letto: %c\n", string[i]);
					if(string[i] != 'x'){
						immagine1[y][x] = 0; 
					}else{
						immagine1[y][x] = 1;
					}
					maxX++;
					i++;
				}
				//tentativo di stampare l'immagine con scarso successo.
				for(x = maxX; x<100;x++){
					immagine1[y][x] = 0;
				}
				y++;
				maxY++;
			}
			
			for(y = 0;y<maxY; y ++ ){
				for(x = 0; x<100; x++){
					printf("%d ", immagine1[y][x]);
				}
				printf("\n");
			}
		}
	}
	
	return 0;
}
