#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "lpd8806lib.h"

/*
 * main.c
 */
int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	initLEDStrip(32);


	int x = 0;
	uint8_t r, g, b;
	while(1)
	{
//		if (x == 0)
//		{
//			r = 127;
//			g = b = 0;
//		} else if (x == 1)
//		{
//			g = 127;
//			r = b = 0;
//		} else
//		{
//			b = 127;
//			r = g = 0;
//		}
//		int i;
//		for(i = 0; i < 32; i++)
//			setRGB(i, r, g, b);

		uint8_t array[99];
//		array[0] = 255;
		int j;
		for (j = 0; j < 96; j += 3)
		{
			array[j] = 128;
			array[j + 1] = 128;
			array[j + 2] = 255;
		}
		array[6] = 255;
		array[8] = 128;
		for (j = 96; j <= 98; j++)
			array[j] = 0;
		showStrip(array, 99);
		x++;
		if (x > 2) x = 0;

		SysCtlDelay(20000000);
	}

}
