#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <time.h>

#include "lpd8806lib.h"
#include "main.h"
#include "patterns.h"

uint8_t activePattern;

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

	activePattern = 3; // init active pattern to blank

	while (1) {
		switch (activePattern) {
		case 0:
			simpleChase(0, 1000000, activePattern);
			break;
		case 1:
			theatreChase(0, 5000000, activePattern);
			break;
		case 2:
			pong(0, 1000000, activePattern);
			break;
		case 3:
			rainbow(0, 100000, activePattern);
			break;
		case 4:
			rainbow(1, 100000, activePattern);
			break;
		case 5:
			staticRainbow();
			break;
		case 6:
			simpleChase(1, 1000000, activePattern);
			break;
		case 7:
			theatreChase(1, 5000000, activePattern);
			break;
		case 8:
			pong(1, 500000, activePattern);
			break;
		case 9:
			// TODO Jingle Bells
			break;
		case 10:
			runChristmasLights(300000, activePattern);
			break;
		case 11:
			runPredefPattern(2000000, fiesta, 30, activePattern, 0);
			break;
		case 12:
			runPredefPattern(10000000, pacman, 52, activePattern, 0);
			break;
		case 13:
			// TODO Custom 1
			break;
		case 14:
			// TODO Custom 2
			break;
		case 15:
			resetStrip();
			break;
		}
	}
}

/*
 * Sets the given pixel to a color based on a 384 position color wheel.
 */
void Wheel(uint16_t pixel, uint16_t WheelPos) {
	char r, g, b;

	switch (WheelPos / 128) {
	case 0:
		r = 127 - WheelPos % 128;   //Red down
		g = WheelPos % 128;      // Green up
		b = 0;                  //blue off
		break;
	case 1:
		g = 127 - WheelPos % 128;  //green down
		b = WheelPos % 128;      //blue up
		r = 0;                  //red off
		break;
	case 2:
		b = 127 - WheelPos % 128;  //blue down
		r = WheelPos % 128;      //red up
		g = 0;                  //green off
		break;
	}

	setRGB(pixel, r, g, b);
}

void simpleChase(uint8_t rainbow, int delay, uint8_t currentPattern) {
	resetStrip();

	if (rainbow)
		performRainbowChase(delay, currentPattern);
	else {
		while (activePattern == currentPattern) {
			performChase(127, 127, 127, delay, currentPattern);
			performChase(127, 0, 0, delay, currentPattern);
			performChase(127, 127, 0, delay, currentPattern);
			performChase(0, 127, 0, delay, currentPattern);
			performChase(0, 127, 127, delay, currentPattern);
			performChase(0, 0, 127, delay, currentPattern);
			performChase(127, 0, 127, delay, currentPattern);
		}
	}
}

void performChase(uint8_t r, uint8_t g, uint8_t b, int delay,
		uint8_t currentPattern) {
	int i;

	for (i = 0; i < 32; i++) {
		if (activePattern != currentPattern)
			return; // stop if pattern was changed.

		setRGB(i, r, g, b);
		showStrip();
		setRGB(i, 0, 0, 0);
		SysCtlDelay(delay);
	}
}

void performRainbowChase(int delay, uint8_t currentPattern) {
	int i;

	for (i = 0; i < 384; i++) {
		if (activePattern != currentPattern)
			return;

		Wheel(i % 32, i);
		showStrip();
		setRGB(i % 32, 0, 0, 0);
		SysCtlDelay(delay);
	}
}

void theatreChase(uint8_t rainbow, int delay, uint8_t currentPattern) {
	if (rainbow)
		performRainbowTheatre(delay, currentPattern);
	else {
		int i;
		for (i = 0; i < 10; i++)
			performTheatre(127, 127, 127, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(127, 0, 0, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(127, 127, 0, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(0, 127, 0, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(0, 127, 127, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(0, 0, 127, delay, currentPattern);
		for (i = 0; i < 10; i++)
			performTheatre(127, 0, 127, delay, currentPattern);
	}
}

void performTheatre(uint8_t r, uint8_t g, uint8_t b, int delay,
		uint8_t currentPattern) {
	int i, j; // TODO not working yet.

	resetStrip();

	for (i = 0; i < 3; i++) {
		if (activePattern != currentPattern)
			return; // stop if pattern was changed.
		for (j = 0; j < 32; j += 3)
			setRGB(i + j, r, g, b);
		showStrip();

		SysCtlDelay(delay);

		for (j = 0; j < 32; j += 3)
			setRGB(i + j, 0, 0, 0);
	}
}

void performRainbowTheatre(int delay, uint8_t currentPattern) {
	int i, j;

	for (i = 0; i < 384; i++) {
		for (i = 0; i < 3; i++) {
			if (activePattern != currentPattern)
				return; // stop if pattern was changed.

			for (j = 0; j < 32; j += 3)
				Wheel(i + j, i);

			showStrip();

			SysCtlDelay(delay);

			for (j = 0; j < 32; j += 3)
				setOff(i + j);
		}
	}
}

void rainbow(uint8_t cycle, int delay, uint8_t currentPattern) {
	uint16_t i, j;

	for (j = 0; j < 384; j++) {
		for (i = 0; i < 32; i++)
			Wheel(i, ((cycle ? (i * 384 / 32) : i) + j) % 384);
		showStrip();
		SysCtlDelay(delay);
	}
}

void staticRainbow() {
	int i;
	for (i = 0; i < 32; i++)
		Wheel(i, i * 12);

	showStrip();
}

void pong(uint8_t rainbow, int delay, uint8_t currentPattern) {
	resetStrip();

	if (rainbow)
		performRainbowPong(delay, currentPattern);
	else {
		performPong(127, 127, 127, delay, currentPattern);
		performPong(127, 0, 0, delay, currentPattern);
		performPong(127, 127, 0, delay, currentPattern);
		performPong(0, 127, 0, delay, currentPattern);
		performPong(0, 127, 127, delay, currentPattern);
		performPong(0, 0, 127, delay, currentPattern);
		performPong(127, 0, 127, delay, currentPattern);
	}
}

void performPong(uint8_t r, uint8_t g, uint8_t b, int delay,
		uint8_t currentPattern) {
	int i;

	for (i = 0; i < 32; i++)
		setRGB(i, 0, 0, 0); // set strip to blank

	for (i = 0; i < 32; i++) {
		if (activePattern != currentPattern)
			return; // stop if pattern was changed.
		setRGB(i, r, g, b);
		showStrip();
		setRGB(i, 0, 0, 0);
		SysCtlDelay(delay);
	}

	for (i = 31; i > 0; i--) {
		if (activePattern != currentPattern)
			return;
		setRGB(i, r, g, b);
		showStrip();
		setRGB(i, 0, 0, 0);
		SysCtlDelay(delay);
	}
}

void performRainbowPong(int delay, uint8_t currentPattern) {
	int i;
	for (i = 0; i < 384 * 31; i++) {
		if (currentPattern != activePattern)
			return;

		Wheel(31 - abs(i % 62 - 31), i % 384);
		showStrip();
		setOff(31 - abs(i % 62 - 31));
		SysCtlDelay(delay);
	}
}

void runChristmasLights(int delay, uint8_t currentPattern) {

	resetStrip();

	uint8_t states[32];

	while (activePattern == currentPattern) {

		int i = rand() % 500;
		if (i < 32 && states[i] == 0)
			states[i]++;

		for (i = 0; i < 32; i++) {
			if (states[i] == 0)
				setOff(i);
			else if (states[i] <= 127) {
				setRGB(i, states[i], states[i], states[i]);
				states[i]++;
			} else {
				setRGB(i, 255 - states[i], 255 - states[i], 255 - states[i]);
				states[i]++;
			}
		}
		showStrip();
		SysCtlDelay(delay);
	}



}

void runPredefPattern(int delay, uint8_t pattern[][96], uint16_t patternLen,
		uint8_t currentPattern, uint8_t playBells) {
	int i, j;

	resetStrip();

	for (i = 0; i < patternLen; i++) {
		if (activePattern != currentPattern)
			return;

		for (j = 0; j < 96; j += 3)
			setRGB(j / 3, pattern[i][j], pattern[i][j + 1], pattern[i][j + 2]);
		showStrip();
		if (playBells) {
			// playNote(i); /* Future support for playing Jingle Bells */
		}
		SysCtlDelay(delay);
	}

}
