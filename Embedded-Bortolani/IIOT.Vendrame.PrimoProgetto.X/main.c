/*
 * File:   main.c
 * Author: Alessandro Vendrame
 *
 * Created on May 4, 2021, 4:38 PM
 */

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2       // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_20        // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1      // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRIPLL          // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (WDT Enabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

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

void delay(unsigned long int n){
    unsigned long int x = 2000;
    while(n--){
        int x;
        for(x = 0; x < 2000; x++);
    }
}



void main()
{
    TRISD = 0x0000;
    
    const unsigned int display[16] = {N0,N1,N2,N3,N4,N5,N6,N7,N8,N9,LA,LB,LC,LD,LE,LF};
    
    while(1)
    {
        int i = 0;
        
        for(i = 0 ; i<16; i++){
            PORTD = display[i];
            delay(1000);
        }
    }
}
