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
	fadingOnGoing = false;
	currentColorIndex = 0;
	beatsPerSecond = 145;
	//this seems messy, I wanted to do a for loop but I wasn't sure how to increment over the color values
	colorArray[0] = strip->Color(0, 0, 255);	//blue
	colorArray[1] = strip->Color(255, 0, 0);	//red
	colorArray[2] = strip->Color(255, 128, 0);	//orange/yellow
	// colorArray[3] = strip->Color(255, 255, 51);	//yellow, too bright and looks white instead of yellow
	colorArray[3] = strip->Color(0, 255, 0);	//green
	colorArray[4] = strip->Color(102, 255, 255);	//teal
	colorArray[5] = strip->Color(51, 0, 102);	//purple
	colorArray[6] = strip->Color(255, 0, 255);	//pink
	currentColor = colorArray[currentColorIndex];
	savedColor = 0;
	colorStatus = Status::singleColor;
	currentPattern = Pattern::none;
	previousPattern = currentPattern;
	iterationCounter = random(7-35);	//patterns will execute for a random amounts of times in that range
}

void LightShow::incrementColorCounter(){
	++currentColorIndex;
	if(currentColorIndex > sizeof(colorArray)/sizeof(colorArray[0])){
		//it went out of bounds, we reset
		currentColorIndex = 0;
		currentColor = colorArray[currentColorIndex];
	}
	else{
		currentColor = colorArray[currentColorIndex];
	}
}

void LightShow::initialize(){
	strip->setBrightness(50);	//0-255, this value should not go up or down throughout the code
	strip->begin();
	strip->show(); // Initialize all pixels to 'off'
	//Iterate through every single built in function we have
	for(long i = 0; i < 65536; i += 255){	//65536 is the max number for hue, it ranges from 0-65535
		strip->fill(strip->ColorHSV(i, 255, 255), 0, LED_COUNT);	//hue color, saturation(0-255), brightness(0-255)
		strip->show();
	}
}

void LightShow::changeColor(){
	strip->fill(currentColor, 0, LED_COUNT);	//color, starting led, ending led
    strip->show();
	incrementColorCounter();	//this will change the color
	colorStatus = Status::singleColor;
}

//Would love to find a better way to do this
void LightShow::fadeColor(){
	//DO NOT mess with brightness, setBrightness looses value of it's previous brightness and the more you call it, the dimmer it gets
	
	//Fading only works if the strip is full of a singular color, we will have to check if this is the case, if not, quickly fill it with a single color with changeColor()
	if(colorStatus != Status::singleColor){
		changeColor();
	}
	
	if(fadingOnGoing == false){	//first time fade is being applied
		fadingOnGoing = true;
		savedColor = currentColor;	//save the color if we want to restore it
		switch(currentColorIndex){
			case 0:	//(0, 0, 255) blue
				fadingColorArray[0] = 0;
				fadingColorArray[1] = 0;
				fadingColorArray[2] = 255;
				break;
			case 1:	//(255, 0, 0)
				fadingColorArray[0] = 255;
				fadingColorArray[1] = 0;
				fadingColorArray[2] = 0;
				break;
			case 2:	//(255, 128, 0)
				fadingColorArray[0] = 255;
				fadingColorArray[1] = 128;
				fadingColorArray[2] = 0;
				break;
			case 3:	//(0, 255, 0)
				fadingColorArray[0] = 0;
				fadingColorArray[1] = 255;
				fadingColorArray[2] = 0;
				break;
			case 4:	//(102, 255, 255)
				fadingColorArray[0] = 102;
				fadingColorArray[1] = 255;
				fadingColorArray[2] = 255;
				break;
			case 5:	////(51, 0, 102)
				fadingColorArray[0] = 51;
				fadingColorArray[1] = 0;
				fadingColorArray[2] = 102;
				break;
			case 6://(255, 0, 255)
				fadingColorArray[0] = 255;
				fadingColorArray[1] = 0;
				fadingColorArray[2] = 255;
				break;
		}
	}
	//Each color has to be decremented a different way, but there has to be a method to generalize this
	switch(currentColorIndex){
		case 0:	//(0, 0, 255) blue
			if(fadingColorArray[2] > 15){
				fadingColorArray[2] -= 5;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 1:	//(255, 0, 0)
			if(fadingColorArray[0] > 15){
				fadingColorArray[0] -= 5;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 2:	//(255, 128, 0)
			if(fadingColorArray[0] > 15 && fadingColorArray[1] > 15){
				fadingColorArray[0] -= 10;
				fadingColorArray[1] -= 5;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 3:	//(0, 255, 0)
			if(fadingColorArray[1] > 15){
				fadingColorArray[1] -= 5;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 4:	//(102, 255, 255)
			if(fadingColorArray[0] > 15 && fadingColorArray[1] > 15 && fadingColorArray[2] > 15){
				fadingColorArray[0] -= 4;
				fadingColorArray[1] -= 10;
				fadingColorArray[2] -= 10;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 5:	//(51, 0, 102)
			if(fadingColorArray[0] > 7 && fadingColorArray[2] > 15){
				fadingColorArray[0] -= 1;
				fadingColorArray[2] -= 2;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
		case 6:	//(255, 0, 255)
			if(fadingColorArray[0] > 15 && fadingColorArray[2] > 15){
				fadingColorArray[0] -= 5;
				fadingColorArray[2] -= 5;
				currentColor = strip->Color(fadingColorArray[0], fadingColorArray[1], fadingColorArray[2]);
			}
			break;
	}
	strip->fill(currentColor, 0, LED_COUNT);
	strip->show();
}

void LightShow::revertFade(){
	if(savedColor != 0){	//have to make sure we have a color to restore it back to
		strip->fill(savedColor, 0, LED_COUNT);
		colorStatus = Status::singleColor;
		fadingOnGoing = false;
	}
}

//start dictates whether it's going to be even or odd
void LightShow::evenOddFill(bool evenOdd){
	for(int i = evenOdd; i < LED_COUNT; i += 2){
		strip->setPixelColor(i, currentColor);
	}
	colorStatus = Status::singleColor;
	strip->show();
	incrementColorCounter();
}

void LightShow::lightChunks(int color = 0)
{
	int j = 0;
	bool space = false;
	for(int i = 0; i < LED_COUNT; ++i){
		//Set up the conditions to know if I'm filling in empty colors or a chunk
		if(j == 15 && space == false){
			space = true;
			j = 0;
		}
		else if(j == 6 && space == true){
			space = false;
			j = 0;
			if(color != 0){	//if this variable is not 0, the color should be changing
				incrementColorCounter();
				colorStatus = Status::multiColor;
			}
			else{
				colorStatus = Status::singleColor;
			}
		}
		//Fill in the pixels with the appropriate colors
		if(space != true){
			strip->setPixelColor(i, currentColor);
		}
		else{
			strip->setPixelColor(i, strip->Color(0, 0, 0));	//black so it will appear off
		}
		++j;
	}
	strip->show();
}

void LightShow::randomFill(){
	for(int i = 0; i < LED_COUNT-2; i += 3){	//-2 on the max count since we're incrementing in threes and assuming there is always 2 more led in the +1, +2 index
		switch(random(0-5)){
			case 0:
				strip->setPixelColor(i, colorArray[0]);	//blue
				strip->setPixelColor(i+1, colorArray[0]);
				strip->setPixelColor(i+2, colorArray[0]);
				break;
			case 1:
				strip->setPixelColor(i, colorArray[1]);	//red
				strip->setPixelColor(i+1, colorArray[1]);
				strip->setPixelColor(i+2, colorArray[1]);
				break;
			case 2:
				strip->setPixelColor(i, colorArray[2]);	//orange/yellow
				strip->setPixelColor(i+1, colorArray[2]);
				strip->setPixelColor(i+2, colorArray[2]);
				break;
			case 3:
				strip->setPixelColor(i, colorArray[3]);	//green
				strip->setPixelColor(i+1, colorArray[3]);
				strip->setPixelColor(i+2, colorArray[3]);
				break;
			case 4:
				strip->setPixelColor(i, colorArray[5]);	//purple
				strip->setPixelColor(i+1, colorArray[5]);
				strip->setPixelColor(i+2, colorArray[5]);
				break;
		}
	}
	colorStatus = Status::multiColor;
	strip->show();
}

void LightShow::rollForPattern(){
	previousPattern = currentPattern;	//saving
	currentPattern = Pattern::none;	//reseting
	Pattern tempPattern = Pattern::none;
	while(currentPattern == Pattern::none){	//if we accidentally role on the same pattern, it will stay at none and roll again
		switch(random(0-4)){
		case 0:
			tempPattern = Pattern::changeColor;
			break;
		case 1:
			tempPattern = Pattern::evenOddFill;
			break;
		case 2:
			tempPattern = Pattern::lightChunks
			break;
		case 3:
			tempPattern = Pattern::randomFill;
			break;
		}
		//Now check that we haven't rolled on the same pattern
		if(tempPattern != previousPattern){
			currentPattern = tempPattern;	//no longer none, will break out of loop
		}
	}
}

void LightShow::play(bool evenOdd = false, int color = 0){
	//Here we want to call the proper function that will display the proper pattern
	switch(currentPattern){
		case Pattern::changeColor:
			changeColor();
			break;
		case Pattern::evenOddFill:
			evenOddFill(evenOdd);
			break;
		case Pattern::lightChunks:
			lightChunks(color);
			break;
		case Pattern::randomFill:
			randomFill();
			break;
	}
	//Now we want to check out iterationCounter and see if it's time to switch to a new pattern
	--iterationCounter;
	if(iterationCounter == 0){
		//let's roll for a new pattern to display
		rollForPattern();
	}
}