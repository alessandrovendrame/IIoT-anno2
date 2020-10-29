/*
	Nome: CalcolaGiorni.c
	Scopo: Inserita una data, dire se è corretta e poi calcolare la distanza in giorni con un altra data inserita
	Autore: Vendrame Alessandro
	Data creazione: 23/10/2020
*/

#include <stdio.h>
#include <string.h>

int checkData(char data[10]){
   int giorni,mesi,anni;
   int ciclo = 0;
   
   char * token = strtok(data, "/");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      printf( "%s\n", token ); //printing each token
      token = strtok(NULL, "/");
      
      switch(ciclo){
      	case 0:
      		giorni = (int)token;
      		break;
      	case 1:
      		mesi = (int)token;
      		break;
      	case 2:
      		anni = (int)token;
      		break;
	  }
   }
   
   if(giorni>0 && giorni<32){
   		if(mesi>0 && mesi<13){
   			if(anni > 0){
   				return 1;
			}else{
				return 0;
			}	
		}else{
			return 0;
		}
   }else{
   		return 0;
   }
}

int main()
{
	char data_1[10], data_2[10];
	int corretta;
	
	do{
		printf("Inserisci la prima data: ");
		scanf("%s", &data_1);
		corretta = checkData(data_1);
		
		if(corretta == 0){
			printf("La data inserita e' sbagliata, inseriscila nuovamente. \n");
		}
	}while(corretta==0);
	
	do{
		printf("Inserisci la seconda data: ");
		scanf("%s", &data_2);
		corretta = checkData(data_2);
		
		if(corretta == 0){
			printf("La data inserita e' sbagliata, inseriscila nuovamente. \n");
		}
	}while(corretta==0);
}
