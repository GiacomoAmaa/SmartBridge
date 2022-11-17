#include "led/Led.h"

Led::Led(int pin){
    this->pin = pin;
    this->lightIntensity = MIN_LED_INTENSITY;
}

bool Led::isOn() {
    return lightIntensity > MIN_LED_INTENSITY;
}

bool Led::isOff() {
    return lightIntensity <= MIN_LED_INTENSITY;
}

int Led::getCurrIntensity() {
    return lightIntensity;
}

int Led::getPin() {
    return pin;
}

void Led::turnOn() {
    lightIntensity = MAX_LED_INTENSITY;
}

void Led::turnOff() {
    lightIntensity = MIN_LED_INTENSITY;
}

void Led::increaseIntensity(int intensity) {
    int newIntensity = lightIntensity + intensity;
    lightIntensity = MAX_LED_INTENSITY;
    if (newIntensity <= MAX_LED_INTENSITY) {
        lightIntensity = newIntensity;
    }
}

void Led::decreaseIntensity(int intensity) {
    int newIntensity = lightIntensity - intensity;
    lightIntensity = MIN_LED_INTENSITY;
    if (newIntensity >= MIN_LED_INTENSITY) {
        lightIntensity = newIntensity;
    }
}
