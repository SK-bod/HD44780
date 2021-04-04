/*
 * IncFile1.h
 *
 * Created: 07.01.2021 21:05:02
 *  Author: stani
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#ifndef HD44780_H_
#define HD44780_H_

#endif /* INCFILE1_H_ */

//Do zdefiniowania
/////////////////////////////////////////////////////////////////////////
#define DDR_LCD_RS DDRD
#define PORT_LCD_RS PORTD
#define LCD_RS 7

#define DDR_LCD_E DDRD
#define PORT_LCD_E PORTD
#define LCD_E 6

#define DDR_LCD_D7 DDRC
#define PORT_LCD_D7 PORTC
#define LCD_D7 5

#define DDR_LCD_D6 DDRC
#define PORT_LCD_D6 PORTC
#define LCD_D6 4

#define DDR_LCD_D5 DDRC
#define PORT_LCD_D5 PORTC
#define LCD_D5 3

#define DDR_LCD_D4 DDRC
#define PORT_LCD_D4 PORTC
#define LCD_D4 2
//////////////////////////////////////////////////////////////////////////

//INSTRUKCJE
/////////////////////////////////////////////////////////////////////////
#define LCD_CLEAR					0x01
#define LCD_HOME					0x02
#define LCD_ENTRY_MODE				0x04
	#define LCD_EM_SHIFT_CURSOR		    0x00
	#define LCD_EM_SHIFT_DISPLAY	 	0x01
	#define LCD_EM_LEFT		   			0x00
	#define LCD_EM_RIGHT				0x02
#define LCD_ONOFF					0x08
	#define LCD_DISP_ON				    0x04
	#define LCD_CURSOR_ON				0x02
	#define LCD_CURSOR_OFF				0x00
	#define LCD_BLINK_ON				0x01
	#define LCD_BLINK_OFF				0x00
#define LCD_SHIFT					0x10
	#define LCD_SHIFT_DISP				0x08
	#define LCD_SHIFT_CURSOR			0x00
	#define LCD_SHIFT_RIGHT			0x04
	#define LCD_SHIFT_LEFT				0x00
#define LCD_FUNC					0x20
	#define LCD_8_BIT					0x10
	#define LCD_4_BIT					0x00
	#define LCD_TWO_LINE				0x08
	#define LCD_FONT_5x10				0x04
	#define LCD_FONT_5x7				0x00
#define LCD_SET_CGRAM				0x40
#define LCD_SET_DDRAM				0x80
#define LCD_LINE1					0x00
#define LCD_LINE2					0x40
////////////////////////////////////////////////////////////////////////
//Rs=0 =>wpisywanie danych
void toggle_E();

void write_byte(unsigned char dane);

void write_command(uint8_t comm);

void write_str(char *str);

void write_int(unsigned int num);

void clr_screen();

void lcd_locate(uint8_t x, uint8_t y);

void Initialize();
