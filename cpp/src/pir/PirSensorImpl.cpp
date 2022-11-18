#include "pir/PirSensorImpl.h"

PirSensorImpl::PirSensorImpl(int pin){
  this->pin = pin;
  this->detectedStatus = false;
  pinMode(pin,INPUT);
  this->calibrate();
}

bool PirSensorImpl::detect(){
  int current = digitalRead(pin);
  if (current != detectedStatus ){
    detectedStatus = current;
    current ? Serial.println("detected!"): Serial.println("no more detected.");
  }
}

void PirSensorImpl::calibrate(){
  Serial.print("Calibrating sensor... ");
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("PIR SENSOR READY.");
}