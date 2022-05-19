#include <Arduino.h>
#include <Joystick.h>

// Define Input Pins
#define fret1 7
#define fret2 6
#define fret3 5
#define fret4 4
#define fret5 3

#define start 8
#define select 9
#define strumUp 14
#define strumDown 15

#define whammy A10
#define joyX A3
#define joyY A2

// For V2
#define accelerometer1 A0
#define accelerometer2 A1

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  9, 0,                  // Button Count, Hat Switch Count
  true, true, true,      // X, Y, and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

const bool initAutoSendState = true;

int xAxis_ = 0;
int yAxis_ = 0;
int zAxis_ = 0;

// Last state of the buttons
int lastButtonState[9] = {0,0,0, 0,0,0, 0,0,0};

void setup() {
  // Initialize Button Pins
  pinMode(fret1, INPUT_PULLUP);
  pinMode(fret2, INPUT_PULLUP);
  pinMode(fret3, INPUT_PULLUP);
  pinMode(fret4, INPUT_PULLUP);
  pinMode(fret5, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  pinMode(strumUp, INPUT_PULLUP);
  pinMode(strumDown, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

void loop() {

  // Axis Runtime
  xAxis_ = analogRead(joyX);
  xAxis_ = map(xAxis_, 0, 1023, 0, 255);
  Joystick.setXAxis(xAxis_);

  yAxis_ = analogRead(joyY);
  yAxis_ = map(yAxis_, 0, 1023, 0, 255);
  Joystick.setYAxis(yAxis_);

  zAxis_ = analogRead(whammy);
  zAxis_ = map(zAxis_, 0, 1023, 0, 255);
  Joystick.setZAxis(zAxis_);

  // Read pin values
  for (int index = 0; index < 9; index++)
  {// index maps to both the button array and the Windows HID
    int currentPin = index < 7 ? index + 3 : index + 7;
    int currentButtonState = !digitalRead(currentPin);
    if (currentButtonState != lastButtonState[currentPin])
    {
      switch (index) {
        case 0: // FRET 5
          Joystick.setButton(0, currentButtonState);
          break;
        case 1: // FRET 4
          Joystick.setButton(1, currentButtonState);
          break;
        case 2: // FRET 3
          Joystick.setButton(2, currentButtonState);
          break;
        case 3: // FRET 2
          Joystick.setButton(3, currentButtonState);
          break;
        case 4: // FRET 1
          Joystick.setButton(4, currentButtonState);
          break;
        case 5: // START
          Joystick.setButton(5, currentButtonState);
          break;
        case 6: // SELECT
          Joystick.setButton(6, currentButtonState);
          break;
        case 7: // STRUM UP
          Joystick.setButton(7, currentButtonState);
          break;
        case 8: // STRUM DOWN
          Joystick.setButton(8, currentButtonState);
          break;
      }
      lastButtonState[currentPin] = currentButtonState;
    }
  }

  delay(10);
}
