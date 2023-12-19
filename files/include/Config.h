#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Bounce2.h>

const int LDR_PIN = 34;
const int BUZZER_PIN = 12;
const int LUMINOSITY_THRESHOLD = 500;
const int TEMPERATURE_LOWER_LIMIT = 10;
const int TEMPERATURE_UPPER_LIMIT = 20;
const int HUMIDITY_UPPER_LIMIT = 60;
const int BUTTON_PIN = 14;

const int LCD_ROW_TEMP = 0;
const int LCD_ROW_HUMIDITY = 1;
const int LCD_ROW_LUMINOSITY = 2;
const int LCD_ROW_ALERT = 3;

#endif
