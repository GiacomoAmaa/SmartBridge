#include "SmartLight.h"
#include "Arduino.h"

SmartLight::SmartLight(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void SmartLight::switchOn(){
  digitalWrite(pin,HIGH);
}

void SmartLight::switchOff(){
  digitalWrite(pin,LOW);
};