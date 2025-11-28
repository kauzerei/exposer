#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int divs=200;
int del=2000;
int amp;
int spd;
int pin1=A4;
int pin2=A5;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  amp=1024-analogRead(pin1);
  spd=analogRead(pin2);
  del=100000.0/(spd+10);
  divs=del<50?1:del<100?2:del<200?4:del<400?8:del<800?16:del<1600?32:del<3200?64:del<6400?128:del<12800?256:512;

  for(float a=0; a<divs; a+=1) {
/*  amp=1024-analogRead(pin1);
  spd=analogRead(pin2);
  del=100000.0/(spd+10);
  divs=del<50?1:del<100?2:del<200?4:del<400?8:del<800?16:del<1600?32:del<3200?64:del<6400?128:del<12800?256:512;
*/
    myservo.write(90.0+90.0*amp*sin(a*2.0*355.0/113.0/divs)/1024);
    //myservo.write(90);
    delay(del/divs);  
  }
}
