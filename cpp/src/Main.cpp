#include "led/LedPowerTask.h"
#include "light_sensor/LightCheckTask.h"
#include "pir/PirCheckTask.h"
#include "servo/ServoControlTask.h"
#include "sonar/SonarCheckTask.h"
#include "potentiometer/Potentiometer.h"
#include "button/Button.h"
#include "lcd/LCD.h"
#include "scheduler/Scheduler.h"
#include "utility/AlarmState.h"
#include "Arduino.h"

#define BASE_PERIOD 20

#define NUM_LEDS 3

#define LED_A_PIN 13
#define LED_B_PIN 12
#define LED_C_PIN 11
#define SERVO_PIN 9
#define SONAR_ECHO_PIN 4
#define SONAR_TRIG_PIN 3
#define PIR_PIN 2
#define BUTTON_PIN 1
#define LIGHT_PIN A0
#define POTENTIOMETER_PIN A1

Scheduler taskmgr;

void setup(){
    AlarmState state = NORMAL;
    int leds[NUM_LEDS];

    Potentiometer* pot = new Potentiometer(POTENTIOMETER_PIN);
    Button* button = new Button(BUTTON_PIN);
    LCD* lcd = new LCD();

    leds[0] = LED_A_PIN;
    leds[1] = LED_B_PIN;
    leds[2] = LED_C_PIN;

    SonarCheckTask* sonartask = new SonarCheckTask(&state, SONAR_TRIG_PIN, SONAR_ECHO_PIN);
    ServoControlTask* servotask = new ServoControlTask(&state, SERVO_PIN);
    LedPowerTask* ledtask = new LedPowerTask(&state, leds, NUM_LEDS);
    LightCheckTask* lighttask = new LightCheckTask(LIGHT_PIN);
    PirCheckTask* pirtask = new PirCheckTask(PIR_PIN);

    taskmgr.init(BASE_PERIOD);
    servotask->init(BASE_PERIOD, sonartask, button, pot);
    ledtask->init(BASE_PERIOD, lighttask, pirtask);
    lighttask->init(BASE_PERIOD);
    pirtask->init(BASE_PERIOD);
    sonartask->init(lcd);

    taskmgr.addTask(lighttask);
    taskmgr.addTask(pirtask);
    taskmgr.addTask(sonartask);
    taskmgr.addTask(servotask);
    taskmgr.addTask(ledtask);
}

void loop(){
    taskmgr.schedule();
    Serial.println();
}