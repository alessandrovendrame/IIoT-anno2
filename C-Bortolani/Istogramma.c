/*
	Nome: Istogramma.c
	Scopo: Scrivere un programma che riceve in input dei valori interi, e che li stampa con n asterischi pari al valore del numero inserito
	Autore: Vendrame Alessandro
	Data creazione: 23/10/2020
*/

#include <stdio.h>
#include <string.h>

void stampaAsterischi(int vet[], int l);

int main(){
	int vett[50], lun;
	int i;
	
	printf("Inserisci il numero di elementi da inserire: ");
	scanf("%d", &lun);
	
	for(i=0;i<lun;i++){
		printf("Elemento %d: ", i);
		scanf("%d", &vett[i]);
	}
	
	stampaAsterischi(vett,lun);
	
	return 0;
}

void stampaAsterischi(int vet[], int l){
	int i,k;
	system("cls");
	printf("Istogramma generato: \n\n");
	
	for(i=0;i<l;i++){
		printf("Elemento %d: %d   ", i, vet[i]);
		for(k=0;k<vet[i];k++){
			printf("*");
		}
		printf("\n");
	}
}
