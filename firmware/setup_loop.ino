pageCb buttonAcb[] = {displayTime, displayDate, blinkTest};
#define callbackA_N 3

pageCb buttonBcb[] = {static1, static2, static3};
#define callbackB_N 3

void setup() {
  Serial.begin(115200);

  HAL::init();

  HAL::setStaticLed(0xFFF);
  HAL::setLastLedNumber(1);
  delay(1000);

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
