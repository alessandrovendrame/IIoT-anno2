/*
	Nome: Somma.c
	Scopo: Somma di due numeri interi
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

int main() //somma due numeri interi
{
	int num1,num2,somma;
	
	//Input num1
	printf("Inserisci num1: ");
	scanf("%d", &num1);
	
	//Input num2
	printf("Inserisci num2: ");
	scanf("%d", &num2);
	
	//Somma num1,num2
	somma = num1+num2;
	
	printf("\n%d + %d = %d\n", num1, num2, somma);
	
	return EXIT_SUCCESS;
}
