#ifndef LIGHTS_H_
#define LIGHTS_H

#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 144
#define digitalPin 7

enum class Status
{
	singleColor,
	multiColor
};

enum class Pattern{
	changeColor,
	fadeColor,
	revertFade,
	evenOddFill,
	lightChunks,
	randomFill,
	none
};

class LightShow
{
	private:
		Adafruit_NeoPixel *strip;	//the actual strip
		int delayValue;	// This will can go up a lot for a dramatic drop, or go down when the beats are rising
		uint32_t currentColor;	//the actual RGB value of the current color we are on
		int fadingColorArray[3];	//this will be used to keep track of each RGB value of the current color such as [0, 0, 255], will only be used for fading
		bool fadingOnGoing;	//will be used to determine if fading is in it's first iteration or not
		int currentColorIndex;	//points to which color we are on
		int beatsPerSecond;	//Not used currently
		uint32_t colorArray[7];	//holds every single color
		uint32_t savedColor;	//will be used to store the color before fading originally applies
		Status colorStatus;	//Allows us to know if the strip is currently one color or many
		Pattern currentPattern;	//Allows us to know which pattern is currently playing
		Pattern previousPattern;	//Allows us to know what the previous pattern was so that we don't display the same one again
		int iterationCounter;
	public:
		//constructor
		LightShow();
		//Setters/Getters/One liners
		void setDelay(int val) { delayValue = val; }
		void clearStrip() {strip->clear();}
		void endFading() {fadingOnGoing = false;}
		
		//Function that makes sure the color index doesn't go out of bounds and changes the current color value, no flashing
		void incrementColorCounter();
		//Function that turns on the led strip with a specific but cool pattern
		void initialize();
		//Function that flashes the current color and increments the color index to change the color
		void changeColor();
		//Function that will fade the current color
		void fadeColor();
		//Function that will restore the color of the strip to what it was before the fade applied
		void revertFade();
		//TODO: Function that will fill gradually based on the beat
		void gradualFill();
		//Function that will flash every even or odd LED depending if start is 0 or 1
		void evenOddFill(bool evenOdd);
		//Function that lights up 7 chunks of 15 leds with 6 empty space between, argument is optional to make each chunk a different color
		void lightChunks(int color = 0);
		//Function that will randomly fill through the strip in groups of 3s
		void randomFill();
		//TODO: Function that create a light show using all of our built in functions without using the sound detector
		void automatic();
		//Function that will roll for a new pattern;
		void rollForPattern();
		//Function that combines every pattern together and reacts based on the sound detector, main function, default parameters for other functions to call
		void play(bool evenOdd = false, int color = 0);
};

#endif
