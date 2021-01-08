/*
	Nome: CalcolaBinario.c
	Scopo: Dato un numero Decimale restituire il numero binario
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
	int num, div, resto;
	int bin[8],i=0,k,m;
	int nbin[8];
	printf("Inserisci un numero: ");
	scanf("%d",&num);
	
	do
	{
		div = num/2;
		resto = num%2;
		bin[i] = resto;
				
		i++;
		num = div;	
	}while(num!=0);
	
	for(k=0;k<i;k++)
	{
		printf("%d",bin[k]);
	}
	
	m=i-1;
	
	printf("\n\nM = %d\n\n", m);
	
	for(k=0;k<i;k++)
	{
		nbin[k] = bin[m];
		m--;
	}
	
	printf("Numero binario: ");
	
	for(k=0;k<i;k++)
	{
		printf("%d",nbin[k]);
	}
}
