#include "../include/SensorManager.h"

DHT dht(23, DHT22);

void readSensors(void *pvParameters)
{
    for (;;)
    {
        if (systemState == ALARM_ENABLED)
        {
            // Read LDR
            sensorValues.luminosity = analogRead(LDR_PIN);

            if (isnan(sensorValues.luminosity))
            {
                Serial.println(F("Failed to read from LDR sensor!"));
            }

            // Read DHT
            float newHumidity = dht.readHumidity();
            float newTemperature = dht.readTemperature();

            if (!isnan(newHumidity) && !isnan(newTemperature))
            {
                sensorValues.humidity = newHumidity;
                sensorValues.temperature = newTemperature;
            }
            else
            {
                Serial.println("Failed to read from DHT sensor!");
            }

            xSemaphoreTake(xMutex, portMAX_DELAY);
            
            if (sensorValues.luminosity < LUMINOSITY_THRESHOLD)
            {
                currentAlert = LUMINOSITY;
            }
            else if (sensorValues.temperature < TEMPERATURE_LOWER_LIMIT || sensorValues.temperature > TEMPERATURE_UPPER_LIMIT || sensorValues.humidity > HUMIDITY_UPPER_LIMIT)
            {
                currentAlert = (sensorValues.temperature < TEMPERATURE_LOWER_LIMIT || sensorValues.temperature > TEMPERATURE_UPPER_LIMIT) ? TEMPERATURE : HUMIDITY;
            }
            else
            {
                currentAlert = NONE;
            }
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
