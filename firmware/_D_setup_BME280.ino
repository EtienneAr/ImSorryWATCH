void setupBME280() {
	while (!BME280.begin()) { delay(500); }

	BME280.setOversampling(TemperatureSensor,Oversample1);
	BME280.setOversampling(HumiditySensor,Oversample1);
	BME280.setOversampling(PressureSensor,Oversample16);

	BME280.mode(SleepMode);
}