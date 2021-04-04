/*
 * CFile1.c
 *
 * Created: 07.01.2021 21:04:44
 *  Author: stani
 */ 
#include "HD44780.h"
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 8000000UL
void SET_RS()
{
	PORT_LCD_RS|=(1<<LCD_RS);
}

void CLR_RS()
{
	PORT_LCD_RS&=~(1<<LCD_RS);
}

void SET_E()
{
	PORT_LCD_E|=(1<<LCD_E);
}
void CLR_E()
{
	PORT_LCD_E&=~(1<<LCD_E);
}
void toggle_E()
{
	SET_E();
	_delay_us(10);
	CLR_E();
}
void write_halfbyte(uint8_t dane)
{
	if(dane&(1<<3)) PORT_LCD_D7|=(1<<LCD_D7);
	else PORT_LCD_D7 &=~(1<<LCD_D7);
	if(dane&(1<<2)) PORT_LCD_D6|=(1<<LCD_D6);
	else PORT_LCD_D6 &=~(1<<LCD_D6);
	if(dane&(1<<1)) PORT_LCD_D5|=(1<<LCD_D5);
	else PORT_LCD_D5 &=~(1<<LCD_D5);
	if(dane&(1)) PORT_LCD_D4|=(1<<LCD_D4);
	else PORT_LCD_D4 &=~(1<<LCD_D4);
}

void write_byte(unsigned char dane)
{
	DDR_LCD_D7|=(1<<LCD_D7);
	DDR_LCD_D6|=(1<<LCD_D6);
	DDR_LCD_D5|=(1<<LCD_D5);
	DDR_LCD_D4|=(1<<LCD_D4);
	
	write_halfbyte(dane>>4);
	toggle_E();
	_delay_us(10);
	write_halfbyte(dane);
	toggle_E();
	
	_delay_us(60);
}


void write_command(uint8_t comm)
{
	PORT_LCD_RS&=~(1<<LCD_RS);
	write_byte(comm);
}
void lcd_locate(uint8_t x, uint8_t y)
{
	switch(y)
	{
		case 0:
		write_command(LCD_SET_DDRAM | (LCD_LINE1+x));
		break;
		case 1:
		write_command(LCD_SET_DDRAM | (LCD_LINE2+x));
		break;
	}
}
void write_str(char *str)
{
	//przerzucanie na drugi wersz jesli jest wiecej niz 16 znakow
	PORT_LCD_RS|=(1<<LCD_RS);
	uint8_t t=0;
	if(strlen(str)>16)
	{
		while(*(str+t)&&t<16)
		{
			 write_byte(*(str+t));
			 t++;
		}
		lcd_locate(0,1);
		PORT_LCD_RS|=(1<<LCD_RS);
		while(*(str+t)&&t<32)
		{
			write_byte(*(str+t));
			t++;
		}
	}
	else
	while(*str) write_byte(*str++);
}

void write_int(unsigned int num)
{
	PORT_LCD_RS|=(1<<LCD_RS);

	char temp [5];
	itoa(num,temp,10);
	write_str(temp);
}

void clr_screen()
{
	write_command(LCD_CLEAR);
}
void Initialize()
{
	DDR_LCD_RS|=(1<<LCD_RS);
	DDR_LCD_E|=(1<<LCD_E);
	DDR_LCD_D7|=(1<<LCD_D7);
	DDR_LCD_D6|=(1<<LCD_D6);
	DDR_LCD_D5|=(1<<LCD_D5);
	DDR_LCD_D4|=(1<<LCD_D4);
	_delay_ms(15);
	
	CLR_RS();
	
	write_halfbyte(0x03);
	toggle_E();
	_delay_ms(2);
	
	toggle_E();
	_delay_us(64);

	write_halfbyte(0x02);
	toggle_E();
	_delay_ms(2);
	
	
	write_command(LCD_FUNC|LCD_TWO_LINE|LCD_4_BIT|LCD_FONT_5x7);
	write_command(LCD_ONOFF|LCD_DISP_ON|LCD_BLINK_ON);
	write_command(LCD_CLEAR);
	write_command(LCD_ENTRY_MODE|LCD_EM_SHIFT_CURSOR|LCD_EM_RIGHT);
}