void setupI2CDevices() {
	Wire.begin();
	
	while (!BME280.begin()) { delay(500); }

	BME280.setOversampling(TemperatureSensor,Oversample4);
	BME280.setOversampling(HumiditySensor,Oversample4);
	BME280.setOversampling(PressureSensor,Oversample16);

	BME280.mode(SleepMode);
}