#include <avr/sleep.h>  //this AVR library contains the methods that controls the sleep modes

bool h12;
bool PM;

void suspend(void) {
  Browser::pointersReset();
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sleep_bod_disable();
  sei();
  sleep_cpu();
}

void displayTime() {
  HAL::on();
  HAL::setLastLedNumber(1);
  HAL::setStaticLed(Artist::minutesToLed(Clock.getMinute()));
  HAL::setBlinkingLed(Artist::hoursToLed(Clock.getHour(h12, PM)));
  HAL::auto_off(3000, suspend);
}

void decimalTest() {
  HAL::on();
  int dec = random(198);
  HAL::setCombinedLed(Artist::decimalToLed(dec-99));
  Serial.println(dec-99);
  HAL::auto_off(-1);
}


void blinkTest() {
  HAL::on();
  HAL::setStaticLed(0x555);
  HAL::setBlinkingLed(0xFFF);
  HAL::setLastLedNumber(2);
  HAL::auto_off(3000, suspend);
}