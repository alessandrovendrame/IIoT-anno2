/*
	Nome: Serach.c
	Scopo: Dato un vettore di interi trovare il numero inserito dall'utente al suo interno
	Autore: Vendrame Alessandro
	Data creazione: 23/10/2020
*/

#include <stdio.h>
#include <string.h>

int main()
{
	int v[30],nToInsert,i;
	int nToFind,numberOfTimes=0,positions[30];
	
	printf("Quanti numeri vuoi inserire: ");
	scanf("%d",&nToInsert);
	
	system("cls");
	
	for(i = 0; i<nToInsert; i++){
		printf("Inserisci il numero in posizione %d: ", (i+1));
		scanf("%d",&v[i]);
	}
	
	system("cls");
	
	printf("Inserisci il numero da trovare: ");
	scanf("%d",&nToFind);
	
	system("cls");
	
	for(i=0; i<nToInsert; i++){
		if(v[i] == nToFind){
			positions[numberOfTimes] = i;
			numberOfTimes++;
		}
	}
	
	stampaVettore(v,nToInsert);
	
	if(numberOfTimes > 0){
		printf("\n\n\nIl numero %d compare %d volte nel vettore inserito nelle seguenti posizioni: \n", nToFind, numberOfTimes);
		
		for(i=0;i<numberOfTimes;i++){
			printf("v[%d]: %d", i, positions[i]);
		}
	}else
	{
		printf("\nIl numero %d non compare nel vettore inserito.", nToFind);
	}
	return 0;
}

void stampaVettore(int vett[], int l){
	int i = 0;
	
	printf("Vettore inserito: \n\n");
	
	for(i; i<l; i++){
		printf("%d ", vett[i]);
	}
}
