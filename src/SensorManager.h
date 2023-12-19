#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>
#include <Bounce2.h>
#include "Config.h"

struct SensorData
{
    float temperature;
    float humidity;
    int luminosity;
};

extern SensorData sensorValues;
extern SemaphoreHandle_t xMutex;
extern SystemState systemState;

void readSensors(void *pvParameters);

#endif 
