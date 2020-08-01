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
  pinMode(digitalPin, INPUT);
  led.initialize();
}

void loop(){
  digital = digitalRead(digitalPin);
//  Serial.println(digital);
  if(digital == HIGH){
    led.play();
    iterationCounter = random(7-35);  //patterns will execute for a random amount of times in that range
    switch(random(0-4))
//    led.fadeColor();
//      led.revertFade();
//    led.randomFill();
//    led.lightChunks(1); //send in a number that isn't a 0 to make each chunk a different color
//    led.lightChunks();
//    led.incrementColorCounter();
//    if(iterationCounter < 25){
//      led.changeColor();
//    }
//    else{
//      led.evenOddFill(evenOdd); //min inclusive, max exclusive
//      evenOdd = !evenOdd;
//    }

    
    led.clearStrip();
    ++iterationCounter;
    if(iterationCounter > 50){
      iterationCounter = 0;
    }
    delay(150); //we only want 1 reading of high and not 3 in a row or more for example
  }
  else{ //there could be a quiet built up, start timer for roughly 1 second, if no high detcted start fading

  }
}
