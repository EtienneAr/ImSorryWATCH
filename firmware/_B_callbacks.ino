#define CB_AUTO_OFF_TIME 5000

bool h12;
bool PM;

int displayTime() {
  HAL::setStaticLed(Artist::minutesToLed(Clock.getMinute()));
  HAL::setBlinkingLed(Artist::hoursToLed(Clock.getHour(h12, PM)));
  return CB_AUTO_OFF_TIME;
  
}

int displayDate() {
  HAL::setCombinedLed(Artist::decimalToLed(Clock.getDate()));
  return CB_AUTO_OFF_TIME;
}


int blinkTest() {
  HAL::setStaticLed(0x555);
  HAL::setBlinkingLed(0xFFF);
  return CB_AUTO_OFF_TIME;
}

int static1() {
  HAL::setStaticLed(0b000000001111);
  return CB_AUTO_OFF_TIME;
}

int static2() {
  HAL::setStaticLed(0b000011111111);
  return CB_AUTO_OFF_TIME;
}

int static3() {
  HAL::setStaticLed(0b111111111111);
  return CB_AUTO_OFF_TIME;
}