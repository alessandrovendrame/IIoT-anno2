#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void convertToBinary(char *hex,char *binary)
{
	int i;
	
	for(i=0;i<4;i++)
	{
		switch(hex[i])
		{
			case '0':
	            strcat(binary,"0000"); 
				break;
	        case '1':
	            strcat(binary,"0001"); 
				break;
	        case '2':
	            strcat(binary,"0010");
				break;
	        case '3':
	            strcat(binary,"0011"); 
				break;
	        case '4':
	            strcat(binary,"0100"); 
				break;
	        case '5':
	            strcat(binary,"0101"); 
				break;
	        case '6':
	            strcat(binary,"0110"); 
				break;
	        case '7':
	            strcat(binary,"0111"); 
				break;
	        case '8':
	            strcat(binary,"1000");
				break;
	        case '9':
	            strcat(binary,"1001"); 
				break;
	        case 'A':
	            strcat(binary,"1010"); 
				break;
	        case 'B':
	            strcat(binary,"1011"); 
				break;
	        case 'C':
	            strcat(binary,"1100"); 
				break;
	        case 'D':
	            strcat(binary,"1101"); 
				break;
	        case 'E':
	            strcat(binary,"1110"); 
				break;
	        case 'F':
	            strcat(binary,"1111"); 
				break;
	        case 'a':
	            strcat(binary,"1010"); 
				break;
	        case 'b':
	            strcat(binary,"1011"); 
				break;
	        case 'c':
	            strcat(binary,"1100"); 
				break;
	        case 'd':
	            strcat(binary,"1101"); 
				break;
	        case 'e':
	            strcat(binary,"1110"); 
				break;
	        case 'f':
	            strcat(binary,"1111"); 
				break;
	        default:
	            printf("\n Invalid hexa digit %c ", hex[i]);
		}
		
	}
}

int main(int argc, char *argv[]) {
	BMP *bitmap;
	int i;
	char hexNumber[4];
	char binNumber[16] = "\0";
	int fx=0,fy=0;
	UINT x,y;
		
	bitmap = BMP_Create(512,200,24);
	
	printf("Inserisci il numero esadecimale di 4 cifre:");
	gets(hexNumber);
	
	convertToBinary(hexNumber,binNumber);
	printf("%s", binNumber);	
	
	for(i=0;i<16;i++){
		if(binNumber[i] == '0'){  //se 0 8px, se 1 24 px
			
			printf("Numero bin: %c\n",binNumber[i]);
			for(x=fx;x<fx+8;x++){
				for(y=0;y<200;y++){
					BMP_SetPixelRGB(bitmap,x,y,0,0,0);
				}
			}
			fx+=8;
			
			printf("Fx = %d\n", fx);
			
			for(x=fx;x<fx+24;x++){
				for(y=0;y<200;y++){
					BMP_SetPixelRGB(bitmap,x,y,255,255,255);
				}
			}
			fx+=24;
			printf("Fx = %d\n", fx);
			
		}else{
			printf("Numero bin: %c\n",binNumber[i]);
			for(x=fx;x<fx+24;x++){
				for(y=0;y<200;y++){
					BMP_SetPixelRGB(bitmap,x,y,0,0,0);
				}
			}
			fx+=24;
			
			printf("Fx = %d\n", fx);
			
			for(x=fx;x<fx+8;x++){
				for(y=0;y<200;y++){
					BMP_SetPixelRGB(bitmap,x,y,255,255,255);
				}
			}
			fx+=8;
			
			printf("Fx = %d\n", fx);
			
		}
	}
	
	BMP_WriteFile(bitmap,"BarCode.bmp");
	
	return 0;
}
