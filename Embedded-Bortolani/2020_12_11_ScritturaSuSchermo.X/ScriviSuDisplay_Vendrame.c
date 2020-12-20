/*
 * File:   ScriviSuDisplay_Vendrame.c
 * Author: Alessandro Vendrame
 *
 * Created on December 11, 2020, 9:24 AM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define FIRST_DISPLAY 0x20
#define _XTAL_FREQ 8000000

#include <xc.h>

void checkKeyPad();
void print_display();

int colScan=0,rowScan=0;
char keyPressed=99, keyok=0;
int delayBtn = 0, contatore;
int stato=0;

const unsigned char colMask[3] = {
    //76543210 posizione del bit
    0b11111110,
    0b11111101,
    0b11111011
};

const unsigned char rowMask[4] = {
    //76543210 posizione del bit
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001   
};

const char displayRegular[] = {0x3F/*0*/, 0x06/*1*/, 0x5B/*2*/, 0x4F/*3*/, 0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,0x7F/*8*/,0x6F/*9*/,
                                0x77/*A*/,0x7C/*B*/,0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/};

const unsigned char keys[] ={1,4,7,'*',2,5,8,0,3,6,9,'#'};

void main(void) {
    TMR0 = 256 - 250;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
    INTCON = 0xA0;
    OPTION_REG = 0x02; 
    
    PORTA = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
    
    char numberToDisplay;
    
    while(1){
      // print_display(); 
 
        if(contatore > 3){
            //checkKeyPad();
            contatore = 0;
            stato = !stato;
        }
        
        if(stato){
            PORTB |= 0x80;
        }else{
            PORTB &= ~0x80;
        }
        
        TRISD &= ~0x0F; //impongo i primi 4 bit come INPUT
        PORTA = 0x20;

        PORTD = displayRegular[keys[keyPressed]];
        //PORTD = contatore;
        
        //__delay_ms(20);
        
        PORTA = 0x00;
    }
    return;
}

void checkKeyPad(){

    PORTA = 0x00;
    //__delay_ms(1);
    TRISD |= 0x0F; //impongo i primi 4 bit come INPUT
    
    for (colScan = 0; colScan < 3; colScan++)
    {
        PORTB = PORTB | 0x07; // porto tutte le colonne a 1
        PORTB &= colMask[colScan]; // porto a zero la colonna attuale
        for (rowScan = 0; rowScan < 4; rowScan++)
        {
            //__delay_ms(1);
            if (!(PORTD & rowMask[rowScan])) // Riga rowScan trovata a massa
            {
                // versione con delay, si può migliorare
                // rendendolo sensibile al fronte
                if (!(PORTD & rowMask[rowScan]))
                {
                    keyPressed = rowScan +(4*colScan); // numero di pulsante premuto
                    keyok = 1; // E? stato premuto un pulsante
                   // delayBtn = 0;
                }
            }
        }
    }
}


void print_display(){
    TRISD = 0x00; //tutti i pin di PORTD come OUTPUT
    TRISA = 0x00; //tutti i pin di PORTA come OUTPUT
   
    PORTA = FIRST_DISPLAY;
    PORTD = displayRegular[keyPressed];
}

void __interrupt() IRC(){
    
    if(INTCON & 0x04){
       contatore++;
       TMR0 = 256 - 250;
       
       INTCON = INTCON & ~0x04;
    }
}