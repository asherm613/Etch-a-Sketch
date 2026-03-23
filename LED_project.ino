#include <FastLED.h>
#define DATA_PIN 5
#define NUM_LEDS 256
int i=0;

void translate(int y, int x) {
  if(y%2==1){
    i=(y*16)+15-x;
  }
  else{
    i=(y*16)+x;
  }
  return i;
}

int Reset = 2;
int G = 4;
int B = 3;
int Xval;
int Yval;
char* clearState = "False";

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(Reset, INPUT);
  pinMode(G, INPUT);
  pinMode(B, INPUT);
  Serial.begin (9600);  
  attachInterrupt(0, reset, RISING); // if reset button is pressed run "void reset"
}
void reset() {
  clearState = "True"; // set the variable clearState to true
}
void loop() {
  int g = digitalRead(G);
  int b = digitalRead(B);
  Xval= map(analogRead(A0), 0, 1023, 0, 15); 
  Yval= map(analogRead(A1), 0, 1023, 0, 15);
  translate(Yval, Xval);
  Serial.println(i); // print the map values
  if (clearState == "True") { // if variable clearState is set to true by the interrupt
    FastLED.clear(); // clear the matrix
    FastLED.show();
    clearState = "False"; // set clearState to false
  }
  if (g == HIGH || b == HIGH) { // if green or blue buttons are pressed
    if (g == HIGH) { // if green is pressed
      leds[i] = CRGB::Green;
      FastLED.show(); // turn the selected light green
    }
    if (b == HIGH) { // if green is pressed
      leds[i] = CRGB::Blue;
      FastLED.show(); // turn the selected light blue
    }
  }
  else { // cursor logic
    if (leds[i] == CRGB::Black) { // if the light is black
      leds[i] = CRGB::Red;
      FastLED.show(); // turn red
      delay (30);
      leds[i] = CRGB::Black;
      FastLED.show(); // after 30 milliseconds turn black
    }
    if (leds[i] == CRGB::Blue) { // if the light is blue
      leds[i] = CRGB::Red;
      FastLED.show(); // turn red
      delay (30);
      leds[i] = CRGB::Blue;
      FastLED.show(); // after 30 milliseconds turn blue
    }
    if (leds[i] == CRGB::Green) { // if the light is green
      leds[i] = CRGB::Red; // turn red
      FastLED.show();
      delay (30);
      leds[i] = CRGB::Green;
      FastLED.show(); // after 30 milliseconds turn green
    }
  }
}