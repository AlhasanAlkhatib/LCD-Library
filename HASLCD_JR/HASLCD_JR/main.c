/******************************************************************************
 * File: HASLCD_JR.h
 * Copyright (C) 2017 ALHASAN ALKHATIB
 *
 * date:   Oktober, 2017
 * Author: ALHASAN ALKHATIB
 *
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"

#include "HASLCD_JR.h"



int main()
{
	 SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);

     has_lcd_4bitsetup();
     has_lcd_erase();
     has_lcd_write(1,1,"Hello World!");
	 SysCtlDelay(5000000);
	 has_lcd_erase();
     has_lcd_switchwrite();//use SW1 and Sw2 to enter a text


	 while(1)
	 {

	 }
}

