pageCb buttonAcb[] = {displayTime, displayDate, blinkTest};
#define callbackA_N 3

void setup() {
  Serial.begin(115200);

  HAL::init();

  HAL::setStaticLed(0xFFF);
  HAL::setLastLedNumber(1);
  delay(1000);

  Button::init(PIN_BUTTON_A, PIN_BUTTON_B);

  setupRTC();
  setupBME280();

  //Setup pages only after the RTC is setup
  Browser::init();
  Browser::setPagesCallbacks(buttonAcb, callbackA_N);

  HAL::off();
}

void loop() {
  Browser::spinOnce();
}
