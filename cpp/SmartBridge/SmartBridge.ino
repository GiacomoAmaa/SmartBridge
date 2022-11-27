#include "LedPowerTask.h"
#include "LightCheckTask.h"
#include "PirCheckTask.h"
#include "ServoControlTask.h"
#include "SonarCheckTask.h"
#include "Potentiometer.h"
#include "Button.h"
#include "LCD.h"
#include "Scheduler.h"
#include "AlarmState.h"
#include "Arduino.h"
#include "Config.h"

Scheduler taskmgr;
AlarmState state;

void printAlarmState() {
  String msg = "NORMAL";
  if (state == PREALARM) {
    msg = "PREALARM";
  } 
  if (state == ALARM) {
    msg = "ALARM";
  }
  Serial.println("Alarm state: "+msg);
}

void setup(){
    Serial.begin(9600);
    Serial.println();
    
    int leds[NUM_LEDS] = {LED_A_PIN, LED_B_PIN, LED_C_PIN};
    state = NORMAL;

    Potentiometer* pot = new Potentiometer(POTENTIOMETER_PIN);
    Button* button = new Button(BUTTON_PIN);
    LCD* lcd = new LCD();

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
    sonartask->init(BASE_PERIOD, lcd);

    taskmgr.addTask(lighttask);
    taskmgr.addTask(pirtask);
    taskmgr.addTask(sonartask);
    taskmgr.addTask(servotask);
    taskmgr.addTask(ledtask);

    Serial.println();
}

void loop(){
    printAlarmState();
    taskmgr.schedule();
    Serial.println();
}