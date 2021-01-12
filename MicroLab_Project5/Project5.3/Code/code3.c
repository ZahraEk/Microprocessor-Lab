/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 1/13/2021
Author  : zahra
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>

bit i = 0;
int step[4] = {0b00001001 , 0b000001010 , 0b00000110 , 0b00000101};
int motorState = 0;
int counter =0;
int reverse;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{


    TCNT0=6;

    PORTA = step[motorState];

    if(reverse > 0) {

        if(motorState < 3) {  

            ++motorState; 
            
        } else {     

            motorState = 0;
        }   

    } else {  

        if(motorState > 0) {  

            --motorState;

        } else {    

            motorState = 3;
        }
    }


}

void main(void)
{


motorState = 0;
reverse = 1;

DDRA=0xff;
PORTA=0x00;

DDRC=0x00;
PORTC=0x00;


TCCR0 = 0x03;
TCNT0 = 0x00;
OCR0 = 0x00;

TIMSK = 0x01;


#asm("sei")

while (1)
      {
          if(PINC.2 == 0) {   
          
           reverse = 0;

        }else{   

            reverse = 1;
        }

      }
}