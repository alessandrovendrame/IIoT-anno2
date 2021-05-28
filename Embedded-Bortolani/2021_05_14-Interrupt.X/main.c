/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on May 14, 2021, 2:45 PM
 */

//--------------------------------------------------------------
//----------------------- CONFIGURAZIONE -----------------------
//--------------------------------------------------------------

// DEVCFG3
#pragma config USERID = 0xFFFF         // Enter Hexadecimal value (Enter Hexadecimal value)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_20        // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_12       // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF            // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1        // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRIPLL          // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = ON            // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON               // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON           // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8          // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD          // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576       // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF            // Watchdog Timer Enable (WDT Enabled)

// DEVCFG0
#pragma config DEBUG = OFF             // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2       // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF               // Program Flash Write Protect (Disable)
#pragma config BWP = OFF               // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//---------------------------------------------------------------------------------
//----------------------- DICHIARAZIONE COSTANTI E LIBRERIE -----------------------
//---------------------------------------------------------------------------------

#include <xc.h>
#include <sys/attribs.h>                  //registro dell'interrupt

#define SEG_A 0x0004
#define SEG_B 0x0008
#define SEG_C 0x0020
#define SEG_D 0x0040
#define SEG_E 0x0080
#define SEG_F 0x0100
#define SEG_G 0x0800

#define N0 ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define N1 ~(SEG_B | SEG_C)
#define N2 ~(SEG_A | SEG_B | SEG_G | SEG_E | SEG_D)
#define N3 ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)
#define N4 ~(SEG_F | SEG_G | SEG_C | SEG_B)
#define N5 ~(SEG_A | SEG_F | SEG_G | SEG_C | SEG_D)
#define N6 ~(SEG_A | SEG_G | SEG_C | SEG_D | SEG_E | SEG_F)
#define N7 ~(SEG_A | SEG_B | SEG_C)
#define N8 ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define N9 ~(SEG_A | SEG_B | SEG_G | SEG_F | SEG_C | SEG_D)
#define LA ~(SEG_A | SEG_B | SEG_C | SEG_G | SEG_E | SEG_F)
#define LB ~(SEG_G | SEG_C | SEG_D | SEG_E | SEG_F)
#define LC ~(SEG_A | SEG_F | SEG_E | SEG_D) 
#define LD ~(SEG_B | SEG_C | SEG_D | SEG_E | SEG_G)
#define LE ~(SEG_A | SEG_F | SEG_G | SEG_E | SEG_D)
#define LF ~(SEG_E | SEG_F | SEG_A | SEG_G) 

//----------------------------------------------------------------------
//----------------------- DICHIARAZIONE FUNZIONI -----------------------
//----------------------------------------------------------------------

void initSys();

//-------------------------------------------------------------------------------
//----------------------- DICHIARAZIONE VARIABILI GLOBALI -----------------------
//-------------------------------------------------------------------------------

const unsigned int display[16] = {N0,N1,N2,N3,N4,N5,N6,N7,N8,N9,LA,LB,LC,LD,LE,LF};
int i = 0;

//----------------------------------------------------
//----------------------- MAIN -----------------------
//----------------------------------------------------

void main(void) {
    
    TRISD = 0x0000;
    initSys();                           //inizializzo il microcontrollore
    
    while(1)                             //loop infinito
    {
        if(i > 15)
            i=0;
        PORTD = display[i];
    }
}

//-----------------------------------------------------------------
//----------------------- SVILUPPO FUNZIONI -----------------------
//-----------------------------------------------------------------

void initSys()                          //funzione che inizializza i bit del microcontrollore
{
    TRISDbits.TRISD1 = 0;               //imposto il bit di TRISD in uscita
    LATDbits.LATD1 = 0;                 //imposto il bit del registro LATD a 0 quindi spento
    
    T2CONbits.TON = 0;                  //spengo il timer in modo che non inizi subito a contare
    T2CONbits.TCKPS = 7;                //imposto il prescaler al massimo impostando i 3 bit di TCKPS a 1
    
    OSCCONbits.PBDIV = 3;
    
    PR2 = 39063;                        //il numero assegnato a PR2 è la soglia del clock, una volta raggiunto lancia l'interrupt
    TMR2 = 0;                           //faccio partire il timer2 da 0
    
    IPC2bits.T2IP = 7;                  //setto la priorità sull'interrupt, quindi se ne vengono lanciati due nello stesso momento
                                        //verrà eseguito prima quello con priorità più alta
    
    IFS0bits.T2IF = 0;                  //setto l'interrupt flag di timer2 a 0
    IEC0bits.T2IE = 1;                  //abilito l'interrupt di timer2
    
    INTCONSET = _INTCON_MVEC_MASK;      //abilita interrupt multivettore
    
    __builtin_enable_interrupts();      //abilità l'interruttore generale di tutti gli interrupt
    
    T2CONbits.TON = 1;    
}

void __ISR(_TIMER_2_VECTOR, IPL7SRS) T2Interrupt(void)      //interrupt di timer2
{
    LATDbits.LATD1 ^= 1;                                     //con ^= faccio lo XOR con 1 e quindi inverto il bit
    IFS0bits.T2IF = 0;                                       //resetto l'interrupt del timer
    
    i = i+1;
}