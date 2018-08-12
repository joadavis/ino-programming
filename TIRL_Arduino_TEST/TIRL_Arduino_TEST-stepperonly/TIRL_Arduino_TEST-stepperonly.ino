// Thanks to Ken Olsen for the original version of this sketch.
// Modified by Joseph Davis, May 2016

#include <Servo.h>

// setup servo
//int servoPin = 8;
//int PEN_DOWN = 20; // angle of servo when pen is down
//int PEN_UP = 80;   // angle of servo when pen is up
//Servo penServo;

float wheel_dia=62 ; //    # mm (increase = spiral out), orig 63
float wheel_base=112; //    # mm (increase = spiral in, ccw)  ,orig 109
//int steps_rev=128; //        # 512 for 64x gearbox, 128 for 16x gearbox
//int delay_time=6; //         # time between steps in ms
int steps_rev=512; //        # 512 for 64x gearbox, 128 for 16x gearbox
int delay_time=6; //         # time between steps in ms, set to 100 to really see

// Arduino Uno has a built in LED on pin 13
//const int ledPin =  13;

// Stepper sequence org->pink->blue->yel
//int L_stepper_pins[] = {12, 10, 9, 11};
//int R_stepper_pins[] = {4, 6, 7, 5};

int L_stepper_pins[] = {10, 11, 12, 13};
int R_stepper_pins[] = {5, 4, 3, 2};

int PEN_stepper_pins[] = {9, 8, 7, 6};
// will use forward for pen up, back for pen down
int PEN_STEPS=20;

// JAD initial wiring
// oypb DCBA -> b bs r w (4321) -> bs4 b5 w6 r7 (ie 5 4 7 6)
// oypb DCBA -> b bs r w (4321) -> bs9 b10 w11 r12 (ie 10 9 12 11)

// revised wiring
// made all sequential

/*
int fwd_mask[][4] =  {{1, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

 *
 * // Original
int rev_mask[][4] =  {{1, 0, 0, 1},
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};

int rev_mask[][4] =  {{0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0},
                      {1, 0, 0, 1}};
*/
// Single stepping
int fwd_mask[][4] =  {{1, 0, 0, 0},
                      {0, 1, 0, 0},
                      {0, 0, 1, 0},
                      {0, 0, 0, 1}};
int rev_mask[][4] =  {{0, 0, 1, 0},
                      {0, 1, 0, 0},
                      {1, 0, 0, 0},
                      {0, 0, 0, 1}};



int analogValue = 0;


void setup() {
  randomSeed(analogRead(1)); 
  Serial.begin(9600);

  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);

  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);

    pinMode(PEN_stepper_pins[pin], OUTPUT);
    digitalWrite(PEN_stepper_pins[pin], LOW);
  }
  //penServo.attach(servoPin);
  Serial.println("setup");

  // ASSUMING start with pen down
  penup();
  
  delay(1000);
}


void loop(){ 
  //pendown();

  // control using an analog potentiometer (dial)
  analogValue = analogRead(0);
  Serial.println(analogValue);

  if (analogValue < 200) {
    // draw a calibration box 4 times
    pendown();
    Serial.println("calibration squares");
    for(int x=0; x<12; x++){
      forward(100);
      left(90);
    }
    for(int x=0; x<12; x++){
      forward(50);
      right(90);
    }
    penup();
    done();      // releases stepper motor

  }

  else if (analogValue < 400) {
    // preset 1
    Serial.println("preset 1 - name");
    //blink_pin(1);
    
    // try some letters, passing a unit size
    write_E(50);
    write_L(50);
    write_I(50);
    write_A(50);
    write_S(50);
    
    done();      // releases stepper motor
  }
  else if (analogValue < 600) {
    // preset 2
    Serial.println("preset 2 - wiggle");
    //blink_pin(2);
    
    forward(1);
    delay(delay_time);
    forward(1);
    delay(delay_time);
    
    for(int x=0; x<12; x++){
      forward(25);
      left(45);
      forward(25);
      right(45);
    }
    
    forward(25);
    done();      // releases stepper motor
  }
  else {
    // preset whatever is left
    Serial.println("preset leftover");
    //blink_pin(3);
    
    done();      // releases stepper motor
  }

  
  while(1);    // wait for reset
}


// ----- HELPER FUNCTIONS -----------
int step(float distance){
  int steps = distance * steps_rev / (wheel_dia * 3.1412); //24.61
  /*
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(steps_rev);
  Serial.print(" ");  
  Serial.print(wheel_dia);
  Serial.print(" ");  
  Serial.println(steps);
  delay(1000);*/
  return steps;  
}


void forward(float distance){
  int steps = step(distance);
  Serial.print("Fwd ");
  Serial.println(steps);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}


void backward(float distance){
  int steps = step(distance);
  Serial.print("Bck ");
  Serial.println(steps);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}


void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}

// Letters assume you are starting at the lower left corner of the letter
// start by pendown, end with penup

void write_E(float distance){
  pendown();
  left(90);
  forward(distance);
  forward(distance);
  right(90);
  forward(distance);
  // TODO: pen up around backwards
  backward(distance);
  left(90);
  backward(distance);
  right(90);
  forward(distance * 0.8);
  backward(distance * 0.8);
  left(90);
  backward(distance);
  right(90);
  forward(distance);
  
  // pen up
  penup();
  // kerning
  forward(distance * 0.5);
  // pen down
}

void write_L(float distance){
  pendown();
  left(90);
  forward(distance * 2);
  backward(distance * 2);
  right(90);
  forward(distance);
  // kerning
  penup();
  forward(distance * 0.5);
}

void write_I(float distance){
  pendown();
  left(90);
  forward(distance * 2.0);
  backward(distance * 2.0);
  right(90);
  // kerning
  penup();
  forward(distance * 0.5);
}

void write_A(float distance){
  float magicDist = distance * 1.41 * 0.5;
  pendown();
  left(90);
  forward(distance);
  right(90);
  forward(distance * 0.5);
  backward(distance * 0.5);
  left(90);
  forward(distance * 0.5);
  right(45);
  forward(magicDist);
  right(90);
  forward(magicDist);
  right(45);
  forward(distance * 0.5);
  right(90);
  forward(distance * 0.5);
  backward(distance * 0.5);
  left(90);
  forward(distance);
  left(90);
  
  // kerning
  penup();
  forward(distance * 0.5);
}

void write_S(float distance){
  pendown();
  forward(distance);
  left(90);
  forward(distance);
  left(90);
  forward(distance);
  right(90);
  forward(distance);
  right(90);
  forward(distance);
  penup();
  right(90);
  forward(distance * 2.0);
  left(90);
  // kerning
  penup();
  forward(distance * 0.5);
}

/*
void blink_pin(int blks){
  // start low
  digitalWrite(ledPin, LOW);
  for(int bl_num = 0; bl_num<blks; bl_num++) {
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
    delay(10);
  }
}
*/


void done(){ // unlock stepper to save battery
  for(int mask=0; mask<4; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}


// stepper version
void penup(){
  delay(25);
  Serial.println("PEN_UP()");
  int steps = step(PEN_STEPS);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(PEN_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
  delay(25);
}


// stepper version
void pendown(){
  delay(25);
  Serial.println("PEN_DOWN()");
  int steps = step(PEN_STEPS);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(PEN_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
  delay(25);
}


/*
void penup(){
  delay(250);
  Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}
*/
