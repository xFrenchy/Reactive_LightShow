#ifndef LIGHTS_H_
#define LIGHTS_H

#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 144
#define digitalPin 7

enum class Status
{
	fade,
	drop
};

class LightShow
{
	private:
		Adafruit_NeoPixel *strip;
		int delayValue;	// This will can go up a lot for a dramatic drop, or go down when the beats are rising
		uint32_t oldColor;
		int currentColorIndex;
		int iterationCounter;
		int beatsPerSecond;
		uint32_t colorArray[7];
		
	public:
		//constructor
		LightShow();
		//Setters
		void setDelay(int val) { delayValue = val; }
		//Function that makes sure the color index doesn't go out of bounds
		void incrementColorCounter();
		//Function that turns on the led strip with a specific but cool pattern
		void initalize();
		//Function that changes the current color to a new one and increments the color index
		void changeColor();
		//Function that will fade the current color by a certain amount
		void fadeColor(int amount);
		//Function that will raise the current color by a certain amount
		void raiseColor(int amount);
		//Function that will fill gradually based on the beat
		void gradualFill();
		//Function that will flash every even LED and then every ODD for a specific amount of times
		void evenOddFill(int amount);
		//Function that create a light show using all of our built in functions without using the sound detector
		void automatic();
};

#endif
