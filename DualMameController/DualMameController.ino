/*
Copyright (c) 2014 WeepingWashyu
This sketch requires the used of NicoHood HID libarary and the Adafruit MCP23017 library.

My Arduino gamepad interface for my mame arcade.
Just a simple sketch to create a dougle joystick interface for my mamearcade using two mcp23017s and an Arduino Micro.
I will probably have to modify this latter to use some of the extra I/O of the Arduino to set the MCP23017 i2c address and to trigger the reset.
*/
#include <HID.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

//defines for the pin addresses I used on the mcp23017
#define dpadup 0
#define dpaddown 1
#define dpadleft 2
#define dpadright 3
#define button1 4
#define button2 5
#define button3 6
#define button4 7
#define button5 15
#define button6 14
#define coin 13
#define playerStart 12

//Objects for the MCP23017
Adafruit_MCP23017 controller1, controller2;
//Objects for the HID Gamepads
Gamepad Gamepad1(1), Gamepad2(2);

//Setting all the pins on the mcp23017 to input using the internal pull up resistor.
void controller1Setup(){
  controller1.begin(0);
  for(int i = 0; i < 16; i++)
  {
    controller1.pinMode(i, INPUT);
    controller1.pullUp(i, HIGH);
  } 
}

//Setting all the pins on the mcp23017 to input using the internal pull up resistor.
void controller2Setup(){
  controller2.begin(1);
  for(int i = 0; i < 16; i++)
  {
    controller2.pinMode(i, INPUT);
    controller2.pullUp(i, HIGH);
  } 
}

//Cycle through the pins on the MCP23017 to set state for Gamepad 1 then send the state to the host.
void controller1Set() {
  //set dpad direction
  if(!controller1.digitalRead(dpadup) && (controller1.digitalRead(dpadleft) && controller1.digitalRead(dpadright))) {
      Gamepad1.dPad1(GAMEPAD_DPAD_UP);
  } else if (!controller1.digitalRead(dpadup) && !controller1.digitalRead(dpadleft)) {
      Gamepad1.dPad1(GAMEPAD_DPAD_UP_LEFT);
  } else if (!controller1.digitalRead(dpadup) && !controller1.digitalRead(dpadright)) {
      Gamepad1.dPad1(GAMEPAD_DPAD_UP_RIGHT);
  } else if (!controller1.digitalRead(dpaddown) && (controller1.digitalRead(dpadleft) && controller1.digitalRead(dpadright))) {
      Gamepad1.dPad1(GAMEPAD_DPAD_DOWN);
  } else if (!controller1.digitalRead(dpaddown) && !controller1.digitalRead(dpadleft)) {
      Gamepad1.dPad1(GAMEPAD_DPAD_DOWN_LEFT);
  } else if (!controller1.digitalRead(dpaddown) && !controller1.digitalRead(dpadright)) {
      Gamepad1.dPad1(GAMEPAD_DPAD_DOWN_RIGHT);
  } else if (!controller1.digitalRead(dpadleft) && (controller1.digitalRead(dpadup) && controller1.digitalRead(dpaddown))) {
      Gamepad1.dPad1(GAMEPAD_DPAD_LEFT);
  } else if (!controller1.digitalRead(dpadright) && (controller1.digitalRead(dpadup) && controller1.digitalRead(dpaddown))) {
      Gamepad1.dPad1(GAMEPAD_DPAD_RIGHT);
  } else {
      Gamepad1.dPad1(GAMEPAD_DPAD_CENTERED);
  }

  //set buttons
  (!controller1.digitalRead(button1)) ? Gamepad1.press(1) : Gamepad1.release(1);
  (!controller1.digitalRead(button2)) ? Gamepad1.press(2) : Gamepad1.release(2); 
  (!controller1.digitalRead(button3)) ? Gamepad1.press(3) : Gamepad1.release(3);
  (!controller1.digitalRead(button4)) ? Gamepad1.press(4) : Gamepad1.release(4);  
  (!controller1.digitalRead(button5)) ? Gamepad1.press(5) : Gamepad1.release(5);
  (!controller1.digitalRead(button6)) ? Gamepad1.press(6) : Gamepad1.release(6);
  (!controller1.digitalRead(coin)) ? Gamepad1.press(7) : Gamepad1.release(7);
  (!controller1.digitalRead(playerStart)) ? Gamepad1.press(8) : Gamepad1.release(8);

  Gamepad1.write();
}

//Cycle through the pins on the MCP23017 to set state for Gamepad 2 then send the state to the host.
void controller2Set() {
  //set dpad direction
  if(!controller2.digitalRead(dpadup) && (controller2.digitalRead(dpadleft) && controller2.digitalRead(dpadright))) {
      Gamepad2.dPad1(GAMEPAD_DPAD_UP);
  } else if (!controller2.digitalRead(dpadup) && !controller2.digitalRead(dpadleft)) {
      Gamepad2.dPad1(GAMEPAD_DPAD_UP_LEFT);
  } else if (!controller2.digitalRead(dpadup) && !controller2.digitalRead(dpadright)) {
      Gamepad2.dPad1(GAMEPAD_DPAD_UP_RIGHT);
  } else if (!controller2.digitalRead(dpaddown) && (controller2.digitalRead(dpadleft) && controller2.digitalRead(dpadright))) {
      Gamepad2.dPad1(GAMEPAD_DPAD_DOWN);
  } else if (!controller2.digitalRead(dpaddown) && !controller2.digitalRead(dpadleft)) {
      Gamepad2.dPad1(GAMEPAD_DPAD_DOWN_LEFT);
  } else if (!controller2.digitalRead(dpaddown) && !controller2.digitalRead(dpadright)) {
      Gamepad2.dPad1(GAMEPAD_DPAD_DOWN_RIGHT);
  } else if (!controller2.digitalRead(dpadleft) && (controller2.digitalRead(dpadup) && controller2.digitalRead(dpaddown))) {
      Gamepad2.dPad1(GAMEPAD_DPAD_LEFT);
  } else if (!controller2.digitalRead(dpadright) && (controller2.digitalRead(dpadup) && controller2.digitalRead(dpaddown))) {
      Gamepad2.dPad1(GAMEPAD_DPAD_RIGHT);
  } else {
      Gamepad2.dPad1(GAMEPAD_DPAD_CENTERED);
  }

  //set buttons
  (!controller2.digitalRead(button1)) ? Gamepad2.press(1) : Gamepad2.release(1);
  (!controller2.digitalRead(button2)) ? Gamepad2.press(2) : Gamepad2.release(2); 
  (!controller2.digitalRead(button3)) ? Gamepad2.press(3) : Gamepad2.release(3);
  (!controller2.digitalRead(button4)) ? Gamepad2.press(4) : Gamepad2.release(4);  
  (!controller2.digitalRead(button5)) ? Gamepad2.press(5) : Gamepad2.release(5);
  (!controller2.digitalRead(button6)) ? Gamepad2.press(6) : Gamepad2.release(6);
  (!controller2.digitalRead(coin)) ? Gamepad2.press(7) : Gamepad2.release(7);
  (!controller2.digitalRead(playerStart)) ? Gamepad2.press(8) : Gamepad2.release(8);

  Gamepad2.write();
}

void setup() {  
 
  controller1Setup();
  controller2Setup();
  
  // Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
  // This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
  Serial.begin(SERIAL_HID_BAUD);

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
  Gamepad1.begin();
  Gamepad2.begin();
}

void loop() {
    controller1Set();
    controller2Set();
}

/*
Prototypes:

void begin(void);
void end(void);
void write(void);
void press(uint8_t b);
void release(uint8_t b);
void releaseAll(void);
void buttons(uint32_t b);
void xAxis(int16_t a);
void yAxis(int16_t a);
void rxAxis(int16_t a);
void ryAxis(int16_t a);
void zAxis(int8_t a);
void rzAxis(int8_t a);
void dPad1(int8_t d);
void dPad2(int8_t d);

Definitions:
GAMEPAD_DPAD_CENTERED 0
GAMEPAD_DPAD_UP 1
GAMEPAD_DPAD_UP_RIGHT 2
GAMEPAD_DPAD_RIGHT 3
GAMEPAD_DPAD_DOWN_RIGHT 4
GAMEPAD_DPAD_DOWN 5
GAMEPAD_DPAD_DOWN_LEFT 6
GAMEPAD_DPAD_LEFT 7
GAMEPAD_DPAD_UP_LEFT 8
*/
