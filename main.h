/*
 * main.h
 *
 *  Created on: Nov 26, 2015
 *      Author: Sam
 */

#ifndef CHRISTMAS_LIGHTS_MAIN_H
#define CHRISTMAS_LIGHTS_MAIN_H

void
	Wheel(uint16_t pixel, uint16_t WheelPos),
	simpleChase(uint8_t rainbow, int delay, uint8_t currentPattern),
	performChase(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowChase(int delay, uint8_t currentPattern),
	theatreChase(uint8_t rainbow, int delay, uint8_t currentPattern),
	performTheatre(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowTheatre(int delay, uint8_t currentPattern),
	rainbow(uint8_t cycle, int delay, uint8_t currentPattern),
	staticRainbow(void),
	pong(uint8_t rainbow, int delay, uint8_t currentPattern),
	performPong(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowPong(int delay, uint8_t currentPattern),
	persistantChase(int delay, uint8_t r, uint8_t g, uint8_t b, uint8_t currentPattern),
	america(int delay, uint8_t currentPattern),
	tulsaPattern(int delay, uint8_t currentPattern),
	runChristmasLights(int delay, uint8_t activePattern),
	runPredefPattern(int delay, uint8_t pattern[][], uint16_t patternLen, uint8_t currentPattern, uint8_t playBells);

int main(void);

#endif /* MAIN_H_ */