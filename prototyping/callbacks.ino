bool h12;
bool PM;

void displayTime() {
  Serial.println("Display time");
  HAL::on();
  HAL::setLastLedNumber(1);
  HAL::applyLed(minutesToLed(Clock.getMinute()));
  HAL::setBlinkingLed(hoursToLed(Clock.getHour(h12, PM)));
}

void blinkTest() {
  Serial.println("blinkTest");
  HAL::on();
  HAL::applyLed(0x555);
  HAL::setBlinkingLed(0xFFF);
  HAL::setLastLedNumber(2);
  HAL::auto_off(3000, Browser::pointersReset);
}