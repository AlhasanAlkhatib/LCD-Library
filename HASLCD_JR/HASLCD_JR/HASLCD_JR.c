/*************************************************************************************************
 *  File: HASLCD_JR.c
 *  Copyright (C) 2017 ALHASAN ALKHATIB
 *
 *  date:   Oktober, 2017
 *  Author: ALHASAN ALKHATIB
 *
 *   Description: 16*2 LCD Setup Drive and Control library
 *                for ARM CORTEX-M4 ARM Cortex -M4 TM4C123G (Tiva C kit)
 *                (Source file)
 *************************************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "HASLCD_JR.h"

/////////////////////////////////////////////////////////////////////////////////////
 void has_lcd_switchwrite()
{		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
		HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
		HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //pin0 ve pin4 input
		GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // pin0 ve pin4 pull-up

		unsigned char a=0x2f;
		unsigned char line=1;
		unsigned char column=1;
  while(1)
   {
     if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0)
     {    while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0){}
	      has_lcd_position(line,column);
          has_lcd_sendchar(a);
	      a++;
	      has_lcd_position(line,column);
     }
     if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
     {    while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0){}
          a=0x2f;// '/' itibaren baslar
             if((line==1) && (column==16))
             {
                 column=0;
         	     line=2;
             }
        	 if((line==2) && (column==16))
             {
        		 column=0;
                 line=1;
             }
	      has_lcd_position(line,++column);
     }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_erase()
{
	has_lcd_sendcommand(0x01);
    SysCtlDelay(1000);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_write(uint8_t line , uint8_t column,char str[])
{
	has_lcd_position(line,column);
	int i=0;
	while((str[i])!=0)
	{
		has_lcd_sendchar(str[i]);
	i++;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_sendchar(uint8_t ch)
{
	 GPIOPinWrite(LCDPORT, highpin, ch & 0xf0 );
     GPIOPinWrite(LCDPORT, RS, 0x01);
     GPIOPinWrite(LCDPORT, E, 0x04);
	    SysCtlDelay(10);
     GPIOPinWrite(LCDPORT, E, 0x00);

		SysCtlDelay(50000);

	 GPIOPinWrite(LCDPORT,highpin,( ch & 0x0f)<<4);
     GPIOPinWrite(LCDPORT, RS, 0x01);
     GPIOPinWrite(LCDPORT, E, 0x04);
		SysCtlDelay(10);
     GPIOPinWrite(LCDPORT, E, 0x00);

		SysCtlDelay(50000);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_sendcommand(uint8_t x)
{
	        GPIOPinWrite(LCDPORT, highpin, x & 0xf0 );
	        GPIOPinWrite(LCDPORT, RS, 0x00);
	        GPIOPinWrite(LCDPORT, E, 0x04);
	        SysCtlDelay(50000);
	        GPIOPinWrite(LCDPORT, E, 0x00);

	        SysCtlDelay(50000);

	        GPIOPinWrite(LCDPORT, highpin,( x & 0x0f)<<4);
	        GPIOPinWrite(LCDPORT, RS, 0x00);
	        GPIOPinWrite(LCDPORT, E, 0x04);
	        SysCtlDelay(100);
	        GPIOPinWrite(LCDPORT, E, 0x00);

	        SysCtlDelay(50000);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_position(uint8_t line , uint8_t column)
{
	if(line==1)
	{
		has_lcd_sendcommand(0x80+(column-1));
	}
	else
	{
		has_lcd_sendcommand(0xc0+(column-1));
	}
  SysCtlDelay(100);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void has_lcd_4bitsetup()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(LCDPORT,0x0ff);//make all pin as output pin
          SysCtlDelay(5000000);
          GPIOPinWrite(LCDPORT, RW,  0x00 );
          SysCtlDelay(5000000);
          GPIOPinWrite(LCDPORT, RS,  0x00 );

          GPIOPinWrite(LCDPORT, highpin,  0x30 );
          GPIOPinWrite(LCDPORT, E, 0x04);
          SysCtlDelay(50000);
          GPIOPinWrite(LCDPORT, E, 0x00);

          SysCtlDelay(50000);

          GPIOPinWrite(LCDPORT, highpin,  0x30 );
          GPIOPinWrite(LCDPORT, E, 0x04);
          SysCtlDelay(50000);
          GPIOPinWrite(LCDPORT, E, 0x00);

          SysCtlDelay(50000);

          GPIOPinWrite(LCDPORT,highpin,  0x30 );
          GPIOPinWrite(LCDPORT, E, 0x04);
          SysCtlDelay(50000);
          GPIOPinWrite(LCDPORT, E, 0x00);

          SysCtlDelay(50000);

          GPIOPinWrite(LCDPORT, highpin,  0x20 );
          GPIOPinWrite(LCDPORT, E, 0x04);
          SysCtlDelay(50000);
          GPIOPinWrite(LCDPORT, E, 0x00);

          SysCtlDelay(50000);

          has_lcd_sendcommand(0x28);//4bit,2satir,5*7 pixel
          has_lcd_sendcommand(0x06);//kusor pozisyonu artitt,kaydirma kapali
          has_lcd_sendcommand(0x0c);//Ekran açık, Kursör kapali, Kursör blink kapali

          SysCtlDelay(50000);

}
