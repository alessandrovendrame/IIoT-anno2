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
#define REPARTO_ID 0x10
#define BOTTONE_1 PORTDbits.RD5

// DEFINE SEGMENT PORT
#define SEG_A 1 << 8    //RD8
#define SEG_B 1 << 7    //RD7
#define SEG_C 1 << 5    //RD5
#define SEG_D 1 << 4    //RD4
#define SEG_E 1 << 3    //RD2
#define SEG_F 1 << 11   //RD9
#define SEG_G 1 << 6    //RD6

//DEFINE COMBINATION TO OPEN 7SEGMENT
#define N0 ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define N1 ~(SEG_B | SEG_C)
#define N2 ~(SEG_A | SEG_B | SEG_G | SEG_E | SEG_D)
#define N3 ~(SEG_A | SEG_B | SEG_G | SEG_C | SEG_D)
#define N4 ~(SEG_F | SEG_B | SEG_G | SEG_C)
#define N5 ~(SEG_A | SEG_F | SEG_G | SEG_C | SEG_D)
#define N6 ~(SEG_A | SEG_F | SEG_G | SEG_C | SEG_D | SEG_E)
#define N7 ~(SEG_A | SEG_B | SEG_C)
#define N8 ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define N9 ~(SEG_A | SEG_B | SEG_F | SEG_G | SEG_C | SEG_D)

//----------------------------------------------------------------------
//----------------------- DICHIARAZIONE FUNZIONI -----------------------
//----------------------------------------------------------------------

void initSys();
void sendData(char x);
void invia(char x);
void ricevi();
char checkDestination(char id);
void saveString(char *s);
//-------------------------------------------------------------------------------
//----------------------- DICHIARAZIONE VARIABILI GLOBALI -----------------------
//-------------------------------------------------------------------------------

int baudRate = 0;
int count=0;
char string[50];
char numeroCoda[50];
char carattere,typeOfMessage;
int indice=0;

const unsigned int display[10] = {N0,N1,N2,N3,N4,N5,N6,N7,N8,N9};

//----------------------------------------------------
//----------------------- MAIN -----------------------
//----------------------------------------------------

void main(void) {
    
  

    initSys();                           //inizializzo il microcontrollore
    //invia('D');
    while(1)                             //loop infinito
    {
       PORTD = display[numeroCoda[0] - '0']; 
    }
}

//-----------------------------------------------------------------
//----------------------- SVILUPPO FUNZIONI -----------------------
//-----------------------------------------------------------------

void initSys()                          //funzione che inizializza i bit del microcontrollore
{
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISDbits.TRISD6= 0;
    TRISD = 0x0000;
 
    //UART TX
    
    U1MODEbits.BRGH = 0; 
    U1BRG = 64;
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
    while(U1STAbits.UTXBF);
    U1TXREG = x;
}
void invia(char x){
    
    LATBbits.LATB1 = 1; //imposta i pin per l'invio dei dati
    LATBbits.LATB2 = 1;
    sendData(x);   
    T2CONbits.TON = 1; //fa partire il timer
}
void ricevi(){
    LATBbits.LATB1 = 0; //imposta i pin per l'invio dei dati
    LATBbits.LATB2 = 0;
}
char checkDestination(char id)
{
    if((id & 0xf0) == REPARTO_ID){ // controllo dell indirizzo che viene inviato nel primo byte del pacchetto
      return 1;        //true
    }
    else return 0;      //false
}
void divideByType(){
    switch(typeOfMessage){
        case 0x0a: //numeroCoda
            saveString(numeroCoda); 
            break;        
    }
}
void saveString(char *s){
    int y;
    for( y=1;y<indice-1;y++){
        s[y-1] = string[y]; //salva la stringa ricevuta nell'array dato in precedenza
        string[y]='\0';
    }
}



// INTERRUPT

void __ISR(_UART_1_VECTOR, IPL7SRS) UartInterrupt(void)      //interrupt di ricezione
{    
    
    carattere = U1RXREG; //riceve il byte dal registro
    string[indice]=carattere; //inserisce il byte ricevuto in un array
    
    indice++;
    if(indice == 1){
        if(checkDestination(string[0]) == 0){ //controlla se il messaggio non è diretto a me
            indice=0; // se non lo è resetta l'indice
        }
        else{
            typeOfMessage = (char)(string[0] & 0x0f); //prende il tipo del messaggio(prof,materia,durata) dagli ultimi 4 bit del primo byte del pacchetto
        }
    }
    else{
        if(string[indice-1] == '-'){ //quando arriva il byte con il carattere di fine stringa deciso '-'
            divideByType(); // in base al tipo definito nel pacchetto smista nelle diverse variabili
            indice=0;
        }
    }
    
    IFS0bits.U1RXIF = 0;
}
void __ISR(_TIMER_2_VECTOR, IPL7SRS) T2Interrupt(void)      //interrupt di timer2
{    
    //LATDbits.LATD5 ^= 1;
    
    ++count;
    if(count >= 20){ //quando raggiunge il counter setta i pin in ricezione
        ricevi();//è stato fatto cosi perche senza un po di attesa l'invio dei dati non poteva avvenire
        T2CONbits.TON = 0;
        count=0;
    }
    
    IFS0bits.T2IF = 0;                                       //resetto l'interrupt del timer

}
