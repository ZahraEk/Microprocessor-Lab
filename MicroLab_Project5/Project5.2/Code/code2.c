/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 1/12/2021
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

int counter = 0;
int motorState = 0;
bit i = 0;

int step[4]={0b00001001 , 0b000001010 , 0b00000110 , 0b00000101};


interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{

    counter++;
    if(counter == 20){
     

        if(motorState < 4 && i ==0){

       PORTA =  step[motorState];
       motorState = motorState +1;
       i = 1;           
       
       if(motorState == 4)
        {
         motorState = 0;

        }

    } else if(i == 1){

        PORTA = 0;
        i = 0;     
        
        if(motorState== 4)
        {
         
         motorState = 0;

        }

        }

          counter=0;
        }
    

    TCNT0 = 6;

}


void main(void)
{

DDRA = 0xff;
PORTA = 0x00;

DDRC = 0x00;
PINC = 0x00;



TCCR0 = 0x01;
TCNT0 = 6;
OCR0 = 0x00;

TIMSK = 0x01;  // Enable timer0 overflow interrupt(TOIE0)


while (1)
      {
        if(PINC.2 == 0)
       {
           #asm("sei")      // Global enable interrupts

       }

      }      
      
}