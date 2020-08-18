pageCb buttonAcb[] = {displayTime};
#define callbackA_N 1

pageCb buttonBcb[] = {displayTemperature, displayHumidity};
#define callbackB_N 2

void setup() {
  HAL::init();

  for(int i=0;i<12;i++) {
    HAL::setStaticLed(1<<i);
    HAL::setLastLedNumber(1);
    delay(180);
  }

  Button::init(PIN_BUTTON_A, PIN_BUTTON_B);

  setupI2CDevices();

  setTimeRTC();
  
  Browser::init();

  Browser::setPagesCallbacksA(buttonAcb, callbackA_N);
  Browser::setPagesCallbacksB(buttonBcb, callbackB_N);

  HAL::off();
}

void loop() {
  Browser::spinOnce();
}
