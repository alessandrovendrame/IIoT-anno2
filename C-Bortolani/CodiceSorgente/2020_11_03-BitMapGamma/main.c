#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	BMP *bitmap;	
	BMP *bmp2;
	UCHAR r,g,b;
	UCHAR rM,gM,bM;
	float percentuale;
	float percChange, aux;
	char scelta;
	int cambiamento;
	
	bitmap = BMP_ReadFile("tiger.bmp");
	
	int width, height, depth;
	UINT x,y;
	
	printf("Inserisci la percentuale di cambiamento: ");
	scanf("%f",&percentuale);
		
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	bmp2 = BMP_Create(width,height,depth);

	for(y=0;y<height;y++){
		for(x=0;x<width;x++){
			
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			
			rM = r * (percentuale/100);
			gM = g * (percentuale/100);
			bM = b * (percentuale/100);
			
			BMP_SetPixelRGB(bmp2,x,y,rM,gM,bM);
		}
	}
	
	BMP_WriteFile(bmp2,"tigerGamma.bmp");
	
	return 0;
}



/// r *  perc ==> (
