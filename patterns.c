#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "lpd8806lib.h"
#include "patterns.h"
#include "predefPatterns.h"

extern uint8_t activePattern;
uint8_t note;
uint8_t length;

void activatePattern(uint8_t selectedPattern) {
	resetStrip();

	switch (selectedPattern) {
	case 0:
		simpleChase(1000000, selectedPattern);
		break;
	case 1:
		theatreChase(2000000, selectedPattern);
		break;
	case 2:
		pong(1000000, selectedPattern);
		break;
	case 3:
		rainbow(0, 100000, selectedPattern);
		break;
	case 4:
		rainbow(1, 100000, selectedPattern);
		break;
	case 5:
		accPattern(500000, selectedPattern);
		break;
	case 6:
		performRainbowChase(1000000, selectedPattern);
		break;
	case 7:
		performRainbowTheatre(2000000, selectedPattern);
		break;
	case 8:
		performRainbowPong(500000, selectedPattern);
		break;
	case 9:
		runPredefPattern(50000, jingle, 51, selectedPattern, 1);
		break;
	case 10:
		runChristmasLights(300000, selectedPattern);
		break;
	case 11:
		runPredefPattern(2000000, fiesta, 30, selectedPattern, 0);
		break;
	case 12:
		runPredefPattern(10000000, pacman, 52, selectedPattern, 0);
		break;
	case 13:
		americaPattern(2000000, selectedPattern);
		break;
	case 14:
		tulsaPattern(1000000, selectedPattern);
		break;
	case 15:
		resetStrip();
		break;
	}
}

/**
 * Utility Function:
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

/**
 * Driver function for the simpleChase pattern.
 * Peformeds colored simple chases until the input changes.
 */
void simpleChase(int delay, uint8_t currentPattern) {
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

/**
 * Performs one simple chase with the given color.
 */
void performChase(uint8_t r, uint8_t g, uint8_t b, int delay,
		uint8_t currentPattern) {
	int i;

	for (i = 0; i < 32; i++) {
		if (activePattern != currentPattern)
			return;

		uint32_t prev = getPixelColor(i);
		setRGB(i, r, g, b);
		showStrip();
		setRGBCompact(i, prev);
		SysCtlDelay(delay);
	}
}

/**
 * Performs a rainbowChase until the input pattern has changed.
 */
void performRainbowChase(int delay, uint8_t currentPattern) {
	int i = 0;

	while (1) {
		if (activePattern != currentPattern)
			return;

		uint32_t prev = getPixelColor(i % 32);
		Wheel(i % 32, i);
		showStrip();
		setRGBCompact(i % 32, prev);
		SysCtlDelay(delay);
		i = (i + 1) % 384;
	}
}

/**
 * Driver function for theatre chase.
 * Performs theatre chases until the input changes
 */
void theatreChase(int delay, uint8_t currentPattern) {
	while (activePattern == currentPattern) {
		performTheatre(127, 127, 127, 10, delay, currentPattern);
		performTheatre(127, 0, 0, 10, delay, currentPattern);
		performTheatre(127, 127, 0, 10, delay, currentPattern);
		performTheatre(0, 127, 0, 10, delay, currentPattern);
		performTheatre(0, 127, 127, 10, delay, currentPattern);
		performTheatre(0, 0, 127, 10, delay, currentPattern);
		performTheatre(127, 0, 127, 10, delay, currentPattern);
	}
}

/**
 * Performs a single color theatre chase a specified number of times.
 */
void performTheatre(uint8_t r, uint8_t g, uint8_t b, int numTimes, int delay,
		uint8_t currentPattern) {
	int i, j, k;

	for (k = 0; k < numTimes; k++) {
		for (i = 0; i < 3; i++) {
			if (activePattern != currentPattern)
				return;

			uint32_t prev;
			for (j = 0; j < 32; j += 3) {
				prev = getPixelColor(i + j);
				setRGB(i + j, r, g, b);
			}
			showStrip();
			for (j = 0; j < 32; j += 3)
				setRGBCompact(i + j, prev);

			SysCtlDelay(delay);
		}
	}
}

/**
 * Performs a continous theatre chase through the rainbow.
 */
void performRainbowTheatre(int delay, uint8_t currentPattern) {
	int i, j, k = 0;

	while (1) {
		for (i = 0; i < 3; i++) {
			if (activePattern != currentPattern)
				return;
			uint32_t prev;
			for (j = 0; j < 32; j += 3) {
				prev = getPixelColor(i + j);
				Wheel(i + j, k);
			}
			showStrip();
			for (j = 0; j < 32; j += 3)
				setRGBCompact(i + j, prev);
			SysCtlDelay(delay);
		}
		k += 2;
		k %= 384;
	}
}

/**
 * Performs rainbow effects on strip.
 * Different colors per pixel if cycle is true.
 */
void rainbow(uint8_t cycle, int delay, uint8_t currentPattern) {
	uint16_t i, j = 0;

	while(currentPattern == activePattern) {
		for (i = 0; i < 32; i++)
			Wheel(i, ((cycle ? (i * 384 / 32) : i) + j) % 384);
		showStrip();
		SysCtlDelay(delay);
		j = (j + 1) % 384;
	}
}

void accPattern(int delay, uint8_t currentPattern) {
	while (currentPattern == activePattern) {
		performAccumulator(127, 127, 127, delay, currentPattern);
		performAccumulator(127, 0, 0, delay, currentPattern);
		performAccumulator(127, 127, 0, delay, currentPattern);
		performAccumulator(0, 127, 0, delay, currentPattern);
		performAccumulator(0, 127, 127, delay, currentPattern);
		performAccumulator(0, 0, 127, delay, currentPattern);
		performAccumulator(127, 0, 127, delay, currentPattern);
	}
}

void performAccumulator(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern) {
	int i, j;
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 32 - i; j++){
			if (currentPattern != activePattern)
				return;
			uint32_t prev = getPixelColor(j);
			setRGB(j, r, g, b);
			showStrip();
			if (j < 31 - i)
				setRGBCompact(j, prev);
			SysCtlDelay(delay);
		}
	}
}

/**
 * Driver function for pong.
 * Runs pong continuously until a new input.
 */
void pong(int delay, uint8_t currentPattern) {
	while(currentPattern == activePattern) {
		performPong(127, 127, 127, delay, currentPattern);
		performPong(127, 0, 0, delay, currentPattern);
		performPong(127, 127, 0, delay, currentPattern);
		performPong(0, 127, 0, delay, currentPattern);
		performPong(0, 127, 127, delay, currentPattern);
		performPong(0, 0, 127, delay, currentPattern);
		performPong(127, 0, 127, delay, currentPattern);
	}
}

/**
 * Performs a single pong trial with the given color.
 */
void performPong(uint8_t r, uint8_t g, uint8_t b, int delay,
		uint8_t currentPattern) {
	int i;
	for (i = 0; i < 62; i++) {
		if (activePattern != currentPattern)
			return;
		uint32_t prev = getPixelColor(31 - abs(i - 31));
		setRGB(31 - abs(i - 31), r, g, b);
		showStrip();
		setRGBCompact(31 - abs(i - 31), prev);
		SysCtlDelay(delay);
	}
}

/**
 * Indefinitely displays pong with a rainbow ball.
 */
void performRainbowPong(int delay, uint8_t currentPattern) {
	int i = 0;
	while (currentPattern == activePattern) {
		Wheel(31 - abs(i % 62 - 31), i % 384);
		showStrip();
		setOff(31 - abs(i % 62 - 31));
		SysCtlDelay(delay);
		i = (i + 1) % 11904;
	}
}

/**
 * Like a single simple chase, but doesn't each pixel to a previous color.
 */
void persistantChase(int delay, uint8_t r, uint8_t g, uint8_t b, uint8_t currentPattern) {
	int i;
	for (i = 0; i < 32; i++) {
		if (currentPattern != activePattern)
			return;
		setRGB(i, r, g, b);
		showStrip();
		SysCtlDelay(delay);
	}
}

/**
 * Does a combined Red, White, and Blue theatre chase.
 */
void americaPattern(int delay, uint8_t currentPattern) {
	int i, j;

	while(1) {
		for(i = 0; i < 3; i++) {
			if(currentPattern != activePattern)
				return;
			for(j = 0; j < 32; j+=3) {
				setRGB(i+j, 127, 0, 0);
				setRGB((i+j+1) % 33, 127, 127, 127);
				setRGB((i+j+2) % 33, 0, 0, 127);
			}
			showStrip();
			SysCtlDelay(delay);
		}
	}
}

/**
 * Repeats a gold, then blue persistant fill.
 */
void tulsaPattern(int delay, uint8_t currentPattern) {
	while(currentPattern == activePattern) {
		persistantChase(delay, 127, 40, 0, currentPattern);
		persistantChase(delay, 0, 0, 127, currentPattern);
	}
}


/**
 * Performs a softly pulsing snowflake pattern.
 */
void runChristmasLights(int delay, uint8_t currentPattern) {
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

/**
 * Runs a pattern that has been predefined and saved in memory.
 */
void runPredefPattern(int delay, uint8_t pattern[][96], uint16_t patternLen,
		uint8_t currentPattern, uint8_t playBells) {
	int i, j;

	for (i = 0; i < patternLen; i++) {
		if (activePattern != currentPattern)
			return;

		for (j = 0; j < 96; j += 3)
			setRGB(j / 3, pattern[i][j], pattern[i][j + 1], pattern[i][j + 2]);
		showStrip();
		if (playBells) {
			note = notes[2*i];
			length = notes[2*i + 1];
			playNote(length, note); /* Future support for playing Jingle Bells */
		}
		SysCtlDelay(delay);
	}
}

void playNote(uint32_t time, uint32_t delay) {
	int totalTime = 0;
	while(totalTime < time) {
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
		SysCtlDelay(SysCtlClockGet()/delay);
		totalTime += SysCtlClockGet()/delay;
	}
}
