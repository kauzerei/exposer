#include <Servo.h>
#include <math.h>

Servo servo;
//frequency:
int freq_pin=A4; //input pin
int freq_pot; //pot read value
float freq; //value in Hz

//amplitude:
int amp_pin=A5; //input pin
int amp_pot; //pot read value
float amp; //value in degrees (max 90)

float srv_vals[256]; //precalculated sin values
byte index=0; //current index in srv_vals array
int skip; //number of bits to skip in index
unsigned long switchtime; //value of micros() to send next goal to servo
const float servo_freq=100; //100 works better than theoretical 50 for some reason

//maybe precalculate freq and skip values just in case?
//can they possibly take more than 1/100s?
//works as is, but think about it

void setup() {
  servo.attach(9);
  for (int i=0;i<256;i++) srv_vals[i]=sin(float(i)*2.0*PI/256.0); //precalculate sin values
  switchtime=micros();
}

void loop() {
  freq_pot=1024-analogRead(freq_pin); //can remove 1024- to invert the pot direction
  freq=pow(10.0,(float(freq_pot-512)/512.0)); //map 0-1023 values to exp frequency scale from 0.1 to 10 hz
  amp_pot=1024-analogRead(amp_pin); //can remove 1024- to invert the pot direction
  amp=90.0*amp_pot/1024.0;
  skip=max(0,ceil(8+log(freq/servo_freq)/log(2)));
  index=(index&(255<<skip))+(1<<skip);
  switchtime=switchtime+1000000*pow(2,skip-8)/freq;
  while(micros()<switchtime);
  servo.write(90+amp*srv_vals[index]);
}
