#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <time.h>

#include "lpd8806lib.h"
#include "patterns.h"

uint8_t activePattern;

// TODO move patterns functions to patterns.c

/*
 * main.c
 *
 * Currently contains a sample demonstration, just to prove the LED library is working correctly.
 */
int main(void) {

	SysCtlClockSet(
	SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	srand(time(NULL));
	initLEDStrip();

	activePattern = 4; // init active pattern to blank

	while (1)
		activatePattern(activePattern);
}
