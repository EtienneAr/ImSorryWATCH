#ifndef HAL_HPP
#define HAL_HPP

#include <stdint.h>
#include <Arduino.h>

void HAL_init();

void HAL_applyLed(uint16_t config);
#endif