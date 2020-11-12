/*
	Scopo: Leggere un codice a barre e tradurlo in un numero esadecimale
*/

#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Dichiarazione variabili
	//
	BMP *bitmap;	
	UCHAR r,g,b;
    char binaryNumber[16];
	bitmap = BMP_ReadFile("BarCode.bmp");
	
	int width;
	UINT x=0,y=1;
	int n=0;
	
	width = BMP_GetWidth(bitmap);

	//
	//Dato che bisogna controllare solo i pixel neri per capire di che bit si tratta
	//faccio partire x da 0 e lo incremento di 8 in modo tale che vada a controllare in realtà il 9 pixel
	//nel caso in cui quest'ultimo sia bianco allora andrò ad inserire nel vettore il carattere 0 altrimenti 
	//inserirò 1.
	//
	
	while (x<width){
        x+=8;
        BMP_GetPixelRGB( bitmap, x, y, &r, &g, &b );
        if(r==255 && g==255 && b==255){
            binaryNumber[n]='0';
        }
        else 
		{
			binaryNumber[n]='1';
		}
        n++;
        x+=24;
    }
    
    binaryNumber[n] = '\0';
    
    printf("%s", binaryNumber);
	
	//Converto il numero binario in numero esadecimale
	//
    char *a = binaryNumber;
    int num = 0;
    do {
        int b = *a=='1'?1:0;
        num = (num<<1)|b;
        a++;
    } while (*a);
	
	//stampo il numero esadecimale
	//
	printf("\nIl numero esadecimale estratto dal codice a barre e': %X", num);
	
	return 0;
}
