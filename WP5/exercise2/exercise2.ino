// File: exercise2.ino

/* 
 * WP5 - Exercise 2
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-03-XX
 * group: 27
 * Submission code: XXXXXX
 */

#include "DHT.h" // dht library

// define DHT pins and type
#define DHTPIN 12
#define DHTTYPE DHT11

// LED pins
#define LED1 3
#define LED2 5
#define LED3 7
#define LED4 9
#define LED5 11

// temperature thresholds for amount of LEDs to light
#define TEMP_LEVEL_1 0
#define TEMP_LEVEL_2 7
#define TEMP_LEVEL_3 15
#define TEMP_LEVEL_4 22
#define TEMP_LEVEL_5 30

// initialize and create our dht
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // begin serial monitor
  Serial.begin(9600);
  // because R4 is uncompatible natively with some of our parts
  // we're making sure that everything is running before we continue, here its serial
  while (!Serial); 
  
  // set pinmode for LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  
  // start dht
  dht.begin();
}

void loop() {
  // because dht11 is old and not really natively compatible to R4
  // we need to delay at the start to ensure everything is runnning before we start reading
  delay(3000);

  // read temperature
  float temp = dht.readTemperature();

  // check if temp is null
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // print temp to serial
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  // reset LEDs
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW); 
  digitalWrite(LED5, LOW);

  // checking how many LEDs to light depending on temperature
  if (temp > TEMP_LEVEL_1) digitalWrite(LED1, HIGH);
  if (temp > TEMP_LEVEL_2) digitalWrite(LED2, HIGH);
  if (temp > TEMP_LEVEL_3) digitalWrite(LED3, HIGH);
  if (temp > TEMP_LEVEL_4) digitalWrite(LED4, HIGH);
  if (temp > TEMP_LEVEL_5) digitalWrite(LED5, HIGH);
}