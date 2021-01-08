/*
	-------APPUNTI BITMAP------
	BMP* BMP_Create(UINT width, UINT height, USHORT depth);
	BMP* BMP_ReadFile(string nameOfFile);
	
	UINT BMP_GetWidth(BMP *bmp);
	UINT BMP_GetHeight(BMP *bmp);
	USHORT BMP_GetDepth(BMP *bmp);
	
	void BMP_GetPixelRGB(BMP *bmp, UINT x, UINT y, UCHAR *r, UCHAR *g, UCHAR *b);
	void BMP_SetPixelRGB(BMP *bmp, UINT x, UINT y, UCHAR r, UCHAR g, UCHAR b);	
*/

#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	BMP *bitmap;	
	BMP *bitmap2;
	UCHAR r,g,b;
	bitmap = BMP_ReadFile("tiger.bmp");
	
	int width, height, depth;
	UINT x,y;
	UINT x1,y1;
	
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	
	bitmap2 = BMP_Create(width,height,depth);

	for(y=height-1,y1=0;y>0;y--,y1++){
		for(x=width-1,x1=0;x>0;x--,x1++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			BMP_SetPixelRGB(bitmap2,x1,y1,r,g,b);
		}
	}
	
	BMP_WriteFile(bitmap2,"tigerSpecchiata.bmp");
	
	return 0;
}
