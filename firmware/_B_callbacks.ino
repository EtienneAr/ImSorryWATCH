bool h12;
bool PM;

int displayTime() {
  HAL::setStaticLed(Artist::minutesToLed(Clock.getMinute()));
  HAL::setBlinkingLed(Artist::hoursToLed(Clock.getHour(h12, PM)));
  return 3000;
  
}

int displayDate() {
  HAL::setCombinedLed(Artist::decimalToLed(Clock.getDate()));
  return 3000;
}


void blinkTest() {
  HAL::setStaticLed(0x555);
  HAL::setBlinkingLed(0xFFF);
}