 #include "Lights.h"

// Declare our NeoPixel strip object:
LightShow led;
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int digital;
unsigned long startTime = 0;
unsigned long nowTime = 0;
bool fade = false;

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
  Serial.print("Digital: "); Serial.println(digital);
//  Serial.print("Fade: ");Serial.println(fade);
  if(digital == HIGH){
    //reset conditions for detecting fade since we are not fading anymore
//    fade = false; 
//    startTime = 0;
    //play patterns
    led.play();
    led.clearStrip();
    delay(150);
  }
//  else if(fade == true){
//    led.fadeColor();
//  }
//  else{ //there could be a quiet built up, start timer for roughly 1 second, if no high detcted start fading
//    if(startTime == 0 && fade == false){ //first time it detected that we should be checking for fade
//      startTime = millis();
//    }
//    nowTime = millis();
//    Serial.print("Start time: "); Serial.println(startTime);
//    Serial.print("Now time: "); Serial.println(nowTime);
//    Serial.print("Result: "); Serial.println(nowTime - startTime);
//    if(nowTime - startTime > 2000 && fade == false){  //checking if the difference is greater than 2 seconds
//      //start fade
//      fade = true;
//      led.fadeColor();
//    }
//  }
  //delay(150); //we only want 1 reading of high and not 3 in a row or more for example
}
