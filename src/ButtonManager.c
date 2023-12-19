#include "ButtonManager.h"

void buttonTask(void *pvParameters)
{
    for (;;)
    {
        if (debouncer.update())
        {
            if (debouncer.fell())
            {
                systemState = (systemState == ALARM_ENABLED) ? ALARM_DISABLED : ALARM_ENABLED;

                xSemaphoreTake(xMutex, portMAX_DELAY);
                buzzerEnabled = (systemState == ALARM_ENABLED);
                xSemaphoreGive(xMutex);

                if (!buzzerEnabled) {noTone(BUZZER_PIN);}
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
