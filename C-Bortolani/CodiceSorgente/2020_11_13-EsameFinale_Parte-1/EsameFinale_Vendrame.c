/*
	Titolo: EsameFinale_Vendrame.c
	Data: 13/11/2020
	Autore: Vendrame Alessandro
*/

#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

#define OFFSET 30

//Struttura per gestire le temperature lette dal file
//
struct temperature{
	int temp;
	UCHAR r;
	UCHAR g;
	UCHAR b;
	char colore[50];
};

//funzione che mi permette di controllare che il pixel letto non abbia i colori scritti nel file per fare il contorno della figura
//
int checkColors(struct temperature scale[], int color, UCHAR r, UCHAR g, UCHAR b){
	int i;
	for(i=0;i<8;i++){
		if(i!=color){
			if(r == scale[i].r && g == scale[i].g && b == scale[i].b)
			{
				return 0;
			}
		}
	}
	
	return 1;
}

//Funzione che controlla i range con offset preimpostato
//
int checkRange(struct temperature scala[], int colore, UCHAR r, UCHAR g, UCHAR b){
	 
	int rangeMaxR;
	int rangeMinR;
	int rangeMaxG;
	int rangeMinG;
	int rangeMaxB;
	int rangeMinB;	
	
	if(scala[colore].r >= 255 - OFFSET){
		rangeMaxR = 255;
	}else{
		rangeMaxR = scala[colore].r + OFFSET;
	}
	if(scala[colore].g >= 255 - OFFSET){
		rangeMaxG = 255;
	}else{
		rangeMaxG = scala[colore].g + OFFSET;
	}
	if(scala[colore].b >= 255 - OFFSET){
		rangeMaxB= 255;
	}else{
		rangeMaxB = scala[colore].b + OFFSET;
	}
	
	if(scala[colore].r <= OFFSET){
		rangeMinR = 0;
	}else{
		rangeMinR = scala[colore].r - OFFSET;
	}
	if(scala[colore].g <= OFFSET){
		rangeMinG = 0;
	}else{
		rangeMinG = scala[colore].g - OFFSET;
	}
	if(scala[colore].b  <= OFFSET){
		rangeMinB = 0;
	}else{
		rangeMinB = scala[colore].b - OFFSET;
	}
	
	if(r >= rangeMinR && r <= rangeMaxR && g >= rangeMinG && g <= rangeMaxG && b >= rangeMinB && b <= rangeMaxB){
		return 1;
	}else{
		return 0;
	}
	
}

int main(int argc, char *argv[]) {
	//Dichiarazione variabili
	//
	BMP *bmp;
	BMP *bmp2;
	int i=0,k;
	int colore;
	FILE *fp;	
	UCHAR r,g,b;
	char legenda[100];
	int temp;
	struct temperature scala[8];
	bmp = BMP_ReadFile("Sicilia.bmp");
	
	int width, height, depth;
	UINT x,y;
		
	if((fp = fopen("mappa_colori.dat","r"))== NULL){																//controllo che il file esista
		printf("Il file che si vuole leggere non esiste o e' vuoto");												//messaggio di errore
		exit(1);																									//ritorno il codice di errore
	}else
	{
		fgets(legenda,100,fp);
		printf("%s\n", legenda);
		while(!feof(fp)){																							//leggo il file finche non finisce
			fscanf(fp,"%d %d %d %d ",&scala[i].temp,&scala[i].r,&scala[i].g,&scala[i].b);
			fgets(scala[i].colore,50,fp);																				
			printf("Dati letti: %d %d %d %d %s", scala[i].temp,scala[i].r,scala[i].g,scala[i].b,scala[i].colore);	//stampo le variabili letti
		}
		
		printf("\n");
		system("pause");	
		fclose(fp);																									//chiudo il file
	}
	
	system("cls");
	
	printf("Inserisci la temperatura da visualizzare: ");
	scanf("%d", &temp);																								//prendo in input la temperatura
	
	//acquisizione dimensioni immagine di partenza
	//
	width = BMP_GetWidth(bmp);
	height = BMP_GetHeight(bmp);
	depth = BMP_GetDepth(bmp);
	
	//Creazione immagine con le stesse dimensioni
	//
	bmp2 = BMP_Create(width,height,depth);
	
	for(x = 0; x < width; x++){
		for(y=0; y < height; y++){
			BMP_SetPixelRGB(bmp2,x,y,255,255,255);
		}
	}

	//Controllo la temperatura selezionata dall'utente
	//
	for(k=0;k<i;k++){
		if(temp >= scala[k].temp-2 && temp <= scala[k].temp+2 ){
			colore = k;
			printf("Temperatura selezionata: %d %d %d %d %s", scala[colore].temp,scala[colore].r,scala[colore].g,scala[colore].b,scala[colore].colore);
		}
	}
	
	//Scorro la prima immagine finchè non trovo un colore diverso dal bianco, se questo colore non fa parte degli altri colori salvati nel file allora
	//metto un pixel di quel colore per fare il contorno altrimenti controllo che sia nel range della temperatura selezionata dall'utente e lo metto nell'altra immagine
	//
	for(x = 0; x < width; x++){
		for(y=0; y < height; y++){
			BMP_GetPixelRGB(bmp,x,y,&r,&g,&b);
			
			if((r != (UCHAR)255) || (b != (UCHAR)255) || (g != (UCHAR)255)){
				if(checkColors(scala,colore,r,g,b) == 1){
					BMP_SetPixelRGB(bmp2,x,y,r,g,b);
				}else if(checkRange(scala,colore,r,g,b) == 1){
					BMP_SetPixelRGB(bmp2,x,y,r,g,b);
				}
			}			
		}
	}
	
	//salvo la nuova immagine
	//
	BMP_WriteFile(bmp2,"TempSicilia.bmp");
	
	return 0;
}
