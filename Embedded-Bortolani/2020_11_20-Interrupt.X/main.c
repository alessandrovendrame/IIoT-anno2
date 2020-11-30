/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on November 17, 2020, 2:48 PM
 */

// PIC16F628 Configuration Bit Settings

// C source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR pin function select (RA5/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOD Reset enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Code Protection bits (Program memory code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 8000000
#include <xc.h>

int count;
int tempo = 15;
int gameChoose=0;

void main(void) {
    
    int button,oldButton;
    INTCON = 0xA0;
    OPTION_REG = 0x07;
    TRISB = 0x00;
    PORTB = 0xFF;
    TRISA = 0b00000100;
    
    count = 0;
    
    while(1){
        button = !(PORTA & 0x04);
        if((button == 1) && (oldButton == 0)) {
            //ho rilevato un fronte di salita
            //eseguo le operazioni che mi servono
            __delay_ms(20);
            button = !(PORTA & 0x04);
            if((button == 1) && (oldButton == 0)){
                gameChoose++;
                tempo += tempo; 
                if(gameChoose > 3){
                    gameChoose = 0;
                    tempo = 15;
                }
            }
        }
        oldButton = button;
    }
    return;
}

void __interrupt() lampeggio(){
    
    if(INTCON & 0x04){
        count ++;
        
        if(count > tempo){
            PORTB = ~PORTB;
            count = 0;
        }
        
        INTCON = INTCON & ~0x04;
    }
    
    
    return;
}
