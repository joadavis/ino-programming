/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

 Modified for my own purposes
 joadavis
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
  myservo3.attach(11);
}

void loop() {
  for (pos = 5; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //if (pos % 15 == 0) {
      myservo2.write(pos);
    //}
    myservo3.write(pos / 2 + 45); // currently have 3 mounted backwards from 2
    delay(45);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 5; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    if (pos % 30 == 0) {
      myservo2.write(pos);
    }
    myservo3.write(pos / 2 + 45);
    delay(300);                       // waits 15ms for the servo to reach the position
  }
  //myservo.write(20);
  //myservo.write(80);
  //delay(300);
  //myservo.write(20);
  //delay(600);
  //myservo.write(80);
  delay(600);

  // circle sweep
  myservo.write(5);
  myservo2.write(180);
  myservo3.write(5);

  delay(1000);
  for (pos = 5; pos <= 180; pos += 1) {
    
  }
}

