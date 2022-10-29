//#define IS_PS3
#define IS_PS4

// external headers
#include "esp_task_wdt.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <Arduino.h>
#include "Preferences.h"
#include <ArduinoJson.h>

#include "esp_camera.h"
#include <base64.h>

// internal headers
#include "parameters_state.h"
#include "parameters_camera.h"
#include "parameters_led.h"

// define permanent flash object
Preferences preferences;


int DEBUG = 1; // if tihs is set to true, the arduino runs into problems during multiple serial prints..
#define BAUDRATE 115200


DynamicJsonDocument jsonDocument(32784);

char output[1000];

/* --------------------------------------------
   Setup
  --------------------------------------------
*/
void setup()
{
  /*
     SETTING UP DEVICES
  */
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  // for any timing related puposes..
  startMillis = millis();

  // Start Serial
  Serial.begin(BAUDRATE);
  Serial.println("Start");



  // display state
  printInfo();

  // reset jsonDocument
  jsonDocument.clear();


  Serial.println(state_act_endpoint);
  Serial.println(state_get_endpoint);
  Serial.println(state_set_endpoint);

  setup_camera();
  setup_led();

}


void loop() {
  
  // for any timing-related purposes
  currentMillis = millis();

  // process incoming serial commands
  if (Serial.available()) {
    DeserializationError error = deserializeJson(jsonDocument, Serial);
    //free(Serial);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    Serial.flush();
    if (DEBUG) serializeJsonPretty(jsonDocument, Serial);

    String task_s = jsonDocument["task"];
    char task[50];
    task_s.toCharArray(task, 256);

    if (DEBUG) {
      Serial.print("TASK: ");
      Serial.println(task);
    }

      jsonProcessor(task);
  }

}


void jsonProcessor(char task[]) {
  /*
      Return state
  */
  if (strcmp(task, state_act_endpoint) == 0)
    state_act_fct();
  if (strcmp(task, state_set_endpoint) == 0)
    state_set_fct();
  if (strcmp(task, state_get_endpoint) == 0)
    state_get_fct();

  /*
    Drive Cameras
  */
  if (strcmp(task, camera_act_endpoint) == 0) {
    camera_act_fct();
  }
  if (strcmp(task, camera_set_endpoint) == 0) {
    camera_set_fct();
  }
  if (strcmp(task, camera_get_endpoint) == 0) {
    camera_get_fct();
  }

  /*
    Drive LEDs
  */
  if (strcmp(task, led_act_endpoint) == 0) {
    led_act_fct();
  }
  if (strcmp(task, led_set_endpoint) == 0) {
    led_set_fct();
  }
  if (strcmp(task, led_get_endpoint) == 0) {
    led_get_fct();
  }
}
