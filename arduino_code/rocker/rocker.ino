#include <Servo.h>
#include <math.h>

Servo servo;
int freq_pin=A4;
int amp_pin=A5;
int freq_pot; //frequency pot read value
int amp_pot; //amplitude pot read value
float freq; //frequency exact value
float amp;
float srv_vals[256];
byte index=0;
int skip;
unsigned long switchtime;

void setup() {
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  for (int i=0;i<256;i++) srv_vals[i]=sin(float(i)*2.0*PI/256.0);
  switchtime=micros();
}

void loop() {
  freq_pot=1024-analogRead(freq_pin); //can remove 1024- to invert the pot direction
  freq=pow(10.0,(float(freq_pot-512)/512.0)); //map 0-1023 values to exp frequency scale from 0.1 to 10 hz
  amp_pot=1024-analogRead(amp_pin); //can remove 1024- to invert the pot direction
  amp=90.0*amp_pot/1024.0;
  skip=max(0,ceil(8+log(freq/50)/log(2)));
  index=(index&(255<<skip))+(1<<skip);
  switchtime=switchtime+1000000*pow(2,skip-8)/freq;
  while(micros()<switchtime);
  servo.write(90+amp*srv_vals[index]);
}
