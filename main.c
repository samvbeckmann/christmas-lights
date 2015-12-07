#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

#include "lpd8806lib.h"
#include "patterns.h"

uint8_t activePattern;

void decodeMatrixInput();

/*
 * Prvoides initialization and the primary loop of the program.
 */

int main(void) {

	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
	IntMasterEnable();

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, 0, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntRegister(GPIO_PORTC_BASE, decodeMatrixInput);
	GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_FALLING_EDGE);
	GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, 0);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);

	srand(time(NULL));

	initLEDStrip();

	activePattern = 15; // init active pattern to blank

	while (1)
		activatePattern(activePattern);
}

void decodeMatrixInput() {
	SysCtlDelay(1000000); // debounce wait
	uint32_t input = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	if ((input & 0xF0) != 0xF0) // try to decode if something is pushed.
		{
			int i, row = -1, col = -1;
			for (i = 1; i < 5; i++) // get row
			{
				if (!(input & (8 << i)))
					row = i - 1;
			}

			for(i = 0; i < 4; i++) // get col
			{
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, 4 << i);
				if (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7) & (16 << row))
				{
					col = i;
					break;
				}
			}

			if (col != -1 && row != -1)
				activePattern = row * 4 + col; // get the char of the button.
		}

	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, 0);

	GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	SysCtlDelay(1000000); // wait to allow button to be lifted
}
