#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Bounce2.h>
#include "SensorManager.h"

extern Bounce debouncer;

void buttonTask(void *pvParameters);

#endif 
