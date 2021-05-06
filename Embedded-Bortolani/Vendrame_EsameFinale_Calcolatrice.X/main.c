/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on January 27, 2021, 2:12 PM
 * 
 * Calcolatrice binario/numerico con KeyPad
 * 
 * [x] Scrivere a lcd i numeri
 * [x] Scrivere a lcd i bit
 * [] Stampare risultato numeri
 * [] Stampare risultato bit
 * [] Inviare il log informativo in seriale
*/

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 16000000
#include <xc.h>

#define L_ON  0x0F
#define L_OFF 0x08
#define L_CLR 0x01
#define L_L1  0x80
#define L_L2  0xC0
#define L_CR  0x0F
#define L_NCR 0x0C
#define L_CFG 0x38
#define L_CUR 0x0E
#define AUX 0x04;

// Dichiarazione funzioni

int readADC(char channel);
void init_LCD();
void Send_Command(char);
void Send_Data(char);
void write_char(char);
void write_string(char *str);
void checkKeypad(void);
void initADC();
void specialChars();
void btnFunc();
void calculate();
void initPic();


const unsigned char keyPad[] = {1,4,7,'*',2,5,8,0,3,6,9,'#'}; 
char special_char[] ={'*','#','='};
const unsigned char number[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
const char numberDisplay[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,0x6D,0x7D,0x07,0x7F,0x6F};

const unsigned char colMask[3] = 
{
    0b11111110,
    0b11111101,
    0b11111011
};
const unsigned char rowMask[4] = 
{
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001
};

//Dichiarazione variabili ausiliarie

unsigned char colScan = 0;
unsigned char rowScan = 0;
unsigned char keypressed = 99;
char keyok = 0; //flag di pulsante premuto
int countButton = 0;
int count = 0;
int valore = 0,oldValore = 0;
char button = 0,oldButton = 0;
char inserted = 0;
char n = 0;
char somma,differenza,and,or;
char value;
char risultato;
char operazione[50];
int index=0;

void main(void) {
    
    //TRISB = 0x00;//imposto PORTB come output
    //TRISD = 0x00;
    
    initPic();
    initADC(); //configura convertitore
    init_LCD();
    Send_Command(L_L1);
    
    while(1)
    {
        valore = readADC(0);//partiamo dal canale AN0
        PORTB = valore; // visualizzo il valore su portB
        PORTD = valore << 8;
        checkKeypad();
        //calculate();
        /*if(oldValore != valore)
        {
            Send_Command(L_L2);
            write_string("Ris:  ");
        }*/
        //PORTD = numberDisplay[keyPad[keypressed]];
    }
    return;
}
void checkKeypad()
{
    TRISB = 0x00;
    TRISD = 0x0F;
    
    for(colScan = 0; colScan < 3; colScan++)
    {
        PORTB = PORTB | 0x07;
        PORTB &= colMask[colScan]; //porto a zero la colonna interessata
        for( rowScan = 0; rowScan < 4; rowScan++)
        {
            if(!(PORTD & rowMask[rowScan]) || keyok)
            {
                keyok = 1;// riga rowScan trovata a massa
                if(!(PORTD & rowMask[rowScan]) && countButton > 1)
                {
                    keypressed = rowScan+(4*colScan);
                    keyok = 0; // è stato premuto un pulsante
                    countButton = 0;
                    btnFunc();
                }
            }
        }
    }
    
    /*if(PORTB & 0x40){
        write_char('=');
        calculate();
    }*/
}
void btnFunc()
{
   if((keyPad[keypressed] == 1) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[1]);
        operazione[index] = number[1];
        index++;
    }
    if((keyPad[keypressed] == 2) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[2]);
        operazione[index] = number[1];
        index++;
    }
    if((keyPad[keypressed] == 3) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[3]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 4) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[4]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 5) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[5]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 6) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[6]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 7) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[7]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 8) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[8]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 9) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[9]);
        operazione[index] = number[1];
        index++;
    }
   if((keyPad[keypressed] == 0) && (inserted == 0))
    {    
        inserted = 1;
        write_char(number[0]);
        operazione[index] = number[1];
        index++;
    }
    specialChars();
}
void specialChars()
{
    if(valore<512)
    {
        if((keyPad[keypressed] == '*') && (inserted == 0))
        {    
            inserted = 1;
            write_char('+');
            operazione[index] = '+';
            index++;
        }
        if((keyPad[keypressed] == '#') && (inserted == 0))
        {
            inserted = 1;
            write_char('-');
            operazione[index] = '-';
            index++;
        }
    }else 
    {
        if((keyPad[keypressed] == '*') && (inserted == 0))
        {    
            inserted = 1;
            write_char('&');
            operazione[index] = '&';
            index++;
        }
        if((keyPad[keypressed] == '#') && (inserted == 0))
        {
            inserted = 1;
            write_char('|');
            operazione[index] = '|';
            index++;
        }
    }
    calculate();
}

void calculate()
{ 
    TRISB = AUX;
    button = 0x40;
    char startCalculation = 0;
    
    if((button == 1) && (oldButton == 0) && (inserted == 0))//controllo strettamente collegato a quello successivo che mi permette di stampare a video il "="
    {
        inserted = 1;
        PORTB = button;
        write_char('=');// =
        startCalculation = 1;
    }
    if(startCalculation) 
    {
        Send_Command(L_L2);
   
        int i;
        char aux;
        char risultato=0;

        for (i = 0; i < index; i++){

            if(operazione[i] != '+' && operazione[i] != '-' && operazione[i] != '&' && operazione[i] != '&')
            {
                if(operazione[i+1] != '+' && operazione[i+1] != '-')
                {
                    aux = operazione[i]*10 + operazione[i+1];
                }else{
                    aux = operazione[i];
                }
            }else{
                if(operazione[i] == '+'){
                    risultato += aux;
                }else if(operazione[i] == '-')
                {
                    risultato -= aux;
                }else if(operazione[i] != '&'){
                    risultato &= aux;
                }else{
                    risultato |= aux;
                }
                aux = 0;
            }
        }

        char risposta = "->"+risultato;

        write_string(risposta);
    }
}

void initADC()
{
    TRISA = 0xFF; //utilizzo TRISA perche le porte di AN corrispondono a quelle di TRISA
    ADCON0 = 0x81;
    ADCON1 = 0x8E;
    __delay_us(20);
    
}
int readADC(char channel)
{
    TRISA = TRISA | 0x04;
    ADCON0 = ADCON0 | (channel << 3);
    //__delay_us(20);
    ADCON0 = ADCON0 | 0x04; //avvio la conversione imponendo GO/DONE
    while(!(ADCON0 & ~0x04)); // --> 0xFB = 0b11111011 oppure si può scrivere ~0x04 --> finche il GO/DONE non torna a 0
    
    return ADRESL +(ADRESH << 8);
}
void init_LCD()
{
    PORTE = PORTE & 0x02;
    PORTE = PORTE & 0x04;
    __delay_ms(20);
    PORTE = PORTE | 0x02;
    Send_Command(L_CFG);
    __delay_ms(5);
    Send_Command(L_CFG);
    __delay_ms(1);
    Send_Command(L_CFG);
    Send_Command(L_ON);
    Send_Command(L_CLR);
    Send_Command(L_CUR);
    Send_Command(L_L1);
}

void Send_Command(char command)
{
    TRISD = 0x00;
    PORTE = PORTE | 0x02; //RE1 0b00000010
    PORTD = command;
    PORTE = PORTE & ~0x04; 
    __delay_ms(3);
    PORTE = PORTE & ~0x02; 
    __delay_ms(3);
    PORTE = PORTE | 0x02;
}

void Send_Data(char data)
{
    TRISD = 0x00;
    PORTE = PORTE | 0x02;
    PORTD = data;
    PORTE  = PORTE | 0x04;
    __delay_ms(3);
     PORTE = PORTE & ~0x02;
    __delay_ms(3);
    PORTE = PORTE | 0x02;    
}
void write_char(char str){
    Send_Data(str);
}
void write_string(char *str){
    for(int i = 0; str[i] != '\0'; i++) {
        Send_Data(str[i]);
    }
}
void initPic()
{
    TRISC = 0x00;
    TRISE = 0x00;
    INTCON = 0xA0;
    OPTION_REG = 0x06;
    TMR0 = 6;
}
void __interrupt() ISR()
{
    if(INTCON & 0x04) //gestisco chimata da timer0 (T0IF)
    {     
        if(inserted == 1)
        {
            count++;
            if(count > 25)
            {
                count = 0;
                inserted = 0;
            }
        }
        if(keyok) 
        {
            countButton++;
        }
        INTCON = INTCON & ~0x04;
    }
    return;
}