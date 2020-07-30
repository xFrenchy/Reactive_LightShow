#include "Lights.h"

LightShow::LightShow(){
	strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
		// Argument 1 = Number of pixels in NeoPixel strip
		// Argument 2 = Arduino pin number (most are valid)
		// Argument 3 = Pixel type flags, add together as needed:
		//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
		//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
	delayValue = 370;	// This will can go up a lot for a dramatic drop, or go down when the beats are rising
	oldColor = 0;
	currentColorIndex = 0;
	iterationCounter = 0;
	beatsPerSecond = 145;
	//this seems messy, I wanted to do a for loop but I wasn't sure how to increment over the color values
	colorArray[0] = strip->Color(0, 0, 255);	//blue
	colorArray[1] = strip->Color(255, 0, 0);	//red
	colorArray[2] = strip->Color(255, 128, 255);	//orange
	colorArray[3] = strip->Color(255, 255, 0);	//yellow
	colorArray[4] = strip->Color(0, 255, 0);	//green
	colorArray[5] = strip->Color(76, 0, 153);	//purple
	colorArray[6] = strip->Color(255, 0, 255);	//pink
}

void LightShow::incrementColorCounter(){
	++currentColorIndex;
	if(currentColorIndex > sizeof(colorArray)/sizeof(colorArray[0])){
		//it went out of bounds, we reset
		currentColorIndex = 0;
	}
}

void LightShow::initalize(){
	strip->begin();
	strip->show(); // Initialize all pixels to 'off'
	//Iterate through every single built in function we have
	for(int i = 0; i < sizeof(colorArray)/sizeof(colorArray[0]); ++i){
		//This for loop will iterate over every single color that we offer
		changeColor();
		delay(delayValue);	//if we don't have a delay, the colors will be too fast
	}
}

void LightShow::changeColor(){
	strip->fill(colorArray[currentColorIndex], 0, LED_COUNT);	//color, starting led, ending led
    strip->show();
	incrementColorCounter();
}


void LightShow::fadeColor(int amount){
	//DO NOT mess with brightness, setBrightness looses value of it's previous brightness and the more you call it, the dimmer it gets
}
