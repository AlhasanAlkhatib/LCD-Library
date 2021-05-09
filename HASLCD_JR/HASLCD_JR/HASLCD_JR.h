/******************************************************************************
 * File: HASLCD_JR.h
 * Copyright (C) 2017 ALHASAN ALKHATIB
 *
 * date:   Oktober, 2017
 * Author: ALHASAN ALKHATIB
 *
 * Description: 16*2 LCD Setup Drive and Control library
 *              for ARM CORTEX-M4 ARM Cortex -M4 TM4C123G (Tiva C kit)
 *              (Header file)
 *****************************************************************************/

#ifndef HASLCD_JR_H_
#define HASLCD_JR_H_


/******************************************************************************************
 *the following are value that will use to setup and drive LCD dispaly
 *RS in LCD board is connected to pb0 in Tiva C kit
 *RW in LCD board is connected to pb1 in Tiva C kit
 *E in LCD board is connected to pb2 in Tiva C kit
 *D4 D5 D6 D7 in LCD board are connected to PB4 PB5 PB6 PB7 in the order
 *****************************************************************************************/
#define RS              GPIO_PIN_0 // RS
#define RW              GPIO_PIN_1// RW
#define E               GPIO_PIN_2// E
#define LCDPORT         GPIO_PORTB_BASE//Represents PORTB
#define highpin         GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 // D4 D5 D6 D7



/******************************************************************************************
*Function:has_lcd_4bitsetup
*
*Description:
*  this function is used to make all pin as output pin, Enable Peripheral of GPIO_portB
*  Setup LCD to Write with 4pin 1 line and 5*7 pixel
*
*Parameteres:
*  void
*
*Return:
*  void
 *****************************************************************************************/
void has_lcd_4bitsetup();


/******************************************************************************************
*Function:has_lcd_erase
*
*Description:
*  this function is used to erase the characters was appeared in LCD Display
*
*Parameteres:
*  void
*
*Return:
*  void
 *****************************************************************************************/
void has_lcd_erase();


/******************************************************************************************
*Function:has_lcd_sendchar
*
*Description:
*  this function is used to Send a char to appeard a char by setting E pin to 1
*
*Parameteres:
*  uint8_t ch
*
*Return:
*  void
 *****************************************************************************************/
void has_lcd_sendchar(uint8_t ch);


/******************************************************************************************
*Function:has_lcd_sedcommand
*
*Description:
*  this function is used to Send a command by clearing E pin
*
*Parameteres:
*  uint8_t x
*
*Return:
*  void
 *****************************************************************************************/
void has_lcd_sendcommand(uint8_t x);


/******************************************************************************************
*Function:has_lcd_write
*
*Description:
*   this function is used to write an array of charecters in spercific line and column
*
*Parameteres:
*   uint8_t line , uint8_t column , char str[]
*
*Return:
*   void
 *****************************************************************************************/
void has_lcd_write(uint8_t line , uint8_t column,char str[]);


/******************************************************************************************
*Function:has_lcd_position
*
*Description:
*   this function is used to send the cursor to specific line and column
*
*Parameteres:
*   uint8_t line , uint8_t column
*
*Return:
*   void
******************************************************************************************/
void has_lcd_position(uint8_t line , uint8_t column);


/******************************************************************************************
*Function:has_lcd_switchwrite
*
*Description:
*   this function is allowing to use thw SW1 and SW2 in Tiva kit to enter charecters
*
*Parameteres:
*   void
*
*Return:
*   void
******************************************************************************************/
void has_lcd_switchwrite();



#endif /* HASLCD_JR_H_*/
