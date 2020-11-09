#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	BMP *bmp;	
	BMP *bmp2;
	BMP *bmp3;
	UCHAR r,g,b;
	UCHAR r1,g1,b1;
	
	bmp = BMP_ReadFile("greenScreenMaurito.bmp");
	bmp2 = BMP_ReadFile("backgroundImage.bmp");	
	
	int width, height, depth;
	UINT x,y;
	UINT x1,y1;
	
	width = BMP_GetWidth(bmp);
	height = BMP_GetHeight(bmp);
	depth = BMP_GetDepth(bmp);
	
	bmp3 = BMP_Create(width,height,depth);

	for(y=0;y<height;y++){
		for(x=0;x<width;x++){
			
			BMP_GetPixelRGB(bmp,x,y,&r,&g,&b);
			BMP_GetPixelRGB(bmp2,x,y,&r1,&g1,&b1);
			
			if((r>=0 && r<=150) && (g>=230 && g<=255) && (b>=0 && b<=150)){
				//printf("Dentro if\n");
				BMP_SetPixelRGB(bmp3,x,y,r1,g1,b1);
			}else
			{
				BMP_SetPixelRGB(bmp3,x,y,r,g,b);
			}			
		}
	}
	
	BMP_WriteFile(bmp3,"mix.bmp");
	
	return 0;
}
