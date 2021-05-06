/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on January 29, 2021, 9:08 AM
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
#define AUX 0x04

void initPic();
void init_LCD();
void init_ADC();
void sendCommand(char cmd);
void sendData(char d);
void write_char(char c);
void write_string(char *str);
char checkKeypad();
int readADC(char channel);
int map(int x, int in_min, int in_max, int out_min, int out_max);
void toString(int valore);
double pow(double x, double n);
void checkPin();

const unsigned char keyPad[] = {1,4,7,'*',2,5,8,0,3,6,9,'#'}; 
const unsigned char number[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
const char numberDisplay[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,0x6D,0x7D,0x07,0x7F,0x6F};
const char pin[4] = {'1','2','3','4'};

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

char pressedButton[] = {};
char oldButton[] = {};

unsigned char colScan = 0;
unsigned char rowScan = 0;
unsigned char keypressed = 99;
char index;
char fronte[12] = "";
char oldFronte[12] = "";
char keyok = 0; //flag di pulsante premuto
int count = 0;
int delayBtn = 0,contDelayButton = 0;
int valore = 0,oldValore = 0;
char inserted = 0;
char n = 0;
int old_val = -1;
int val_ADC = -1;
int P1Value = -1;
char key=-1;
char str[2];
char insertedPin[4];
char pinIndex=0;

void main(void) {
    initPic();
    init_ADC();
    init_LCD();
    
    while(1){
        val_ADC = map(readADC(0),0,1023,0,7);
        
        if(old_val != val_ADC){
            sendCommand(L_CLR);
            sendCommand(L_L1);
            char a = val_ADC + '0';
            write_string("P1-> ");
            sendCommand(L_L1 + 5);
            write_char(a);
            old_val = val_ADC;
        }
        
        key = checkKeypad();
        
        if(keypressed != 99){
            write_char(key);
            key = -1;
        }
        
    }
    
    return;
}

void initPic()
{
    //TRISB = 0x00;
    //TRISD = 0x00;
    TRISE = 0x00;
    INTCON = 0xA0;
    OPTION_REG = 0x05; // prescaler 1:64
    TMR0 = 6;
}

void init_ADC()
{
    TRISA = 0xFF; //utilizzo TRISA perche le porte di AN corrispondono a quelle di TRISA
    ADCON0 = 0x81;
    ADCON1 = 0x8E;
    __delay_us(20);   
}

void init_LCD()
{
    PORTE = PORTE & 0x02;
    PORTE = PORTE & 0x04;
    __delay_ms(20);
    PORTE = PORTE | 0x02;
    sendCommand(L_CFG);
    __delay_ms(5);
    sendCommand(L_CFG);
    __delay_ms(1);
    sendCommand(L_CFG);
    sendCommand(L_ON);
    sendCommand(L_CLR);
    sendCommand(L_CUR);
    sendCommand(L_L1);
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
    TRISD = 0x00;
    PORTE = PORTE | 0x02;
    PORTD = d;
    PORTE = PORTE | 0x04;
    __delay_ms(3);
    PORTE = PORTE & ~0x02;
    __delay_ms(3);
    PORTE = PORTE | 0x02;
}

void write_char(char c)
{
    sendData(c);
}

void write_string(char *str){
    for(int i = 0; str[i] != '\0'; i++) {
        sendData(str[i]);
    }
}

void toString(int valore){
    int i;
    int num =0;
    for (i=0;i<2;i++){
        str[1-i] = '0' + ((valore)%(char)pow(10,1+i)) / (char)pow(10,i);
    }
}

double pow(double x, double n){
    int i;
    double number = 1;
    
    for ( i=0 ; i< n ; i++){
        number *= x;
    }
}

char checkKeypad()
{
    //TRISE = 0x00;
    //PORTE = 0x00;
    TRISD |= 0x0F;
    TRISB = 0x00;

    /*for(colScan = 0; colScan < 3; colScan++)
    {
        PORTB = PORTB | 0x07;                       // porto tutte le colonne a 1
        PORTB &= colMask[colScan];                  //porto a zero la colonna interessata
        for( rowScan = 0; rowScan <4; rowScan++)
        {
            index = (rowScan + (4*colScan));
            fronte[index] = !(PORTD & rowMask[rowScan]);
            if(((fronte[index])&&(!(oldFronte[index]))) || keyok)
            {                          
                keyok = 1; // riga rowScan trovata a massa
                if(((fronte[index])&&(!(oldFronte[index]))) && delayBtn > 1)
                {
                    keypressed = index;
                    delayBtn = 0;
                }
                oldFronte[index] = fronte[index];
            }
        }
    }*/
    return 99;
}



void checkPin(){
    int i=0;
    char sbaglio = 0;
    for(i=0; i < 4; i++){
        if(pin[i]!=insertedPin[i]){
            sbaglio = 1;
        }
    }
    
    if(sbaglio == 1){
        sendCommand(L_L2);
        write_string("CHIUSO");
    }else{
        sendCommand(L_L2);
        write_string("APERTO");
    }
}

void __interrupt() ISR() {
    if(INTCON & 0x04) {
       
        if(keyok) {
            delayBtn ++;
            keyok = 0;
        }
        INTCON = INTCON & ~0x04;
    }
    return;
}
