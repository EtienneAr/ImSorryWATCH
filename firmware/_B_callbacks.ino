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
  HAL::setStaticLed(Artist::hoursToLed(Clock.getHour(h12, PM)));
  return CB_AUTO_OFF_TIME;
  
}

int displayTemperature() {
  readBME();
  HAL::setStaticLed(Artist::hoursToLed((temperature/100)%10));
  return CB_AUTO_OFF_TIME;
}

int displayHumidity() {
  readBME();
  HAL::setStaticLed(Artist::hoursToLed((humidity/100)%10));
  return CB_AUTO_OFF_TIME;
}