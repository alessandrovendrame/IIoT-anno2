/*
	Nome: HelloWorld.c
	Scopo: Visualizzare una riga di testo
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdio.h>

// La funzione main � il punto di inizio

char *getWord()
{
	return "Ciao bello!";
}

int main(void)
{
	char *c = getWord();
	
	printf("Hello world!\n");
	printf("%s\n",c);
	return 0;  // indica che l'esecuzione � terminata con successo
}


// fine della funzione main
