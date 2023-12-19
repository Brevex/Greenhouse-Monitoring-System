#include "Config.h"
#include "SensorManager.h"
#include "DisplayManager.h"
#include "BuzzerManager.h"
#include "ButtonManager.h"

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
