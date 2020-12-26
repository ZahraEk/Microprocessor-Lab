/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/26/2020
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

void lcd_comm (char);
void lcd_data(char);
void lcd_init (void);


void main(void)
{
   
	lcd_init();    //Initialize LCD      
    
	lcd_data('H');  //adding the data
	lcd_data('E');
	lcd_data('L');
	lcd_data('L');
	lcd_data('O');

	lcd_comm(20);  //create space between the two words

	lcd_data('W');
	lcd_data('O');
	lcd_data('R');
	lcd_data('L');
	lcd_data('D');
    lcd_data('!');
 
     
	while(1)
	{
	;  //do nothing	
	}   
    
}

void lcd_comm(char x){

	PORTD = x;
	PORTC &= ~(1<<RS);  //RS=0 command reg.
	PORTC |= 1<<EN;     //Enable Pulse
	delay_ms(20);
	PORTC &= ~(1<<EN);  //Disable Pulse
    
}

void lcd_data(char x){

	PORTD = x;
	PORTC |= 1<<RS;    //RS=1 Data reg.
	PORTC |= 1<<EN;    //Enable Pulse
	delay_ms(20);
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
