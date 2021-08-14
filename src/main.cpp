#include "RpiFunctions.hpp"

#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

#define SDA 21
#define SCL 22

const int16_t i2c_esp32=0x04;
 
const int PINA = 2;
const int PINB = 15;

const int MOTOR_STOP = 0x00;
const int MOTOR_FORWARD = 0x01;
const int MOTOR_BACKWARD = 0x02;

uint8_t motorState[1] = {MOTOR_STOP};

void updateLinearActuator(void* param) {
  for (;;) {
    Rpi::updateWire();
    Serial.println(motorState[0]);
    switch(motorState[0]) {
      case MOTOR_FORWARD:
        digitalWrite(PINA, LOW);
        digitalWrite(PINB, HIGH);
        break;
      case MOTOR_BACKWARD:
        digitalWrite(PINA, HIGH);
        digitalWrite(PINB, LOW);
        break;
      case MOTOR_STOP:
      default:
        digitalWrite(PINA, LOW);
        digitalWrite(PINB, LOW);
        break;
    }
    vTaskDelay(10);
  }
}

void readString(uint8_t registerCode, int howMany, uint8_t* data) {
  switch(registerCode) {
    case 0x01: {
      motorState[0] = data[0];
      break;
    }
  }
}

int readReqHandler(uint8_t registerCode, uint8_t* &data) {
  switch(registerCode) {
    case 0x01: {
      data = motorState;
      return 1;
    }
    default: {
      return 0;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PINA, OUTPUT);
  pinMode(PINB, OUTPUT);
  Rpi::initWireSlave(SDA, SCL, i2c_esp32);
  Rpi::registerReceiveRequest(readString);
  Rpi::registerReadRequest(readReqHandler);
  xTaskCreate(&updateLinearActuator, "actuatortask", 1000, NULL, 0, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}
