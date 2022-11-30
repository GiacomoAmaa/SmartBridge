#include "LedPowerTask.h"
#include "LightCheckTask.h"
#include "PirCheckTask.h"
#include "ServoControlTask.h"
#include "SonarCheckTask.h"
#include "Potentiometer.h"
#include "SerialCommunicationTask.h"
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
  Serial.println();
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

  int leds[NUM_LEDS] = {LED_A_PIN, LED_B_PIN, LED_C_PIN};
  state = NORMAL;

  Potentiometer* pot = new Potentiometer(POTENTIOMETER_PIN);
  Button* button = new Button(BUTTON_PIN);

  SonarCheckTask* sonarTask = new SonarCheckTask(&state, SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  ServoControlTask* servoTask = new ServoControlTask(&state, SERVO_PIN);
  LedPowerTask* ledTask = new LedPowerTask(&state, leds, NUM_LEDS);
  LightCheckTask* lightTask = new LightCheckTask(LIGHT_PIN);
  PirCheckTask* pirTask = new PirCheckTask(PIR_PIN);
  LCDTask* lcd = new LCDTask(&state);
  SerialCommunicationTask* serialComm = new SerialCommunicationTask(&state);

  taskmgr.init(BASE_PERIOD);
  servoTask->init(3 * BASE_PERIOD, sonarTask, button, pot);
  ledTask->init(BASE_PERIOD, lightTask, pirTask);
  sonarTask->init(BASE_PERIOD);
  lightTask->init(BASE_PERIOD);
  pirTask->init(2 * BASE_PERIOD);
  lcd->init(3 * BASE_PERIOD, servoTask, sonarTask);
  serialComm->init(4 * BASE_PERIOD, sonarTask, servoTask, lightTask, ledTask);

  taskmgr.addTask(lightTask);
  taskmgr.addTask(pirTask);
  taskmgr.addTask(sonarTask);
  taskmgr.addTask(serialComm);
  taskmgr.addTask(servoTask);
  taskmgr.addTask(ledTask);
  taskmgr.addTask(lcd);
}

void loop(){
  #ifdef DEBUG
    printAlarmState();
  #endif
  taskmgr.schedule();
}
