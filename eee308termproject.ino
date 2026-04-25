#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define DHTPIN 7
#define DHTTYPE DHT11
#define LEDPIN 8

// LCD address
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor objects
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

// LED temperature threshold
float temperatureThreshold = 20.0;

// BMP280 detected?
bool bmpAvailable = false;

// ---------------------------------------------------
// Prediction Module
// ---------------------------------------------------
float calculateRainProbability(float T, float RH, float atmPressure) {

  float rainProbability =
      0.55 * RH
    + 0.30 * (1013.0 - atmPressure)
    + 0.15 * (25.0 - T);

  if (rainProbability > 100.0) rainProbability = 100.0;
  if (rainProbability < 0.0) rainProbability = 0.0;

  return rainProbability;
}

// ---------------------------------------------------
// Data Logging and Serial Monitoring Module
// ---------------------------------------------------
void serialMonitoringModule(float temperature,
                            float humidity,
                            float atmPressure,
                            float rainProbability,
                            bool dhtValid,
                            bool bmpValid,
                            bool ledState) {

  Serial.println("------ DATA LOGGING MODULE ------");

  if (dhtValid) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("DHT11 Status: ERROR");
  }

  if (bmpValid) {
    Serial.print("Atmospheric Pressure: ");
    Serial.print(atmPressure);
    Serial.println(" hPa");
  } else {
    Serial.println("BMP280 Status: ERROR");
  }

  if (dhtValid && bmpValid) {
    Serial.print("Rain Probability: ");
    Serial.print(rainProbability);
    Serial.println(" %");
  } else {
    Serial.println("Rain Probability: NOT CALCULATED");
  }

  Serial.print("LED Alert Status: ");
  if (ledState) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.println("---------------------------------");
  Serial.println();
}

// ---------------------------------------------------
// Serial Plotter Module
// ---------------------------------------------------
void serialPlotterModule(float temperature,
                         float humidity,
                         float atmPressure,
                         float rainProbability,
                         bool dhtValid,
                         bool bmpValid) {

  if (dhtValid && bmpValid) {
    Serial.print("Temp:");
    Serial.print(temperature);
    Serial.print(",");

    Serial.print("Humidity:");
    Serial.print(humidity);
    Serial.print(",");

    Serial.print("Pressure:");
    Serial.print(atmPressure);
    Serial.print(",");

    Serial.print("Rain:");
    Serial.println(rainProbability);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  dht.begin();
  Wire.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Start");
  lcd.setCursor(0, 1);
  lcd.print("Checking...");

  // ---------------------------------------------------
  // BMP280 ADDRESS DETECTION (EKLENEN KISIM)
  // ---------------------------------------------------
  if (bmp.begin(0x76)) {
    Serial.println("BMP280 found at address 0x76");
    bmpAvailable = true;
  } else if (bmp.begin(0x77)) {
    Serial.println("BMP280 found at address 0x77");
    bmpAvailable = true;
  } else {
    Serial.println("BMP280 NOT FOUND");
    bmpAvailable = false;
  }

  delay(2000);
  lcd.clear();
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  float atmPressure = 0.0;

  bool dhtValid = true;
  bool bmpValid = false;

  if (isnan(humidity) || isnan(temperature)) {
    dhtValid = false;
  }

  if (bmpAvailable) {
    atmPressure = bmp.readPressure() / 100.0;

    if (atmPressure >= 900.0 && atmPressure <= 1100.0) {
      bmpValid = true;
    } else {
      bmpValid = false;
    }
  }

  if (dhtValid && temperature > temperatureThreshold) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  bool ledState = digitalRead(LEDPIN);

  float rainProbability = 0.0;

  if (dhtValid && bmpValid) {
    rainProbability = calculateRainProbability(
      temperature,
      humidity,
      atmPressure
    );
  }

  serialMonitoringModule(
    temperature,
    humidity,
    atmPressure,
    rainProbability,
    dhtValid,
    bmpValid,
    ledState
  );

  serialPlotterModule(
    temperature,
    humidity,
    atmPressure,
    rainProbability,
    dhtValid,
    bmpValid
  );

  lcd.clear();

  if (dhtValid) {
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(9, 0);
    lcd.print("H:");
    lcd.print(humidity, 0);
    lcd.print("%");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("DHT11 Error");
  }

  if (bmpValid) {
    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(atmPressure, 1);
    lcd.print("hPa");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("BMP280 Error");
  }

  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Rain Prob:");

  lcd.setCursor(0, 1);

  if (dhtValid && bmpValid) {
    lcd.print(rainProbability, 1);
    lcd.print("%");
  } else {
    lcd.print("Sensor Error");
  }

  delay(2000);
}