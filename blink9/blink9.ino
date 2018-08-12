/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led13 = 13;
int led12 = 12;
int led11 = 11;
int count = 4;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  //pinMode(led13, OUTPUT);     
  //pinMode(led12, OUTPUT);     
  //pinMode(led11, OUTPUT);     
  
  for (int thisPin = 4; thisPin < 14; thisPin++)  {
    pinMode(thisPin, OUTPUT);      
  }
}

// the loop routine runs over and over again forever:
void loop() {
  /*digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second

  digitalWrite(led12, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led12, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second

  digitalWrite(led11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);               // wait for a second
  digitalWrite(led11, LOW);    // turn the LED off by making the voltage LOW
  delay(250);               // wait for a second
  */

  for (int thisPin = 4; thisPin < 14; thisPin++)  {
    digitalWrite(thisPin, random(2));      
  }
  delay(1000); // make this read an analog pin for value  
  
  // count up
  for (int thisPin = 4; thisPin < 14; thisPin++)  {
    digitalWrite(thisPin, thisPin < count);      
  }
  delay(1000); // make this read an analog pin for value  
  count = count + 1;
  if (count > 13) count = 4;
}
