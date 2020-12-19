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
int segment[10] = {0b10111111, 0b10000110, 0b11011011, 0b11001111, 0b1100110, 0b11101101, 0b11111101, 0b10000111, 0b11111111, 0b11101111 };



void main(void)
{
    DDRC.0 = 0;
    DDRA = 0xFF;
    DDRD = 0x20;
    // initialize the timer counter
    TCNT1 = 0;
   
    // enable compare interrupt A
    TIMSK1 = 0x10;
    // configure mode of operation  with OCR1A
    TCCR1B = 0x02;
    TCCR1A = 0x40;
    #asm ("sei") 
    
    while(1){ 
      if(PINC.0 == 1 ){ 

       for(i=0; i<10 ;i++){   
       PORTA = segment[i];  
        
         
        //if(PINC.0 == 0){
        // PORTA = 0 ;
        //}
       }
       
      }else{
           
          PORTA = 0;
       }
    } 
}



 


   


