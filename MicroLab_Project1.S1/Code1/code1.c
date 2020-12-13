/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : code1
Version : 
Date    : 12/13/2020
Author  : zahra
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
static unsigned int time_count; /*0.5 second counter*/

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void) 
{
    TCNT0 = 56; /*set for 132 us timeout*/
    ++time_count; /*increment 0.5 second counter*/
    if (time_count == 3787)
  {
        PORTC.0 = (PORTC.0 ^ 1); /*complement port bit to blink LED*/
        time_count = 0; /*reset time counter for next 0.5 second*/ 
     }
}

void main (void) {
    DDRC = 0x01; /*set lsb for output*/

    /*set timer 0 prescaler to clk/8*/
    TCCR0=0x02;
    TCNT0=56;
   

    /* unmask Timer 0 overflow interrupt*/
    TIMSK=0x01;

    /* enable interrupts */
    #asm("sei")

    while(1) 
    {
        ; /*do nothing in here */
    }
}

