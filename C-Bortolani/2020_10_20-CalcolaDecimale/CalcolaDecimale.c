/*
	Nome: CalcolaDecimale.c
	Scopo: Dato un numero decimale stampare il numero binario
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
	int pot, somma=0, resto;
	int bin[8],i=0,k=7;
	
	for(i;i<8;i++)
	{
		printf("Inserisci un numero: ");
		scanf("%d",&bin[i]);	
	}	
	
	for(i=0;i<8;i++)
	{
		pot = pow(2,k) * bin[i];
		printf("%d\n", pot);
		somma = somma + pot;
		k--;
	}
	
	printf("Il numero decimale e': %d", somma);
}
