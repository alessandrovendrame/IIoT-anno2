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
	int soglia;
	int media;
	
	//Richiesta della soglia da controllare
	//
	printf("Inserisci la soglia: ");
	scanf("%d",&soglia);	
	
	//Acquisizione delle dimensioni dell'immagine
	//
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	
	//Creazione della seconda immagine
	//
	bitmap2 = BMP_Create(width,height,depth);

	for(x=0;x<width;x++){
		for(y=0;y<height;y++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			media= (r+g+b)/3;
			
			if(media > soglia){								//se la media supera la soglia metto il colore bianco
				BMP_SetPixelRGB(bitmap2,x,y,255,255,255);
			}else
			{
				BMP_SetPixelRGB(bitmap2,x,y,0,0,0);			//altrimenti metto il colore nero
			}
		}
	}
	
	BMP_WriteFile(bitmap2,"tigerBiancoNero.bmp");			//Salvo la nuova immagine
	BMP_Free(bitmap2);
	
	return 0;
}
