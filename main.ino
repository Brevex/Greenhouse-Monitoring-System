#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
#include <map>

#define WIFI_SSID       "Wokwi-GUEST" // Default Wokwi wifi login
#define WIFI_PASSWORD   ""
#define AIO_SERVER      "io.adafruit.com"
#define AIO_USERNAME    "" // Change to your respective login
#define AIO_KEY         "" // Change to your respective key
#define AIO_SERVERPORT  1883

#define DHTPIN 23
#define LDRPIN 34
#define BUZZERPIN 12
#define BUTTONPIN 14

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Bounce debouncer = Bounce();

float temperature, humidity;
int luminosity;
bool buzzerActive = false;
String alert = "none";
String previousAlert = "none";

// Change to your Adafruit.io feeds
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish luminosityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/luminosity");

struct AlertRule 
{
  float min;
  float max;
  String message;
};

std::map<String, AlertRule> alertRules = {
  {"Temperature", {10.0, 20.0, "Temperature"}},
  {"Humidity", {0.0, 60.0, "Humidity"}},
  {"Luminosity", {500.0, 1023.0, "Luminosity"}}
};

void readSensors() 
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  luminosity = analogRead(LDRPIN);

  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Failed to read from DHT sensor!");
  }
}

void checkAlerts() 
{
  alert = "none";
  buzzerActive = false;

  for (const auto& [parameter, rule] : alertRules) 
  {
    float value = parameter == "Temperature" ? temperature :
                  parameter == "Humidity" ? humidity : luminosity;

    if (value < rule.min || value > rule.max) 
    {
      alert = rule.message;
      buzzerActive = true;
      break;
    }
  }
}

void updateLCD() 
{
  lcd.setCursor(0, 0);
  lcd.print("Temperature: " + String(temperature, 1));
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(humidity, 1));
  lcd.setCursor(0, 2);
  lcd.print("Luminosity: " + String(luminosity));

  if (alert != previousAlert) 
  {
    lcd.setCursor(0, 3);
    lcd.print("Alert:                ");

    lcd.setCursor(0, 3);
    lcd.print("Alert: " + alert);

    previousAlert = alert;
  }
}

void handleBuzzer() 
{
  if (buzzerActive && debouncer.fell()) 
  {
    buzzerActive = false;
  }

  digitalWrite(BUZZERPIN, buzzerActive);
}

void connectWiFi() 
{
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" connected!");
}

void connectMQTT() 
{
  int8_t ret;

  if (mqtt.connected()) { return; }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) 
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }

  Serial.println("MQTT Connected!");
}

void setup() 
{
  Serial.begin(115200);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(BUZZERPIN, OUTPUT);

  debouncer.attach(BUTTONPIN, INPUT_PULLUP);
  debouncer.interval(5);

  connectWiFi();
  connectMQTT();
}

void loop() 
{
  readSensors();
  checkAlerts();
  updateLCD();
  handleBuzzer();
  debouncer.update();

  if (WiFi.status() != WL_CONNECTED) 
  {
    connectWiFi();
  }

  connectMQTT();

  if (!mqtt.ping()) 
  {
    mqtt.disconnect();
  }

  temperatureFeed.publish(temperature);
  humidityFeed.publish(humidity);
  luminosityFeed.publish(luminosity);
}
