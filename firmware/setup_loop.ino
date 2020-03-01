pageCb buttonAcb[] = {displayTime, decimalTest, blinkTest};
#define callbackA_N 3

void setup() {
  Serial.begin(115200);
  
  HAL::init();

  setupRTC();
  
  //Setup pages only after the RTC is setup
  Browser::init(PIN_BUTTON_A, PIN_BUTTON_B);
  Browser::setPagesCallbacks(buttonAcb, callbackA_N);
}

void loop() {
  Browser::spinOnce();
}
