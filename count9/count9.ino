/*
  with a 3x3 array of leds, count using the pins like pips on a die
 */
 
int sensorPin = A0;
int sensorValueA0 = 0;
// 0 to 9, with 000 010 000 representing a dot in middle
// my pin layout
// 13 12 11
// 10  9  8
//  7  6  5
// value matrix
// 256 128  64
//  32  16   8
//   4   2   1
int numPatterns[] = {
  000000000,
  16,
  256 + 1,
  256 + 16 + 1,
  256 + 64 + 4 + 1,

  256 + 64 + 16 + 4 + 1,
  511 - 128 - 16 - 2,
  511 - 128 - 2,
  511 - 16,
  511
};
int currNum = 0;

// the setup routine runs once when you press reset:
void setup() {                
  
  for (int thisPin = 5; thisPin < 14; thisPin++)  {
    pinMode(thisPin, OUTPUT);      
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // use the loop to increment through the patterns
  currNum = currNum + 1;
  if (currNum > 9) {
    currNum = 0;
  }

  int mask = 0011;
  for (int thisPin = 5; thisPin < 14; thisPin++)  {
    int pinval = LOW;
    if (numPatterns[currNum] & mask) pinval = HIGH;
    digitalWrite(thisPin, pinval );      
    mask << 1;
  }
  sensorValueA0 = analogRead(sensorPin);
  delay(sensorValueA0); // make this read an analog pin for value  
}
