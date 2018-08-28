/* Infrared_Send.ino Example sketch for IRLib2 and Circuit Playground Express
   Illustrates how to transmit an IR signal whenever you do push one of the
   built-in pushbuttons.
*/
#include <Adafruit_CircuitPlayground.h>

float spl;
float movement;

#if !defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #error "Infrared support is only for the Circuit Playground Express, it doesn't work with the Classic version"
#endif

void setup() {

  Serial.begin(9600);
  CircuitPlayground.begin();
}

//Defines for a Samsung TV using NECx protocol
//#define MY_PROTOCOL NECX
#define MY_PROTOCOL NEC
#define MY_BITS 32
#define MY_MUTE 0xE0E0F00F
#define MY_POWER 0xF7A05F

#define FADE7 0xF7F00F
#define WHITE 0xF7E01F
#define PURPLE 0xF7D02F
#define MUSIC4 0xF7C837
#define OFF 0xF7C03F
#define JUMP7 0xF7B04F
#define GREEN 0xF7A05F
#define YELLOW 0xF7906F
#define MUSIC2 0xF78877
#define BRIGHTNESSDOWN 0xF7807F
#define FADE3 0xF7708F
#define BLUE 0xF7609F
#define CYAN 0xF750AF
#define MUSIC3 0xF748B7
#define ON 0xF740BF
#define JUMP3 0xF730CF
#define RED 0xF720DF
#define ORANGE 0xF710EF
#define MUSIC1 0xF708F7
#define BRIGHTNESSUP 0xF700FF
#define TERMINATOR 0xFFFFFFFF

void loop() {
  // If the left button is pressed send a mute code.

  if (CircuitPlayground.leftButton()) {
    CircuitPlayground.irSend.send(MY_PROTOCOL,MY_MUTE,MY_BITS);
    while (CircuitPlayground.leftButton()) {}//wait until button released
  }

  // If the right button is pressed send a power code.
  if (CircuitPlayground.rightButton()) {
    CircuitPlayground.irSend.send(MY_PROTOCOL,MY_POWER,MY_BITS);
    while (CircuitPlayground.rightButton()) {}//wait until button released
  }







  if (CircuitPlayground.slideSwitch()==1) {
    //MODE 1 - motion sensing
    //Measure movement in y axis
    movement = abs( CircuitPlayground.motionY() );
    // Report movement
    Serial.println(movement);


    if (movement < 1) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,RED,MY_BITS);
     Serial.println("red");
    }
    if (movement > 1 && movement < 2) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,ORANGE,MY_BITS);
     Serial.println("orange");
    }
    if (movement > 2 && movement < 3) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,YELLOW,MY_BITS);
     Serial.println("yellow");
    }
    if (movement > 3 && movement < 4) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,GREEN,MY_BITS);
     Serial.println("green");
    }
    if (movement > 4 && movement < 5) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,BLUE,MY_BITS);
     Serial.println("blue");
    }
    if (movement > 5 && movement < 6) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,PURPLE,MY_BITS);
     Serial.println("purple");
    }
    if (movement > 6 && movement < 500) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,WHITE,MY_BITS);
     Serial.println("white");
    }
        delay(80);

  }



  if (CircuitPlayground.slideSwitch()==0) {
    //MODE 2 - sound sensing

    // Take 50 milliseconds of sound data to calculate
    spl = CircuitPlayground.mic.soundPressureLevel(80);
    Serial.println(spl);


    if (spl < 84) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,RED,MY_BITS);
    Serial.println("red");
    }
    if (spl > 84 && spl < 87) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,ORANGE,MY_BITS);
    Serial.println("orange");
    }
    if (spl > 87 && spl < 90) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,YELLOW,MY_BITS);
    Serial.println("yellow");
    }
    if (spl > 93 && spl < 96) {
      CircuitPlayground.irSend.send(MY_PROTOCOL,GREEN,MY_BITS);
      Serial.println("green");
    }
    if (spl > 96 && spl < 99) {
      CircuitPlayground.irSend.send(MY_PROTOCOL,BLUE,MY_BITS);
      Serial.println("blue");
    }
    if (spl > 99 && spl < 101) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,PURPLE,MY_BITS);
     Serial.println("purple");
    }
    if (spl > 101 && spl < 500) {
     CircuitPlayground.irSend.send(MY_PROTOCOL,WHITE,MY_BITS);
     Serial.println("white");
    }
  }


    //follow each message with a terminator
    CircuitPlayground.irSend.send(MY_PROTOCOL,TERMINATOR,MY_BITS);
    CircuitPlayground.irSend.send(MY_PROTOCOL,TERMINATOR,MY_BITS);
    CircuitPlayground.irSend.send(MY_PROTOCOL,TERMINATOR,MY_BITS);

}
