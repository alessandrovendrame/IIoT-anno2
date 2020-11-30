/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on November 30, 2020, 3:07 PM
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

int timerFirstLed=0;
int timerSecondLedOff=0;
int timerSecondLedOn=0;
int statoFirstLed=1;
int statoSecondLedPre=0;
int statoSecondLedPost=0;
int button=0;
int oldButton=0;
int buttonState;

void main(void) {
    TMR0 = 256 - 250;                           //Imposto il timer con partenza a 6 in modo da avere un delay di 1 millisecondo
    TRISA = 0b00000100;                         //Imposto la porta in modo che abbia un pin in input
    TRISB = 0x00;                               //Metto tutti i bit di PORTB in output
    PORTB = 0x00;                               //Spengo tutti i bit di PORTB
    INTCON = 0xA0;                              //Imposto l'interrupt
    OPTION_REG = 0x02;                          //Metto il prescaler a 1:8
    
    while(1){
        
    }
    
    return;
}

void __interrupt() lampeggio(){
    
    if(INTCON & 0x04){
        timerFirstLed++;                            //incremento il timer del primo led
        
        if(timerFirstLed >= 2000){                  //quando passano 2 secondi accendo o spengo il led
            if(statoFirstLed == 1){
                statoFirstLed = 0;
                PORTB = PORTB & 0x02;
            }else{
                statoFirstLed = 1;
                PORTB = PORTB | 0x01;
            }
            timerFirstLed = 0;                      //resetto il timer del led
        }
        
        if(statoSecondLedPre == 1){                 //nel caso in cui venga premuto il pulsante comincio ad incrementare un timer per il secondo led
            timerSecondLedOff++;
            if(timerSecondLedOff >= 5000){          //quando il timer arriva a 5 secondi accende il secondo led mentre il primo continua a lampeggiare
                PORTB = PORTB | 0x02;
                timerSecondLedOff = 0;
                statoSecondLedPre=0;
                statoSecondLedPost=1;
            }
        }
        
        if(statoSecondLedPost == 1){                //dopo che si è acceso il led parte un altro timer che conta per 4 secondi 
            timerSecondLedOn++;
            if(timerSecondLedOn >= 4000){           //raggiunti i 4 secondi spengo il led mantenedo il primo in lampeggio
                timerSecondLedOn=0;
                statoSecondLedPost=0;
                PORTB = PORTB & 0x01;
            }
        }
        
        button = !(PORTA & 0x04);                       //Se il pulsante viene premuto
        if((button == 1) && (oldButton == 0)) {         
            //ho rilevato un fronte di salita
            //eseguo le operazioni che mi servono
            button = !(PORTA & 0x04);
            if((button == 1) && (oldButton == 0)){     //mi assicuro che il pulsante sia ancora premuto e in caso
                buttonState  = !buttonState;           //attivo il flag sul pulsante e imposto il timer dell'accensione a 0
                statoSecondLedPre = 1;
                timerSecondLedOff = 0;
            }
        }
        oldButton = button;
        
        INTCON = INTCON & ~0x04;
    } 
    
    return;
}

