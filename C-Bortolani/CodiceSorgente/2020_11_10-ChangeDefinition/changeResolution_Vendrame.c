#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Dichiarazione variabili
	//
	BMP *bitmap;	
	BMP *bitmap2;
	UCHAR r[4],g[4],b[4];
	UCHAR rM=0,gM=0,bM=0;
	int i;
	bitmap = BMP_ReadFile("tiger.bmp");
	
	int width, height, depth;
	UINT x,y;
	
	//acquisizione dimensioni immagine di partenza
	//
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	
	//Creazione immagine con il doppio delle dimensioni
	//
	bitmap2 = BMP_Create(width,height,depth);

	//
	//prendo i valori rgb dei 4 pixel adiacenti e faccio la media
	//successivamente posiziono 4 pixel con il valore rgb della media
	//nella nuova immagine
	//
	for(x = 0; x < width; x++){
		for(y=0; y < height; y++){
			BMP_GetPixelRGB(bitmap,x,y,&r[0],&g[0],&b[0]);
			BMP_GetPixelRGB(bitmap,x+1,y,&r[1],&g[1],&b[1]);
			BMP_GetPixelRGB(bitmap,x,y+1,&r[2],&g[2],&b[2]);
			BMP_GetPixelRGB(bitmap,x+1,y+1,&r[3],&g[3],&b[3]);
			
			rM = (r[0] + r[1] + r[2] + r[3])/4;
			gM = (g[0] + g[1] + g[2] + g[3])/4;
			bM = (b[0] + b[1] + b[2] + b[3])/4;
			
			BMP_SetPixelRGB(bitmap2,x,y,rM,gM,bM);
			BMP_SetPixelRGB(bitmap2,x,y+1,rM,gM,bM);
			BMP_SetPixelRGB(bitmap2,x+1,y,rM,gM,bM);
			BMP_SetPixelRGB(bitmap2,x+1,y+1,rM,gM,bM);
			y++;
		}
		x++;
	}
	
	//salvo la nuova immagine
	//
	BMP_WriteFile(bitmap2,"tigerResolution.bmp");
	
	return 0;
}
