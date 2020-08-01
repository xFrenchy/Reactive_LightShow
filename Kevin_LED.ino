 #include "Lights.h"

// Declare our NeoPixel strip object:
LightShow led;
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int digital;
int iterationCounter = 0;
bool evenOdd = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));  //Need this to set the random seed
  pinMode(DIGITALPIN, INPUT);
  led.initialize();
  led.rollForPattern(); //ABSOLUTELY NEEDED BECAUSE THE PATTERN IS DEFAUTLY ON NONE
  led.clearStrip();
}

void loop(){
  digital = digitalRead(DIGITALPIN);
//  Serial.println(digital);
  if(digital == HIGH){
    led.play();
    led.clearStrip();
    delay(150); //we only want 1 reading of high and not 3 in a row or more for example
  }
  else{ //there could be a quiet built up, start timer for roughly 1 second, if no high detcted start fading
    
  }
}
