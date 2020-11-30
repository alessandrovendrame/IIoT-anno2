/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on November 27, 2020, 3:58 PM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR pin function select (RA5/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOD Reset enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Code Protection bits (Program memory code protection off)

#define _XTAL_FREQ 8000000
#include <xc.h>

int count=0;
int unita=0;
int decine=0;
int stato=0;

const char display[16] = {0xEE, 0x28, 0xcd, 0x6d, 0x2b, 0x67, 0xe7, 0x2c, 
                          0xef, 0x6f, 0xaf, 0xe3, 0xc6, 0xe9, 0xc7, 0x87};

void main(void) {
    TRISB = 0x00;
    PORTB = 0x00;
    INTCON = 0xA0;
    OPTION_REG = 0b00001000;
    
    while(1){
        
        
        
    }
    
    return;
}

void __interrupt() conteggio(){
    
    
    if(INTCON & 0x04){
        stato = !stato;
        count ++;
        
        if(stato == 1){
            PORTB = display[unita];
            PORTB = PORTB | 0x10;
        }else
        {
            PORTB = display[decine];
            PORTB = PORTB & ~0x10;
        }
        
        if(count > 8000){            
            count = 0;
            unita ++;
            if(unita > 9){
                unita = 0;
                decine ++;
                if(decine > 9){
                    decine = 0;
                }
            }
        }
        
        INTCON = INTCON & ~0x04;
    }
    
    
    return;
}