#include <Adafruit_NeoPixel.h>
#include "Lights.h"

// Declare our NeoPixel strip object:
LightShow led;
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));  //Need this to set the random seed
  pinMode(digitalPin, INPUT);
  led.initalize();
}

////variables go here:
//int digital;
//uint32_t blue = strip.Color(0, 0, 255);
//uint32_t red = strip.Color(255, 0, 0);
//uint32_t orange = strip.Color(255, 128, 255);
//uint32_t yellow = strip.Color(255, 255, 0);
//uint32_t green = strip.Color(0, 255, 0);
//uint32_t purple = strip.Color(76, 0, 153);
//uint32_t pink = strip.Color(255, 0, 255); 
//uint32_t colorArray[7] = {blue, red, orange, yellow, green, purple, pink};
//uint32_t oldColor = 0;
//static int index = 0;
//int iterationCounter = 0;

void loop(){
  Serial.println("Hello OOP :)");
}


////DO NOT mess with brightness, setBrightness looses value of it's previous brightness and the more you call it, the dimmer it gets
//void loop(){
//  digital = digitalRead(digitalPin);
//  if(digital == HIGH){
//    //LET IT SHINE BABBYYYYY
//    Serial.println("LIT");
//    strip.fill(colorArray[index], 0, LED_COUNT);
//    strip.show();
//    oldColor = colorArray[index] - 75;
//    ++index;
//    if(index > 6){
//      index = 0;
//    }
////    strip.fill(blue, 0, LED_COUNT);
////    strip.show();
//  }
//  else if(oldColor != 0){
//    //fade the color away by decrementing, this gives the effect of dimming  
//    Serial.println("Fade");
//    strip.fill(oldColor, 0, LED_COUNT);
//    strip.show();
//    if(oldColor > 50){
//      oldColor -= 75;
//    }
//  }
//  //turn them off immediatly 
//  delay(400);  //maybe not so quickly
////  if(iterationCounter == 25){
////    iterationCounter = 0; //reset it so that it doesn't overflow
////    //here I want to call some sort of lightshow
////    strip.clear();  //reset strip
////    int choice = random(0,2);
////    if(choice == 0)
////      gradualFill();
////    else
////      evenOddFill();
////  }
//  //strip.clear();
//  //strip.show();
////  ++iterationCounter;
//}
//
//void colorChase(){
//  for(int i = 5; i < LED_COUNT; ++i){
//    strip.setPixelColor(i-5, 0, 255, 255);
//    strip.setPixelColor(i-4, 0, 255, 255);
//    strip.setPixelColor(i-3, 255, 0, 255);
//    strip.setPixelColor(i-2, 255, 0, 255);
//    strip.setPixelColor(i-1, 255, 255, 0);
//    strip.setPixelColor(i, 255, 255, 0);
//    strip.show();
//    delay(25);
//  }
//}
//
////function that changes color every time it detects a beat
//void BeatsPerColor(int i){
//  //we have 7 colors to work with blue, red, orange, yellow, green, purple, pink all in the colorArray
//  strip.fill(colorArray[i], 0, LED_COUNT);
//}
//
//void gradualFill(){
//  int j = 71;
//  uint32_t randColor;
//  for(int i = 70; i > 0; --i){
//    if(i % 20 == 0){
//      randColor = colorArray[random(0,7)];
//    }
//    strip.setPixelColor(i, randColor);
//    strip.setPixelColor(j, randColor);
//    ++j;
//    strip.show();
//    delay(10);
//  }
//  //REVERSE TIME BABBBYYYYY
//  j = 143;
//  for(int i = 0; i < 71; ++i){
//    if(i % 20 == 0){
//      randColor = colorArray[random(0,7)];
//    }
//    strip.setPixelColor(i, randColor);
//    strip.setPixelColor(j, randColor);
//    --j;
//    strip.show();
//    delay(10);
//  }
//}
//
////lights up every even LED, shows them, lights up all odds, shows them as well
//void evenOddFill(){
//  uint32_t randColor = 0;
//  for(int j = 0; j < 14; ++j){ //0 for even, 1 for odd
//    randColor = colorArray[random(0,7)];
//    for(int i = 0; i < LED_COUNT; ++i){
//      if(j % 2 == 0 && i % 2 == 0){
//        //even
//        strip.setPixelColor(i, randColor);
//      }
//      else if( j % 2 == 1 && i % 2 == 1){
//         //odd
//        strip.setPixelColor(i, randColor);
//      }
//    }
//    //at the end of this for loop, we have filled either an even or an odd
//    strip.show();
//    strip.clear();
//    delay(100);
//  }
//}
//
////TODO make a function for a lightshow that isn't based on the sound detector, average BPM is aroud 160 for what songs kevin would play
//void automatic(){
//
//}
