/*
 * File:   ComunicazioneSeriale_Vendrame.c
 * Author: Alessandro Vendrame
 *
 * Created on January 22, 2021, 9:24 AM
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 32000000
#define L_ON 0x0F
#define L_OFF 0x08
#define L_CLR 0x01
#define L_L1 0x80
#define L_L2 0xC0
#define L_CR 0x0F
#define L_NCR 0x0C
#define L_CFG 0x38
#define L_CUR 0x0E
#define channel 2
#include <xc.h>

//Variabili
const unsigned char rowMask[4]=
{
    0b00001000, // Riga 1
    0b00000100, // Riga 2
    0b00000010, // Riga 3
    0b00000001 // Riga 4
};
const unsigned char colMask[3]=
{
    0b11111110, // Colonna 1 => RB0 a massa
    0b11111101, // Colonna 2 => RB1 a massa
    0b11111011 // Colonna 3 => RB2 a massa
};

const char keyPad[] = {'1','4','7','*','2','5','8','0','3','6','9','#'};
unsigned char colScan = 0;
unsigned char rowScan = 0;
unsigned char keypressed = 0;
char keyok = 0; // flag di pulsante premuto
int count, pwm;
int delayBtn = 0;
int setpointTemperature = 30;
int old_val = -1;
int val_ADC = -1;
char c1,c2,c3,c4, t1, t2;
int temp1;
double volt, temp;
char change = 1;
char receivedMessage;

//Funzioni
void initPic();
void init_Uart();
void initDisplayLCD();
void sendData(char d);
void sendCommand(char cmd);
void write_string(char scritta[]);
void write_char(char c);
void checkKeypad();
void writeToDisplayLCD();
void trasmitData(char c);
void getData();


void main(void) {

    initPic();
    init_Uart();
    initDisplayLCD();
       
    while(1)
    {
       if(count > 50){
          checkKeypad(); 
          count = 0;
       }             
    }
    return;
}

void checkKeypad()
{
    PORTA = 0x00;
    TRISD = 0xFF;
    PORTD = 0xFF;
    
    for (colScan = 0; colScan < 3; colScan++)
    {
        PORTB = PORTB | 0x07; // porto tutte le colonne a 1
        PORTB &= colMask[colScan]; // porto a zero la colonna attuale
        for (rowScan = 0; rowScan < 4; rowScan++)
        {
            if (!(PORTD & rowMask[rowScan]) || keyok) // Riga rowScan trovata a massa
            {
                keyok = 1;
                // rendendolo sensibile al fronte
                if (!(PORTD & rowMask[rowScan]) && delayBtn > 1)
                {
                    keypressed = rowScan +(4*colScan); // numero di pulsante premuto
                    keyok = 0; // E? stato premuto un pulsante
                    delayBtn = 0;
                    
                    //Da mettere controlli per pulsante premuto
                    
                    trasmitData(keyPad[keypressed]);
                    write_char(keyPad[keypressed]);
                }
            }
        }
    }
}

void write_string(char scritta[])
{
    int i = 0;
    while(scritta[i] != '\0')
    {
        sendData(scritta[i]);
        i++;
    }
}
void write_char(char c)
{
    sendData(c);
}

void initPic()
{
    TRISD = 0x00;
    TRISE = 0x00;
    TRISB = 0x00;
    TRISA = 0x00;
    
    INTCON = 0xE4;     // 1010 0000
    PIE1 = 0x22;
    OPTION_REG = 0x06; // prescaler 1:128
    TMR0 = 131;  

}

void initDisplayLCD()
{
    PORTE = 0x00;
    __delay_ms(20);
    PORTE = PORTE | 0x02;
    sendCommand(L_CFG); 
    __delay_ms(5);
    sendCommand(L_CFG); 
    __delay_ms(1);
    sendCommand(L_CFG); 
    sendCommand(L_OFF); 
    sendCommand(L_ON); 
    sendCommand(L_CLR);   
    sendCommand(L_CUR); 
    sendCommand(L_L1); 

}

void sendCommand(char cmd)
{
    PORTE = PORTE | 0x02; 
    PORTD = cmd;
    PORTE = PORTE & ~0x04;
    __delay_ms(3);
    PORTE = PORTE & ~0x02;
    __delay_ms(3);
    PORTE = PORTE | 0x02;
}

void sendData(char d)
{
     PORTE = PORTE | 0x02;
     TRISD = 0x00;
     PORTD = d;
     PORTE = PORTE | 0x04;
    __delay_ms(3);
    PORTE = PORTE & ~0x02;
    __delay_ms(3);
    PORTE = PORTE | 0x02;
}

void init_Uart(){
    long baudRate = _XTAL_FREQ;
    TXSTA |= 0x20; //TXEN = 1
    TRISC &= ~0x40; // RC6 --> Output RC7--> Input 0b1000000
    TRISC |= 0x80;  //RC7
    RCSTA |= 0x80; //SPEN = 1
    RCSTA |= 0x10; //CREN = 1
    SPBRG = (_XTAL_FREQ/(long)(64UL*baudRate))-1;
}

void trasmitData(char c){
    while(!(PIR1 &~0x20));
    TXREG = c;
}

void __interrupt() ISR()
{
    if(INTCON & 0x04) //gestisco chimata da timer0 (T0IF)
    {        
        count++;
        if(keyok)
        {
            delayBtn++;
        }

        INTCON = INTCON & ~0x04;
    }

    if(PIR1 & 0x02) //gestisco chiamata a RCIF --> RICEZIONE
    {
        while(!(PIR1 & ~0x02));
    }
    return;
} 