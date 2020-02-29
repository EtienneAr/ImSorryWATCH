pageCb buttonAcb[] = {displayTime, decimalTest, blinkTest};
#define callbackA_N 3

void setupRTC() {
  Wire.begin();
}

void setup() {
  Serial.begin(115200);
  
  setupRTC();
  
  HAL::init();
  
  Browser::init();
  Browser::setPagesCallbacks(buttonAcb, callbackA_N);
}

void loop() {
  Browser::spinOnce();
}
