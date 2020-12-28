/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/27/2020
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

#define F_CPU 8000000UL  //CPU Frequency 8MHz 
#define RS 0             //RS=0
#define EN 1             //EN=1

int i = 0;
int counter = 0;  //OverFlow counter
char alphabet_letters[]= {'A','B', 'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

void lcd_comm (char);
void lcd_data(char);
void lcd_init (void);

interrupt [TIM1_OVF] void timer1_ovf_isr(void)    // Timer1 ISR
{
         
     if(counter == 0 ){

       

      lcd_init();    //initialize LCD      

     //adding data
      for(i=0 ; i<13 ; i++){     //line1
           
           lcd_data(alphabet_letters[i]);
            
      }

      lcd_comm(0xC0);  //go to 2nd line
      lcd_comm(30);    //characters are in middle of LCD

      for(i=13 ; i<26 ; i++){     //line2
           
           lcd_data(alphabet_letters[i]);
            
       }

        
      } 
      
    counter++;   
  	
    TCNT1H = 0xFF;
    TCNT1L = 0xF0;
    
}

void main(void)
{

	TCCR1A = 0x00;
	TCCR1B = 0x01;  // Clock source: System Clock      
    
    // Timer1 initialization 
    TCNT1H = 0xFF;  
    TCNT1L = 0xF0; 
    
    // External Interrupt initialization
    MCUCR =(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR =(0<<ISC2);

	TIMSK = 0x04;   // Enable timer1 overflow interrupt(TOIE1)
    #asm ("sei")    // Enable global interrupts
    
    while(1){ 
     ;   //do nothing
     }
     
 }    

void lcd_comm(char x){

    PORTD = x;
    PORTC &= ~(1<<RS);  //RS=0 command reg.
    PORTC |= 1<<EN;     //Enable Pulse
    delay_ms(30);
    PORTC &= ~(1<<EN);  //Disable Pulse
    
}

void lcd_data(char x){

    PORTD = x;
    PORTC |= 1<<RS;    //RS=1 Data reg.
    PORTC |= 1<<EN;    //Enable Pulse
    delay_ms(30);
    PORTC &= ~(1<<EN); //Disable Pulse
    
}

void lcd_init(void){

    DDRD = 0xFF;      //PORTD initialization
    DDRC = 0x03;      //PORTC initialization
    
    lcd_comm(0x38);   //initialization of 16X2 LCD in 8bit mode 
    lcd_comm(0x06);   //auto Increment cursor
    lcd_comm(0x0D);   //Display ON Cursor ON
    lcd_comm(0x01);   //clear display
    lcd_comm(0x80);   //cursor at home position
    
}
