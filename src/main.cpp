#include <Arduino.h>
/* Sample code to use a relay board as an H bridge to control
 *  an actuator.
 * 
 * Progressive Automations, July 2015
 * 
 * This example code is in the public domain
 */
 
const int PINA = 2;
const int PINB = 15;//assign relay INx pin to arduino pin

void setup() {
  Serial.begin(9600);
  // Serial.begin(115200);
  pinMode(PINA, OUTPUT);//set relay as an output
  pinMode(PINB, OUTPUT);//set relay as an output

}

void loop() {

  digitalWrite(PINA, LOW);
  digitalWrite(PINB, HIGH);
  Serial.println("FWD");
  delay(2000);

  digitalWrite(PINA, LOW);
  digitalWrite(PINB, LOW);
  Serial.println("STOP");
  delay(10000);

  digitalWrite(PINA, HIGH);
  digitalWrite(PINB, LOW);
  Serial.println("FWD");
  delay(2000);

  digitalWrite(PINA, LOW);
  digitalWrite(PINB, LOW);
  Serial.println("STOP");
  delay(10000);

}