#include "../include/BuzzerManager.h"

void buzzerTone(void *pvParameters)
{
    for (;;)
    {
        if (currentAlert != NONE && buzzerEnabled)
        {
            Serial.println(F("ALERT!"));

            tone(BUZZER_PIN, 1000);
            vTaskDelay(pdMS_TO_TICKS(500));
            noTone(BUZZER_PIN);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
