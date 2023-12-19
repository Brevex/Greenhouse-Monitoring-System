#ifndef BUZZER_MANAGER_H
#define BUZZER_MANAGER_H

#include <Bounce2.h>
#include "SensorManager.h"

extern TaskHandle_t buzzerTaskHandle;

void buzzerTone(void *pvParameters);

#endif
