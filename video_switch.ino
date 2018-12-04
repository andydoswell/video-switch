/* Audio Video multiplexer
 *  (c) 2018 A.G.Doswell
 *  
 *  Software to control video multiplexer hardware.
 *  Details on andydoz.blogspot.com
 *  
 */


int systemAselect = 12; // systemA select switch
int systemIselect = 11; // systemI select switch
/*int systemAA0 = A0;
  int systemAA1 = A1;
  int systemAA2 = A2;
  int systemIA0 = 8;
  int systemIA1 = 9;
  int systemIA2 = 10;
*/
int systemAregister;
int systemIregister;
#include <Wire.h>
#include <OzOLED.h>

void setup() {
  analogWrite(3, 127); // bring up -5V rail
  pinMode (systemAselect, INPUT_PULLUP);
  pinMode (systemIselect, INPUT_PULLUP);
  DDRC = DDRC | 0b11100000;
  DDRB = DDRB | 0b11100000;
  /* pinMode (systemAA0, OUTPUT);
    pinMode (systemAA1, OUTPUT);
    pinMode (systemAA2, OUTPUT);
    pinMode (systemIA0, OUTPUT);
    pinMode (systemIA1, OUTPUT);
    pinMode (systemIA2, OUTPUT);*/
  PORTD = PORTD & 0b11100000; // clear top 3  bits
  PORTB = PORTB & 0b11100000;
  OzOled.init();                   // initialze SDD1306 OLED display
  OzOled.sendCommand(0x8d);        // Set displays inbuilt inverter on
  OzOled.sendCommand(0x14);
  OzOled.setBrightness(0xFF);      // ... and brightness to max
  OzOled.clearDisplay();           // Clear the screen
  OzOled.setNormalDisplay();       // Set display to Normal mode
  OzOled.clearDisplay();
  OzOled.printString("405 Source", 0, 0);
  OzOled.printString("625 Source", 0, 3);
}
// start select register at 32 and increment 32 for every address. write it straight to the port. , once it gets to 160, reset.
void loop() {
  if (digitalRead (systemAselect)) {
    systemAregister += 32;
    if (systemAregister == 256) {
      systemAregister = 0;
    }
    PORTC = PORTC & 0b00011111; // clear top 3 bits
    PORTC = PORTC | systemAregister;
    updateDisplay ();
    delay (100);
  }
  if (digitalRead (systemIselect)) {
    systemIregister += 32;
    if (systemIregister == 256) {
      systemIregister = 0;
    }
    PORTB = PORTB & 0b00011111; // clear top 3 bits
    PORTB = PORTB | systemIregister;
    updateDisplay ();
    delay (100);
  }
}

void updateDisplay () {
  switch (systemAregister) {
    case 0:
      OzOled.printString("Media Box      ", 0, 2);
      break;
    case 32:
      OzOled.printString("DVD            ", 0, 2);
      break;
    case 64:
      OzOled.printString("Top Freeview   ", 0, 2);
      break;
    case 96:
      OzOled.printString("Bottom Freeview", 0, 2);
      break;
    case 128:
      OzOled.printString("HDMI Input     ", 0, 2);
      break;
    case 160:
      OzOled.printString("FreeSat        ", 0, 2);
      break;
    case 192:
      OzOled.printString("Aux 1 Input    ", 0, 2);
      break;
    case 224:
      OzOled.printString("Aux 2 Input    ", 0, 2);
      break;
  }
  switch (systemIregister) {
    case 0:
      OzOled.printString("Media Box      ", 0, 4);
      break;
    case 32:
      OzOled.printString("DVD            ", 0, 4);
      break;
    case 64:
      OzOled.printString("Top Freeview   ", 0, 4);
      break;
    case 96:
      OzOled.printString("Bottom Freeview", 0, 4);
      break;
    case 128:
      OzOled.printString("HDMI Input     ", 0, 4);
      break;
    case 160:
      OzOled.printString("FreeSat        ", 0, 4);
      break;
    case 192:
      OzOled.printString("Aux 1 Input    ", 0, 4);
      break;
    case 224:
      OzOled.printString("Aux 2 Input    ", 0, 4);
      break;
  }
}
