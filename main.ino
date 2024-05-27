#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
#include <map>

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
  lcd.print("Temp: " + String(temperature, 1));
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

void setup() 
{
  Serial.begin(115200);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(BUZZERPIN, OUTPUT);

  debouncer.attach(BUTTONPIN, INPUT_PULLUP);
  debouncer.interval(5);
}

void loop() 
{
  readSensors();
  checkAlerts();
  updateLCD();
  handleBuzzer();
  debouncer.update();
}
