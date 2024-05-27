#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Bounce2.h>

enum AlertType
{
    NONE,
    TEMPERATURE,
    HUMIDITY,
    LUMINOSITY
};

enum SystemState
{
    ALARM_ENABLED,
    ALARM_DISABLED
};

const char* getAlertString(AlertType alert)
{
    switch (alert)
    {
        case NONE:
            return "None ";

        case TEMPERATURE:
            return "Temperature ";

        case HUMIDITY:
            return "Humidity ";

        case LUMINOSITY:
            return "Luminosity ";

        default:
            return "Unknown ";
    }
}

struct SensorData
{
    float temperature;
    float humidity;
    int luminosity;
};

SensorData sensorValues;

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

bool buzzerEnabled = true;

AlertType currentAlert = NONE;
AlertType previousAlert = NONE;

DHT dht(23, DHT22);
LiquidCrystal_I2C lcd(0x27, 20, 4);

Bounce debouncer = Bounce();
SemaphoreHandle_t xMutex;
TaskHandle_t buzzerTaskHandle;
SystemState systemState = ALARM_ENABLED;

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

void displayTask(void *pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);

        // Limpa completamente a linha "Alert" antes de atualizar
        lcd.setCursor(7, LCD_ROW_ALERT);
        lcd.print("                  ");

        // Define os rótulos e valores para exibição
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

                if (!buzzerEnabled)
                {
                    noTone(BUZZER_PIN);
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void setup()
{
    ledcSetup(0, 1000, 10);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    Serial.begin(9600);

    dht.begin();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);

    xMutex = xSemaphoreCreateMutex();

    xTaskCreatePinnedToCore(readSensors, "TaskReadSensors", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(buzzerTone, "TaskBuzzerTone", 10000, NULL, 1, &buzzerTaskHandle, 0);
    xTaskCreatePinnedToCore(displayTask, "TaskDisplay", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(buttonTask, "TaskButton", 10000, NULL, 1, NULL, 0);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    debouncer.attach(BUTTON_PIN);
    debouncer.interval(50);
}

void loop(){}
