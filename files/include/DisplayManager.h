#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>
#include "SensorManager.h"

extern LiquidCrystal_I2C lcd;

void printLabelValue(const char* label, float value, int row);
void displayTask(void *pvParameters);

#endif 
