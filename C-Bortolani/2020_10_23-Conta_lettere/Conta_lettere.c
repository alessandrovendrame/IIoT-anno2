/*
	Nome: Codifica.c
	Scopo: Leggere una frase in input, stamparla, stampare quante consonanti e quante vocali sono prsenti
	Autore: Vendrame Alessandro
	Data creazione: 23/10/2020
*/

#include <stdio.h>
#include <string.h>

void checkLetter(char let[], int *comparse, char frase[]){
	int i=0, k;
	
	do{
		for(k=0;k<26;k++){
			if((let[k] == frase[i]) || ((let[k]-32) == frase[i])){
				comparse[k]++;
			}
		}
		i++;
	}while(frase[i]!=NULL);
}

int main(){
	char lettere[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int comparse[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char frase[100];
	int nvocali=0, nconsonanti=0;
	int i=0,l;
	
	printf("Inserisci una frase: ");
	gets(frase);
	
	checkLetter(lettere,comparse,frase);
	
	system("cls");
	printf("Le lettere comparse: \n");
	
	for(i=0;i<26;i++){
		printf("%c: %d\n", lettere[i], comparse[i]);
		if((lettere[i] == 'a') || (lettere[i] == 'e') || (lettere[i] == 'i') || (lettere[i] == 'o') || (lettere[i] == 'u')){
			nvocali = nvocali + comparse[i];
		}else{
			nconsonanti = nconsonanti + comparse[i];
		}
	}
	
	printf("\n\nVocali presenti nella stringa: %d", nvocali);
	printf("\nConsonanti presenti nella stringa: %d", nconsonanti);
	
	return 0;
	
}
