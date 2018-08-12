/*
  Lightbox
  For putting inside a peace sign pumpkin
  general purpose blinking light 
  joadavis 29 Oct 2016
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led13 = 13;
int led12 = 12;
int led11 = 11;
int led10 = 10;
int count = 4;

int sensorPin = A0;
int sensorValueA0 = 0;     




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

  sensorValueA0 = analogRead(sensorPin);
  delay(sensorValueA0 * 2); // make this read an analog pin for value 

  for (int thisPin = 4; thisPin < 14; thisPin++)  {
    // more on than off
    int va = random(3);
    if (va > 1) va = 1;
    digitalWrite(thisPin, va);      
  }
  //delay(1000); // make this read an analog pin for value  
}
