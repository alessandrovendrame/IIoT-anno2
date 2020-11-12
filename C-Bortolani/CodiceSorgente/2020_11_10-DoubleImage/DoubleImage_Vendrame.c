#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Dichiarazione variabili
	//
	BMP *bitmap;	
	BMP *bitmap2;
	UCHAR r,g,b;
	bitmap = BMP_ReadFile("tiger.bmp");
	
	int width, height, depth;
	UINT x,y;
	UINT x1,y1;
	
	//acquisizione dimensioni immagine di partenza
	//
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	
	//Creazione immagine con il doppio delle dimensioni
	//
	bitmap2 = BMP_Create(width*2,height*2,depth);

	//
	//Ciclo sulla lunghezza doppia e dato che x e y sono interi dividendo per 2
	//si otterrà l'intero per difetto
	//
	for(x = 0; x < width*2; x++){
		for(y=0; y < height*2; y++){
			BMP_GetPixelRGB(bitmap,x/2,y/2,&r,&g,&b);
			BMP_SetPixelRGB(bitmap2,x,y,r,g,b);
		}
	}
	
	//salvo la nuova immagine
	//
	BMP_WriteFile(bitmap2,"tigerDoppia.bmp");
	
	return 0;
}
