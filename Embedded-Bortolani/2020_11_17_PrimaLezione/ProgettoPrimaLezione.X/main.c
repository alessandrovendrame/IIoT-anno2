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
#include <stdio.h>

void main(void) {
        
    TRISA = 0b00000100;
    TRISB = 0x00;
    PORTB = 0x00;
    char oldPort;
    char aux;
    char button = 0;
    char oldButton = 0;
    char state = 0;
    int i = 0;
    char sequence [36] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
                          0x81,0x82,0x84,0x88,0x90,0xA0,0xC0,
                          0xC1,0xC2,0xC4,0xC8,0xD0,0xE0,
                          0xE1,0xE2,0xE4,0xE8,0xF0,
                          0xF1,0xF2,0xF4,0xF8,
                          0xF9,0xFA,0xFC,
                          0xFD,0xFE,
                          0xFF};
    int x,k=0;
    
    while(1){
        
        button = !(PORTA & 0x04);
        if((button == 1) && (oldButton == 0)) {
            //ho rilevato un fronte di salita
            //eseguo le operazioni che mi servono
            __delay_ms(20);
            button = !(PORTA & 0x04);
            if((button == 1) && (oldButton == 0)){
                state  = !state;
                i++;
                k=0;
                oldPort = 0x80;
            }
        }
        oldButton = button;
        
        if(i == 2){
            i = 0;
        }
        
        switch(i){
            case 0:
               for(x = 0; x < 8; x++){
                    PORTB = 0x03 << x;
                    __delay_ms(100); 
               }
               break;
            case 1:
                for(x=0;x<36;x++){
                    PORTB = sequence[x];
                    __delay_ms(100); 
                }
                break;
        }
        
    }
    return;
}
