# Time relay for exposure unit.
#
# Copyright (c) 2024 Kauzerei
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

#include <TM1637Display.h> //https://github.com/avishorp/TM1637

const char led_out=7;
const char button_up=6;
const char button_mid=5;
const char button_down=4;
const char display_clk=2;
const char display_dio=3;
byte ei=10;
double sec=1;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
unsigned long time;
  
TM1637Display display(display_clk, display_dio);

void setup() {
  pinMode(led_out,OUTPUT);
  pinMode(button_up,INPUT_PULLUP);
  pinMode(button_down,INPUT_PULLUP);
  pinMode(button_mid,INPUT_PULLUP);
  digitalWrite(led_out,LOW);
  display.setBrightness(0x0f);
}

void showtime(byte ei) {
  if (ei>10) display.showNumberDec(2<<(ei-11));
  else if (ei==10) display.showNumberDec(1);
  else display.showNumberDecEx(2<<(9-ei),0b11100000);
  }

void loop() {
  showtime(ei);
  if (digitalRead(button_up)==LOW) {ei=ei+1; delay(100);}
  if (digitalRead(button_down)==LOW) {ei=ei-1; delay(100);}
  if (digitalRead(button_mid)==LOW) {
    time=millis();
    digitalWrite(led_out,HIGH);
    while (millis()-time<pow(2,ei-10)*1000)
    display.showNumberDec((millis()-time)/1000-pow(2,ei-10));
    digitalWrite(led_out,LOW);
    delay(500); //implement this better someday maybe
  }
}
