#include "parameters_led.h"
// Custom function accessible by the API
void led_act_fct() {
  if (DEBUG) Serial.println("led_act_fct");


  // assign default values to thhe variables
  if (jsonDocument.containsKey("value")) {
    ledcWrite(LED_PWM_CHANNEL, jsonDocument["value"]);

  }
    jsonDocument.clear();   
}

void led_set_fct() {
  // default value handling
}

// Custom function accessible by the API
void led_get_fct() {
}

void setup_led() {
    ledcSetup(LED_PWM_CHANNEL, LED_PWM_FREQ, LED_PWM_RESOLUTION);
    ledcAttachPin(LED_GPIO_NUM, LED_PWM_CHANNEL);
}
