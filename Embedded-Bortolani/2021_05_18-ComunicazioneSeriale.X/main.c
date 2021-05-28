/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on May 18, 2021, 2:45 PM
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

//COSTANTI

#define BOTTONE_1 PORTDbits.RD2
#define BOTTONE_2 PORTDbits.RD3
#define DATI LATDbits.LATD5
#define CLOCK LATDbits.LATD6

//----------------------------------------------------------------------
//----------------------- DICHIARAZIONE FUNZIONI -----------------------
//----------------------------------------------------------------------

void initSys();
void getButton();

//-------------------------------------------------------------------------------
//----------------------- DICHIARAZIONE VARIABILI GLOBALI -----------------------
//-------------------------------------------------------------------------------

int i = 0;
int t3bits = 0;
char running = 0;

char bottone1 = -1 , o_bottone1 = -1, checkb1 = 0, contButton = 0;
char bottone2 = -1, o_bottone2 = -1, checkb2 = 0, contButton2 = 0;

char bottone_1_ON = 0;
char bottone_2_ON = 0;

char IdPressedButton = 0;                     //0x01 = button1 , 0x02 = button2 

char acceso = 0xAA;
char spento = 0xF0;
int serialIndex = 0;

//----------------------------------------------------
//----------------------- MAIN -----------------------
//----------------------------------------------------

void main(void) {
    
    TRISD = 0x0000;
    initSys();                           //inizializzo il microcontrollore
    
    while(1)                             //loop infinito
    {
        getButton();
    }
}

//-----------------------------------------------------------------
//----------------------- SVILUPPO FUNZIONI -----------------------
//-----------------------------------------------------------------

void initSys()                          //funzione che inizializza i bit del microcontrollore
{
    TRISDbits.TRISD1 = 0;               //imposto il bit di TRISD in uscita
    TRISDbits.TRISD2 = 1;
    TRISDbits.TRISD3 = 1;
    LATDbits.LATD1 = 0;                 //imposto il bit del registro LATD a 0 quindi spento
    
    LATDbits.LATD6 = 0;
    LATDbits.LATD5 = 0;
    
    //TIMER 2 CONF
    
    T2CONbits.TON = 0;                  //spengo il timer in modo che non inizi subito a contare
    T2CONbits.TCKPS = 7;                //imposto il prescaler al massimo impostando i 3 bit di TCKPS a 1
    
    PR2 = 2000;                         //il numero assegnato a PR2 è la soglia del clock, una volta raggiunto lancia l'interrupt
    TMR2 = 0;                           //faccio partire il timer2 da 0
    
    IPC2bits.T2IP = 7;                  //setto la priorità sull'interrupt, quindi se ne vengono lanciati due nello stesso momento
                                        //verrà eseguito prima quello con priorità più alta
    
    IFS0bits.T2IF = 0;                  //setto l'interrupt flag di timer2 a 0
    IEC0bits.T2IE = 1;                  //abilito l'interrupt di timer2
    
    //TIMER 3 CONF
    
    T3CONbits.TON = 0;                  //spengo il timer in modo che non inizi subito a contare
    T3CONbits.TCKPS = 7;                //imposto il prescaler al massimo impostando i 3 bit di TCKPS a 1
    
    PR3 = 250;                        //il numero assegnato a PR3 è la soglia del clock, una volta raggiunto lancia l'interrupt
    TMR3 = 0;                           //faccio partire il timer3 da 0
    
    IPC3bits.T3IP = 7;                  //setto la priorità sull'interrupt, quindi se ne vengono lanciati due nello stesso momento
                                        //verrà eseguito prima quello con priorità più alta
    
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    
    //INTERRUPT CONF
    
    INTCONSET = _INTCON_MVEC_MASK;      //abilita interrupt multivettore
    
    __builtin_enable_interrupts();      //abilità l'interruttore generale di tutti gli interrupt
    
    T2CONbits.TON = 1;  
}

void __ISR(_TIMER_2_VECTOR, IPL7SRS) T2Interrupt(void)      //interrupt di timer2
{    
    //LATDbits.LATD5 ^= 1;
    
    i = i+1;
    
    IFS0bits.T2IF = 0;                                       //resetto l'interrupt del timer

}

void __ISR(_TIMER_3_VECTOR, IPL7SRS) T3Interrupt(void)      //interrupt di timer3
{
    //LATDbits.LATD1 ^= 1;                                     //con ^= faccio lo XOR con 1 e quindi inverto il bit
    
    if( (t3bits + 1)%2 == 0)
    {
        if(t3bits<15)
        {
            char aux = (IdPressedButton >> serialIndex) & 1;
            DATI = aux;
            
            serialIndex++;
        }else{
            if((IdPressedButton == (char)0xd1) && bottone_1_ON)
            {
                DATI = (acceso >> serialIndex) & 1; 
            }
            else if((IdPressedButton == (char)0xd1) && !bottone_1_ON)
            {
                DATI = (spento >> serialIndex) & 1;   
            }else if((IdPressedButton == (char)0xd2) && bottone_2_ON)
            {
                DATI = (acceso >> serialIndex) & 1;   
            }else if((IdPressedButton == (char)0xd2) && !bottone_2_ON)
            {
                DATI = (spento >> serialIndex) & 1;   
            }
            
            serialIndex++;
        }
        
    }
    
    CLOCK ^= 1;
    
    t3bits++;
    
    if(serialIndex > 7){
        serialIndex = 0;
    }
        
    if(t3bits > 31){
        T3CONbits.TON = 0;
        serialIndex = 0;
        t3bits = 0;
        running = 0;
        DATI = 0;
    }

    IFS0bits.T3IF = 0;                                      //resetto l'interrupt del timer
}


void getButton(){  
    
    //BOTTONE 1
    
    bottone1 = !(BOTTONE_1); // CHECK LEVEL LOGIC RD2
    if(((bottone1 == 1)&&(o_bottone1 == 0)) || checkb1 == 1) {
       checkb1 = 1;
       bottone1 = !(BOTTONE_1);
       if(((bottone1 == 1) && (o_bottone1 == 0)) || contButton >= 1) {
           checkb1 = 0;
           contButton = 0;
           
           if(!running){
               running = 1;
               bottone_1_ON = !bottone_1_ON;
               
               IdPressedButton = (char)0xd1;
               
               DATI = (IdPressedButton >> serialIndex) & 1;
                              
               serialIndex++;
               
               T3CONbits.TON = 1; 
           }           
           
       }
    }
    
    o_bottone1 = bottone1;
    
    //BOTTONE 2
    
    bottone2 = !(BOTTONE_2); // CHECK LEVEL LOGIC RD2
    if(((bottone2 == 1)&&(o_bottone2 == 0)) || checkb2 == 1) {
       checkb2 = 1;
       bottone2 = !(BOTTONE_2);
       if(((bottone2 == 1) && (o_bottone2 == 0)) || contButton2 >= 1) {
           checkb2 = 0;
           contButton2 = 0;
           
           if(!running){
               running = 1;
               bottone_2_ON = !bottone_2_ON;
               
               IdPressedButton = (char)0xd2;
               
               DATI = (IdPressedButton >> serialIndex) & 1;
               
               serialIndex++;
               
               T3CONbits.TON = 1; 
           }           
           
       }
    }
    
    o_bottone2 = bottone2;
    
}

