bool h12;
bool PM;

#define SEA_LEVEL 1013.25
unsigned long BME_lastMeasure_ms = 0;
int32_t temperature, humidity, pressure;
float altitude;

inline void readBME() {
	if(millis() - BME_lastMeasure_ms < BME_MEASURE_MIN_INT_MS) return;
	BME_lastMeasure_ms = millis();
	
  BME280.mode(ForcedMode);
	BME280.getSensorData(temperature,humidity,pressure); // Get most recent readings
  BME280.mode(SleepMode);
  altitude = 44330.0*(1.0 - pow(((float)pressure / 100.0) / SEA_LEVEL, 0.1903));
}

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

int displayTemperature() {
  readBME();
  HAL::setCombinedLed(Artist::decimalToLed(temperature/100));
  return CB_AUTO_OFF_TIME;
}

int displayHumidity() {
  readBME();
  HAL::setCombinedLed(Artist::decimalToLed(humidity/100));
  return CB_AUTO_OFF_TIME;
}

int displayPressure() {
  readBME();
  //Do something here
  //HAL::setCombinedLed(Artist::decimalToLed(pressure));
  return CB_AUTO_OFF_TIME;
}

int displayAltitude() {
  readBME();
  HAL::setBlinkingLed(0);
  HAL::setStaticLed(int(altitude));
  Serial.println(altitude);
  return CB_AUTO_OFF_TIME;
}