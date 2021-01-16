/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on December 29, 2020, 9:24 AM
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

//Funzioni
void initPic();
void initDisplayLCD();
void init_ADC();
void sendData(char d);
void sendCommand(char cmd);
void write_string(char scritta[]);
void write_char(char c);
int read_ADC(char ch);
void checkKeypad();
void manageTemperature(int t1, int t2);
void writeToDisplayLCD();
void main(void) {

    initPic();
    init_ADC();
    initDisplayLCD();
    while(1)
    {
        if(count > 100) 
        {
            checkKeypad();
            count = 0;
        }
        temp1 = getRealTemperature();
        manageTemperature((temp1),setpointTemperature * 100);
        if((int)(temp1/100) == setpointTemperature && change)
        {
            c1 = ((temp1/1000)%10) + '0';
            c2 = ((temp1/100)%10) + '0';
            c3 = ((temp1/10)%10) + '0';
            c4 = ((temp1/1)%10) + '0';
            sendCommand(L_CLR);
            char tempString[] = "Temp: ";
            write_string(tempString);
            write_char(c1);            
            write_char(c2);
            //write_char('.');
            //write_char(c3);
            //write_char(c4);
            write_char(0xDF);
            write_char('C');
            
            sendCommand(L_L2);
            char setPointString[] = "Set Point: ";
            t1 = setpointTemperature/10 + '0';
            t2 = setpointTemperature%10 + '0';
            write_string(setPointString);
            write_char(t1);            
            write_char(t2);
            write_char(0xDF);
            write_char('C');
            
            change = 0;
        }   
    }
    return;
}
int getRealTemperature()
{
    val_ADC = read_ADC(channel);
    volt = val_ADC*4.88281; // Convert it into the voltage 
    temp = volt/10.0;  // Getting the temperature values 
    temp1 = temp*100;

    return temp1;
}
void manageTemperature(int t1, int t2)
{
    TRISC = TRISC & ~0x20;
    if(t1 > t2)
    {
        PORTC = PORTC & ~0x20;
    }else{ PORTC = PORTC | 0x20;}
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
                    
                    if(keypressed == 3) // premo *
                    {
                        setpointTemperature++;
                        change = 1;
                    } else if(keypressed == 11) // premo #
                    {
                        setpointTemperature--;
                        change = 1;
                    }
                }
            }
        }
    }
}
int read_ADC(char ch)
{
    TRISD = 0x00;
    TRISA = TRISA | 0x04; //RA2
    ADCON0 = ADCON0 | (ch << 3);
    ADCON0 = ADCON0 | 0x04;
    while(!(ADCON0&~0x04)); // controllo che GO/DONE ritorni a 0
    return ADRESL + (ADRESH << 8);
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
void init_ADC()
{
    TRISA = TRISA | 0x04;
    ADCON0 = 0x91; //10010001
    ADCON1 = 0x8A;
    __delay_us(20);
}
void initPic()
{
    TRISD = 0x00;
    TRISE = 0x00;
    TRISB = 0x00;
    TRISA = 0x00;
    
    INTCON = 0xA0;
    OPTION_REG = 0x02; // prescaler 1:8
    TMR0 = 6;  

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
     PORTD = d;
     PORTE = PORTE | 0x04;
    __delay_ms(3);
    PORTE = PORTE & ~0x02;
    __delay_ms(3);
    PORTE = PORTE | 0x02;
}

void __interrupt() ISR()
{
    if(INTCON & 0x04) //gestisco chimata da timer0 (T0IF)
    {        
        count++;
        pwm++;
        if(keyok)
        {
            delayBtn++;
        }

        INTCON = INTCON & ~0x04;
    }
    return;
} 