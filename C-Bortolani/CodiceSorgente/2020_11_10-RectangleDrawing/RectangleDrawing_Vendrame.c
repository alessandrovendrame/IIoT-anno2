/*
	Scopo: Chiedere le dimensioni dell'immagine e le dimensioni di un rettangolo ( base altezza ) e disegnarlo
	
	Autore: Vendrame Alessandro
*/

#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	BMP *bitmap;														//Creazione puntatore al file
	
	//DICHIARAZIONE VARIABILI
	//
	int width, height, depth = 24;
	int altezza,base;
	UINT x,y;
	int ix,iy;
	
	//Acquisizione delle dimensioni dell'immagine
	//
	printf("Inserisci larghezza dell'immagine: ");
	scanf("%d",&width);
	printf("Inserisci altezza dell'immmagine: ");
	scanf("%d",&height);
	
	//Acquisizione delle coordinate di partenza del rettangolo
	//
	printf("Inserisci coordinata x di partenza del rettangolo: ");
	scanf("%d", &x);
	printf("Inserisci coordinata y di partenza del rettangolo: ");
	scanf("%d",&y);
	
	//Ciclo che chiede nuovamente le dimensioni del rettangolo nel caso in cui superino la dimensione dell'immagine
	//
	do{
		
		printf("Inserisci base del rettangolo: ");
		scanf("%d", &base);
		printf("Inserisci altezza del rettangolo: ");
		scanf("%d",&altezza);
		
	}while((x+base > width) || (y+altezza > height));
	
	//Creazione dell'immagine
	//
	bitmap = BMP_Create(width,height,depth);

	//Metto lo sfondo dell'immagine bianco
	//
	for(iy=0;iy<height;iy++){
		for(ix=0;ix<width;ix++){
			BMP_SetPixelRGB(bitmap,ix,iy,255,255,255);
		}
	}
	
	//Disegno il rettangolo
	//
	for(ix = x; ix < x + base; ix++){
		for(iy = y; iy < y + altezza; iy++){
			if(ix == x || ix == x+base-1 || iy == y || iy == y+altezza-1)
			{
				BMP_SetPixelRGB(bitmap,ix,iy,0,0,0);
			} 
		}
	}
	
	//Salvo l'immagine
	//
	BMP_WriteFile(bitmap,"rectangle.bmp");
	BMP_Free(bitmap);
	
	return 0;
}
