// Time relay for exposure unit.
//
// Copyright (c) 2024 Kauzerei
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include <TM1637Display.h> //https://github.com/avishorp/TM1637

const char led_out=7;
const char button=6;
const char encoder_b=5;
const char encoder_a=4;
const char display_clk=2;
const char display_dio=3;
unsigned long debounce=0;
byte ei=10;
double sec=1;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
unsigned long time;
  
TM1637Display display(display_clk, display_dio);

ISR (PCINT2_vect){ // PCINT2_vect: interrupt vector for PORTD
  //if (digitalRead(encoder_a)&&digitalRead(encoder_b)) ei=ei-1;
  //if (digitalRead(encoder_a)&&!digitalRead(encoder_b)) ei=ei+1;
  if (millis()>debounce && (PIND&(1<<4))) {
    if ((PIND&(1<<5))) ei--;
    else ei++;
    debounce=millis()+20;
  }
}

void setup() {
  pinMode(led_out,OUTPUT);
  pinMode(encoder_a,INPUT_PULLUP);
  pinMode(encoder_b,INPUT_PULLUP);
  pinMode(button,INPUT_PULLUP);
  digitalWrite(led_out,LOW);
  display.setBrightness(0x0f);
  PCICR = (1<<PCIE2);    // enable PCINT[23:16] interrupts
  PCMSK2 = (1<<PCINT20); // D4 = PCINT20
}

void showtime(byte ei) {
  if (ei>10) display.showNumberDec(2<<(ei-11));
  else if (ei==10) display.showNumberDec(1);
  else display.showNumberDecEx(2<<(9-ei),0b11100000);
  }

void loop() {
  showtime(ei);
  if (digitalRead(button)==LOW) {
    time=millis();
    digitalWrite(led_out,HIGH);
    while (millis()-time<pow(2,ei-10)*1000)
    display.showNumberDec((millis()-time)/1000-pow(2,ei-10));
    digitalWrite(led_out,LOW);
    delay(500); //implement this better someday maybe
  }
}
