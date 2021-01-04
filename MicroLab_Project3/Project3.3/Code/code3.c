/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/28/2020
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

int ov_counter;
int i = 0;
unsigned int start_edge, end_edge;
unsigned int clocks,period_out;
char frequency[10];

void lcd_comm(char);
void lcd_data(char);
void lcd_init(void);
void lcd_clear(void);
		
interrupt [TIM1_OVF] void timer1_ovf_isr(void){   // Timer1 overflow ISR

     ++ov_counter;
}

interrupt [TIM1_CAPT] void timer1_capt_isr(void){  //Timer1 input capture ISR

      //combine two 8bit capture register into the 16 bit count
      end_edge = 256 * ICR1H + ICR1L + ov_counter * 65536;
      clocks =(unsigned long)end_edge + ((unsigned long)ov_counter *65536) - (unsigned long)start_edge;  
      
      period_out = (clocks/750) ;  //output ms     
      
      ov_counter = 0;   //clear overflow
      start_edge = end_edge;   //save end time to use as start edge
      
      sprintf(frequency,"%d Hz", period_out); 
      lcd_init();    //initialize LCD      

     //adding data
      for(i=0 ; i<6 ; i++){    
           
           lcd_data(frequency[i]);
            
      }

}

void main(void)
{

TCCR1A = 0x00;
TCCR1B = 0xC2; //enable input capture mode / prescaler 8

TIMSK = 0x24;  //unmask timer1 overflow and capture interrupts

#asm("sei")    // Enable global interrupts

while (1)
      {
       ;   //do nothing

      }
}

void lcd_comm(char x){

    PORTB = x;
    PORTA &= ~(1<<RS);  //RS=0 command reg.
    PORTA |= 1<<EN;     //Enable Pulse
    delay_ms(30);
    PORTA &= ~(1<<EN);  //Disable Pulse
    
}

void lcd_data(char x){

    PORTB = x;
    PORTA |= 1<<RS;    //RS=1 Data reg.
    PORTA |= 1<<EN;    //Enable Pulse
    delay_ms(30);
    PORTA &= ~(1<<EN); //Disable Pulse
    
}

void lcd_clear()
{
	lcd_comm(0x01);		/* clear display */
	lcd_comm(0x80);		/* cursor at home position */
}

void lcd_init(void){

    DDRA = 0x03;      //PORTA initialization   
    DDRB = 0xFF;      //PORTB initialization 
    
    lcd_comm(0x38);   //initialization of 16X2 LCD in 8bit mode 
    lcd_comm(0x06);   //auto Increment cursor
    lcd_comm(0x0D);   //Display ON Cursor ON
    lcd_comm(0x01);   //clear display
    lcd_comm(0x80);   //cursor at home position
    
}