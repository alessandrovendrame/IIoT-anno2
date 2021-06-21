/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on June 1, 2021, 2:21 PM
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

//----------------------------------------------------------------------
//----------------------- DICHIARAZIONE FUNZIONI -----------------------
//----------------------------------------------------------------------

void initSys();
void sendData(char x);
void invia(char x);
void ricevi();

//-------------------------------------------------------------------------------
//----------------------- DICHIARAZIONE VARIABILI GLOBALI -----------------------
//-------------------------------------------------------------------------------

int baudRate = 0;
int count=0;

//----------------------------------------------------
//----------------------- MAIN -----------------------
//----------------------------------------------------

void main(void) {
    
    TRISDbits.TRISD6= 0;
    TRISDbits.TRISD7= 0;

    initSys();                           //inizializzo il microcontrollore
    //invia('D');
    while(1)                             //loop infinito
    {
     
    }
}

//-----------------------------------------------------------------
//----------------------- SVILUPPO FUNZIONI -----------------------
//-----------------------------------------------------------------

void initSys()                          //funzione che inizializza i bit del microcontrollore
{
    //UART TX
    
    U1MODEbits.BRGH = 0; 
    U1BRG = 62;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    
    U1STAbits.UTXEN = 1;

    //UART RX
    
    //Enabling Interrupt on receive
    
    IEC0bits.U1RXIE = 1;
    IPC6bits.U1IP = 7;
    IPC6bits.U1IS = 0;
    U1STAbits.URXISEL = 0;
    ricevi();   
    //Enabling UART receiver
    U1STAbits.URXEN = 1;
    
    //Timer 2 CONF
    
    T2CONbits.TON = 0;                  //spengo il timer in modo che non inizi subito a contare
    T2CONbits.TCKPS = 7;                //imposto il prescaler al massimo impostando i 3 bit di TCKPS a 1
    
    PR2 = 2000;                         //il numero assegnato a PR2 è la soglia del clock, una volta raggiunto lancia l'interrupt
    TMR2 = 0;                           //faccio partire il timer2 da 0
    
    IPC2bits.T2IP = 7;                  //setto la priorità sull'interrupt, quindi se ne vengono lanciati due nello stesso momento
                                        //verrà eseguito prima quello con priorità più alta
    
    IFS0bits.T2IF = 0;                  //setto l'interrupt flag di timer2 a 0
    IEC0bits.T2IE = 1;
    
    U1MODEbits.ON = 1;

    
    INTCONSET = _INTCON_MVEC_MASK;      //abilita interrupt multivettore
    
    __builtin_enable_interrupts();      //abilità l'interruttore generale di tutti gli interrupt    
}

void sendData(char x){
    U1TXREG = x;
}
void invia(char x){
    
    LATDbits.LATD6 = 1;
    LATDbits.LATD7 = 1;
    sendData(x);
    //ricevi();
}
void ricevi(){
    LATDbits.LATD6 = 0;
    LATDbits.LATD7 = 0;
}

// INTERRUPT

void __ISR(_UART_1_VECTOR, IPL7SRS) UartInterrupt(void)      //interrupt di ricezione
{    
    char var = U1RXREG;
    
   if (var == (char)'G'){
        LATDbits.LATD1 ^= 1;
        invia(var);
        T2CONbits.TON = 1;
    }
    
    IFS0bits.U1RXIF = 0;
}
void __ISR(_TIMER_2_VECTOR, IPL7SRS) T2Interrupt(void)      //interrupt di timer2
{    
    //LATDbits.LATD5 ^= 1;
    
    ++count;
    if(count >= 10){
        ricevi();
        T2CONbits.TON = 0;
        count=0;
    }
    
    IFS0bits.T2IF = 0;                                       //resetto l'interrupt del timer

}
