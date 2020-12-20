/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/19/2020
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
#include <stdio.h>
#include <delay.h>

int i = 0;
int counter = 0;  //OverFlow counter
int SevenSeg[10] = {0b10111111, 0b10000110, 0b11011011, 0b11001111, 0b1100110, 0b11101101, 0b11111101, 0b10000111, 0b11111111, 0b11101111 }; //Numbers Of 7segment

interrupt [TIM1_OVF] void timer1_ovf_isr(void)    // Timer1 ISR
{
         
     if(counter == 0 ){

       if(PINC.0 == 1){  //Enable Switch

         if(i < 10){
           
           PORTA =  SevenSeg[i];  //Set numbers Of SevenSegment on PORTA  
           
        }else{ 

           i = 0 ;
           PORTA = SevenSeg[i];

         }

         i++;

        }
      } 
      
    counter++;   
     	
    TCNT1H = 0xFF;
    TCNT1L = 0xF0;
    
}

void main(void)
{
    DDRC.0 = 0;  //PORTC.0 initialization
    DDRA = 0xFF; //PORTA initialization


	TCCR1A = 0x00;
	TCCR1B = 0x01;  // Clock source: System Clock      
    
    // Timer/Counter 1 initialization 
    TCNT1H = 0xFF;  
    TCNT1L = 0xF0; 
    
    // External Interrupt initialization
    MCUCR =(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR =(0<<ISC2);

	TIMSK = 0x04;   // Enable timer1 overflow interrupt(TOIE1)
    #asm ("sei")   // Enable global interrupts
    
    while(1){ 
     ;   //do nothing
     }
  
  }   



 


   


