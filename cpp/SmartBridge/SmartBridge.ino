#include "LedPowerTask.h"
#include "LightCheckTask.h"
#include "PirCheckTask.h"
#include "ServoControlTask.h"
#include "SonarCheckTask.h"
#include "Potentiometer.h"
#include "Button.h"
#include "LCDTask.h"
#include "Scheduler.h"
#include "AlarmState.h"
#include "Arduino.h"
#include "Config.h"

Scheduler taskmgr;
AlarmState state;

/**
* Prints on serial line the current allarm status.
*/
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

    SonarCheckTask* sonartask = new SonarCheckTask(&state, SONAR_TRIG_PIN, SONAR_ECHO_PIN);
    ServoControlTask* servotask = new ServoControlTask(&state, SERVO_PIN);
    LedPowerTask* ledtask = new LedPowerTask(&state, leds, NUM_LEDS);
    LightCheckTask* lighttask = new LightCheckTask(LIGHT_PIN);
    PirCheckTask* pirtask = new PirCheckTask(PIR_PIN);
    LCDTask* lcd = new LCDTask();

    taskmgr.init(BASE_PERIOD);
    servotask->init(BASE_PERIOD, sonartask, button, pot, lcd);
    ledtask->init(BASE_PERIOD, lighttask, pirtask);
    sonartask->init(BASE_PERIOD, lcd);
    lighttask->init(BASE_PERIOD);
    pirtask->init(BASE_PERIOD);
    lcd->init(BASE_PERIOD);

    taskmgr.addTask(lighttask);
    taskmgr.addTask(pirtask);
    taskmgr.addTask(sonartask);
    taskmgr.addTask(servotask);
    taskmgr.addTask(ledtask);
    taskmgr.addTask(lcd);

    Serial.println();
}

void loop(){
    printAlarmState();
    taskmgr.schedule();
    Serial.println();
}