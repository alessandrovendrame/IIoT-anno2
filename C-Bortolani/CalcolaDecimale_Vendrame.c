/*
	Nome: CalcolaDecimale_Vendrame.c
	Scopo: Dato un numero binario, di massimo 24 bit, ritornare il valore decimale
	Autore: Vendrame Alessandro
	Data creazione: 20/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

int checkBinaryNumber(char v[]); 	//funzione che controlla che il numero binario venga inserito correttamente
int countDigits(char v[]);       	//funzione che conta quanti bit sono presenti nel numero binario
int calcolaPotenza(int esponente);	//funzione che calcola la potenza di 2 con l'esponente equivalente al numero passato come parametro

int main(){
	char numeroBinario[24];			//Dichiarazione del vettore che conterrà il numero binario
	
	int nDigits=0;					//variabile che tiene salvati il numero di bits inseriti nel vettore
	int nDecimal=0;					//variabile che servirà per salvare il numero decimale
	int nInt;						//variabile ausiliaria che permette di trasformare il carattere nel numero intero da moltiplicare per la potenza di due
	
	int i,pot=0,ris;				//variabili per la lettura da vettore(i) e per il calcolo del numero decimale(pot,ris)
	
	int binaryCorrect=0;   			// variabile che serve a ciclare nel caso il numero binario venga inserito in modo sbagliato
	
	do{																						//inizio ciclo do-while
	
		printf("Inserisci il numero binario: ");											//Richiesta del numero binario
		gets(numeroBinario);																//Lettura del numero binario	
		
		binaryCorrect = checkBinaryNumber(numeroBinario);									//controllo che il numero binario sia stato inserito correttamente
		nDigits = countDigits(numeroBinario);												//salvo sulla variabile il numero di bit inseriti dall'utente
		
		if(binaryCorrect == 0){																//controllo sulla variabile "booleana" per decidere se scrivere o meno il messaggio d'errore
		
			system("cls");																	//pulisco lo schermo per avere più ordine
			printf("Il numero binario non e' stato inserito in modo corretto!\n");			//stampo il messaggio d'errore
		}
		
	}while(binaryCorrect != 1);																//nel caso in cui il numero non sia stato inserito correttamente il programma richiede l'inserimento
	
	for(i=nDigits-1;i>=0;i--){					//ciclo il vettore partendo dalla fine												
		
		nInt = (int)numeroBinario[i] - 48;		//casto il carattere inserito ad intero										
		
		ris =  nInt * calcolaPotenza(pot);		//calcolo il risultato della moltiplicazione tra il bit e la potenza di due relativa alla posizione
	
		nDecimal = nDecimal + ris;				//sommo al numero decimale il risultato della moltiplicazione
		
		pot++;									//incremento l'esponente della potenza per far funzionare correttamente il calcolo
		
	}
	
	system("cls");								//pulisco lo schermo per avere più ordine										
	printf("Il numero decimale generato dal numero binario %s e':  %d", numeroBinario, nDecimal); // stampo il numero binario e il numero decimale generato dal programma
	
	return 0; //termino l'esecuzione del codice
}

int checkBinaryNumber(char v[]){ 
	
	int i=0;								//indice per scorrere il vettore
	
	do{
		int bit = (int)v[i] - 48;			//cast del bit ad intero
				
		if((bit != 0) && (bit != 1)){		//controllo che il valore inserito sia 0 o 1 altrimenti ritorno il messaggio di errore
			return 0;			
		}
		
		i++;								//incremento i per continuare a scorrere il vettore
	}while(v[i] != '\0');
	
	if(i>24){								//nel caso in cui l'utente inserisca più di 24 caratteri, dimensione massima dell'array, verrà comunque mostrato il messaggio di errore
		return 0;
	}
	
	return 1;								//nel caso in cui non ci siano problemi invece la funzione restituisce esito positivo.
}

int calcolaPotenza(int esponente){
	int risultato=1;						//risultato della potenza
	int i;									//indice del ciclo for
	
	if(esponente == 0){						//se l'esponente è uguale a 0 la potenza darà come risultato 1
		return risultato;
	}else									//altrimenti
	{
		for(i=0;i<esponente;i++){			//se l'esponente è > 0 ogni ciclo quest'ultimo viene moltiplicato per 2 tante volte quanto il valore della variabile "esponente"
			risultato = risultato * 2;
		}
		
		return risultato;					//restituise il valore della potenza di 2
	}
}

int countDigits(char v[]){
	int i=0;                 				//indice che serve a contare i bit presenti all'interno del numero binario
	
	do{		
		i++;		
	}while(v[i] != '\0');
	
	return i;								//restituzione del numero di bit inseriti
}
