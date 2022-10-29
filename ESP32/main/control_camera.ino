// Custom function accessible by the API
void camera_act_fct() {
  if (DEBUG) Serial.println("camera_act_fct");


  // assign default values to thhe variables
  if (jsonDocument.containsKey("grabimage")) {
    for (int iframe = 0; iframe < 5; iframe++) {
      // free frame buffer and adjust brightnesssetu
      camera_fb_t* fb = esp_camera_fb_get();
      esp_camera_fb_return(fb);
    }

    if (!fb || fb->format != PIXFORMAT_JPEG) {
    } else {
      delay(40);

      Serial.println("++");
      Serial.print("{'frame': '");
      String encoded = base64::encode(fb->buf, fb->len);
      esp_camera_fb_return(fb);
      Serial.write(encoded.c_str(), encoded.length());
      Serial.println("'}");
      Serial.println("--");
      Serial.println();
    }
    jsonDocument.clear();
    jsonDocument["return"] = 1;
  }
}


void camera_set_fct() {


  // default value handling
  int axis = -1;
  if (jsonDocument.containsKey("axis")) {
    int axis = jsonDocument["axis"];
  }
}



// Custom function accessible by the API
void camera_get_fct() {
}


void setup_camera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA; //320x240
  config.jpeg_quality = 10;
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {

    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  s->set_hmirror(s, 1);
  s->set_vflip(s, 1);
}
