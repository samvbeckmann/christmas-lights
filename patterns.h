/*
 * patterns.h
 *
 *  Created on: Dec 2, 2015
 *      Author: Sam
 */

#ifndef PATTERNS_H_
#define PATTERNS_H_

void
	activatePattern(uint8_t selectedPattern),
	Wheel(uint16_t pixel, uint16_t WheelPos),
	simpleChase(int delay, uint8_t currentPattern),
	performChase(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowChase(int delay, uint8_t currentPattern),
	theatreChase(int delay, uint8_t currentPattern),
	performTheatre(uint8_t r, uint8_t g, uint8_t b, int numTimes, int delay, uint8_t currentPattern),
	performRainbowTheatre(int delay, uint8_t currentPattern),
	rainbow(uint8_t cycle, int delay, uint8_t currentPattern),
	pong(int delay, uint8_t currentPattern),
	performPong(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	performRainbowPong(int delay, uint8_t currentPattern),
	accPattern(int delay, uint8_t currentPattern),
	performAccumulator(uint8_t r, uint8_t g, uint8_t b, int delay, uint8_t currentPattern),
	persistantChase(int delay, uint8_t r, uint8_t g, uint8_t b, uint8_t currentPattern),
	americaPattern(int delay, uint8_t currentPattern),
	tulsaPattern(int delay, uint8_t currentPattern),
	runChristmasLights(int delay, uint8_t activePattern),
	runPredefPattern(int delay, uint8_t pattern[][], uint16_t patternLen, uint8_t currentPattern, uint8_t playBells);
	playNote(uint32_t time, uint32_t delay);

#endif /* PATTERNS_H_ */
