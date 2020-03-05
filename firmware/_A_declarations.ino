#include "src/HAL.hpp"
#include "src/artist.hpp"
#include "src/browser.hpp"
#include <avr/sleep.h>

#include <Wire.h>

#include "DS3231.h"
DS3231 Clock;

#include <BME280.h>  // Include the BME280 Sensor library
BME280_Class   BME280;