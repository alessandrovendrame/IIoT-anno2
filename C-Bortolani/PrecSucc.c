/*
	Nome: Somma.c
	Scopo: Dato un numero stampare il numero precedente e quello successivo a quello inserito
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num,prec,succ;
	
	printf("Inserisci un numero: ");
	scanf("%d",&num);
	
	//Primo metodo
	prec = num-1;
	succ = num+1;	
	printf("\nIl numero precedente e' %d, mentre il numero successivo e' %d\n\n", prec, succ);
	
	//Secondo metodo
	printf("Il numero precedente e' %d, mentre il numero successivo e'%d", num-1, num+1);
	
	return EXIT_SUCCESS;
}
