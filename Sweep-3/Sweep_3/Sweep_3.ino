// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

// modified for my purposes - joadavis


#include <Servo.h> 
 
//Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo servo_pen;
Servo servo_y;
Servo servo_x1;
Servo servo_x2;  // may be flipped to match?

int pos_pen = 0;    // variable to store the servo position 
int pos_y = 0;    // variable to store the servo position 
int pos_x1 = 0;    // variable to store the servo position 
int pos_x2 = 0;    // variable to store the servo position 

int action = 1;
int PEN_UP = 90;
int PEN_DOWN = 5;

void setup() 
{ 
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo_pen.attach(11);
  servo_y.attach(10);
  servo_x1.attach(6);
  servo_x2.attach(5);
} 
 
 
void loop() 
{ 
  action = 1;
  if (action == 0) 
  {
    // zero out the servos
    pos_pen = PEN_UP;
    servo_pen.write(pos_pen);
    
    pos_y = 0;
    servo_y.write(pos_y);
    pos_x1 = 0;
    servo_x1.write(pos_x1);
    pos_x2 = 0;
    servo_x2.write(pos_x2);
  }
  else if (action == 1)
  {
    sweep();
  }
  delay(150);  
}
  
void sweep()
{
  servo_pen.write(PEN_DOWN);
  int pos = 5;
  // trimming back the range by 5 deg on each end
  for(pos = 5; pos < 176; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_y.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 175; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo_y.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  servo_pen.write(PEN_UP);
  delay(200);
} 
