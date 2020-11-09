#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	BMP *bitmap;	
	BMP *bmp1,*bmp2,*bmp3,*bmp4;
	BMP *composedImage;
	UCHAR r,g,b;
	bitmap = BMP_ReadFile("tiger.bmp");
	
	UINT width, height;
	USHORT depth;
	UINT halfWidth, halfHeight;
	UINT x,y;
	
	width = BMP_GetWidth(bitmap);
	height = BMP_GetHeight(bitmap);
	depth = BMP_GetDepth(bitmap);
	halfWidth = width/2;
	halfHeight = height/2;
	
	bmp1 = BMP_Create(halfWidth,halfHeight,depth);
	bmp2 = BMP_Create(halfWidth,halfHeight,depth);
	bmp3 = BMP_Create(halfWidth,halfHeight,depth);
	bmp4 = BMP_Create(halfWidth,halfHeight,depth);

	composedImage = BMP_Create(width,height,depth);
	//-----------PRIMA IMMAGINE------------------

	for(y=0;y<halfHeight;y++){
		for(x=0;x<halfWidth;x++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			BMP_SetPixelRGB(bmp1,x,y,r,g,b);
		}
	}
	
	BMP_WriteFile(bmp1,"tiger1.bmp");
	
	//------------SECONDA IMMAGINE---------------
	
	for(y=0;y<halfHeight;y++){
		for(x=halfWidth;x<width;x++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			BMP_SetPixelRGB(bmp2,x-halfWidth,y,r,g,b);
		}
	}
	
	BMP_WriteFile(bmp2,"tiger2.bmp");
	
	//--------------TERZA IMMAGINE----------------
	
	for(y=halfHeight;y<height;y++){
		for(x=0;x<halfWidth;x++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			BMP_SetPixelRGB(bmp3,x,y-halfHeight,r,g,b);
		}
	}
	
	BMP_WriteFile(bmp3,"tiger3.bmp");
	
	//--------------QUARTA IMMAGINE----------------
	
	for(y=halfHeight;y<height;y++){
		for(x=halfWidth;x<width;x++){
			BMP_GetPixelRGB(bitmap,x,y,&r,&g,&b);
			BMP_SetPixelRGB(bmp4,x-halfWidth,y-halfHeight,r,g,b);
		}
	}
	
	BMP_WriteFile(bmp4,"tiger4.bmp");
	
	//---------------RICOMPOSIZIONE IMMAGINE-----------
	
	for(y=0;y<halfHeight;y++){
		for(x=0;x<halfWidth;x++){
			BMP_GetPixelRGB(bmp1,x,y,&r,&g,&b);
			BMP_SetPixelRGB(composedImage,x,y,r,g,b);
		}
	}
	for(y=0;y<halfHeight;y++){
		for(x=halfWidth;x<width;x++){
			BMP_GetPixelRGB(bmp2,x-halfWidth,y,&r,&g,&b);
			BMP_SetPixelRGB(composedImage,x,y,r,g,b);
		}
	}
	for(y=halfHeight;y<height;y++){
		for(x=0;x<halfWidth;x++){
			BMP_GetPixelRGB(bmp3,x,y-halfHeight,&r,&g,&b);
			BMP_SetPixelRGB(composedImage,x,y,r,g,b);
		}
	}
	for(y=halfHeight;y<height;y++){
		for(x=halfWidth;x<width;x++){
			BMP_GetPixelRGB(bmp4,x-halfWidth,y-halfHeight,&r,&g,&b);
			BMP_SetPixelRGB(composedImage,x,y,r,g,b);
		}
	}
	
	BMP_WriteFile(composedImage,"tigerComposed.bmp");
	
	return 0;
}
