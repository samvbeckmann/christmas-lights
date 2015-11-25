// #include "Energia.h"
#include "lpd8806lib.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


/*
 * This library is not particulary robust at the moment, and it requires the user to construct their own buffers.
 * However, for some reason there is a problem if I attempt to consstruct the buffer here.
 * Feel free to PR this repository if you find a way to hold the buffer in here properly, as it will make the library
 * more robust, and all around easier to use.
 * - Sam Beckmann (@samvbeckmann) 11/24/15
 */

void initLEDStrip(uint16_t inNumLEDs)
{
	// Prep the GPIO for transmitting.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Send an empty byte to clear any buffer, prepare the strip to recieve information.
	uint8_t simpleArray[1] = {0};
	showStrip(simpleArray, 1);
}

void showStrip(uint8_t buffer[], uint16_t bufferLen)
{
	// Step through the passed buffer, pushing the whole thing to the strip
	uint16_t i;
	for (i = 0; i < bufferLen; i++) {
		uint8_t aByte = buffer[i];

		// MSB first
		uint8_t b;
		for (b = 7;; b--) {
			GPIOPinWrite( GPIO_PORTB_BASE, DATA_PIN, (aByte >> b));    // faster

			GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, CLOCK_PIN);  // clock high
			GPIOPinWrite( GPIO_PORTB_BASE, CLOCK_PIN, 0);  // clock low

			if (b == 0)
				break;
		}
	}

}

// Valid color ranges: 0x0...0x7f
//uint8_t * setRGB(uint8_t buffer[], uint16_t idx, uint8_t r, uint8_t g, uint8_t b) {
//	uint16_t offset = idx * 3;
//	buffer[offset] = (b | 0x80);
//	buffer[offset + 1] = (r | 0x80);
//	buffer[offset + 2] = (g | 0x80);
//	return buffer;
//}
