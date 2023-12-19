#include "../include/DisplayManager.h"

void printLabelValue(const char* label, float value, int row)
{
    int labelLength = strlen(label);
    lcd.setCursor(0, row);
    lcd.print(label);
    lcd.print(value);

    if (row == LCD_ROW_ALERT)
    {
        lcd.setCursor(labelLength, row);
        lcd.print(getAlertString(currentAlert));
    }
}

void displayTask(void *pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);

        lcd.setCursor(7, LCD_ROW_ALERT);
        lcd.print("                  ");

        const char* labels[] = {"Temp: ", "Humidity: ", "Luminosity: ", "Alert: "};
        float values[] = {sensorValues.temperature, sensorValues.humidity, sensorValues.luminosity, static_cast<float>(currentAlert)};

        for (int i = 0; i < 4; ++i)
        {
            printLabelValue(labels[i], values[i], i);
        }

        xSemaphoreGive(xMutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
