/*
	Nome: Codifica.c
	Scopo: Leggere una frase in input, stamparla, se sono presenti vocali vanno susseguite da una f se sono minuscole e da una F se sono maiuscole
	Autore: Vendrame Alessandro
	Data creazione: 23/10/2020
*/

#include <stdio.h>
#include <string.h>

void inserisciF(char *vStart, char *vFinish, int l1);

int main(){
	char v1[100],v2[100];
	int l=0,i=0;
	
	printf("Inserisci la frase da modificare: ");
	gets(v1);
	
	system("cls");
	
	printf("Frase inserita: ");
	do{
		printf("%c",v1[i]);
		i++;
	}while(v1[i] != NULL);
	
	inserisciF(v1,v2,i);
	
	printf("\n\nFrase codificata: %s", v2);
	
	return 0;
}

void inserisciF(char *vStart, char *vFinish, int l1)
{
	int i,lung=0;
	for(i=0; i<l1; i++){
		vFinish[lung] = vStart[i];
		
		if((vStart[i] == 'a') || (vStart[i] == 'e') || (vStart[i] == 'i') || (vStart[i] == 'o') || (vStart[i] == 'u')){
			lung++;
			vFinish[lung] = 'f';
		}else if((vStart[i] == 'A') || (vStart[i] == 'E') || (vStart[i] == 'I') || (vStart[i] == 'O') || (vStart[i] == 'U')){
			lung++;
			vFinish[lung] = 'F';
		}
		
		lung++;		
	}
	
	vFinish[lung] = '\0';
}
