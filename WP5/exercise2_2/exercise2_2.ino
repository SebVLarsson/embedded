// File: exercise2_2.ino

/* 
 * WP5 - Exercise 2_2
 * John Dickson, Oliver Hansson, Sebastian VingÃ¥rd Larsson
 * 2026-03-XX
 * group: 27
 * Submission code: XXXXXX
 */

#include "DHT.h" // dht library

// define DHT pins and type
#define DHTPIN 12
#define DHTTYPE DHT11

// light sensor pins
#define LDRPIN A0

// LED pins
#define LED1 5
#define LED2 7
#define LED3 9

// temperature thresholds/levels
#define TEMP_LEVEL_1 0
#define TEMP_LEVEL_2 24
#define TEMP_LEVEL_3 30

// light thresholds/levels
#define LIGHT_LEVEL_1 35
#define LIGHT_LEVEL_2 31
#define LIGHT_LEVEL_3 26

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
  
  // start dht
  dht.begin();
}

void loop() {
  // because dht11 is old and not really natively compatible to R4
  // we need to delay at the start to ensure everything is runnning before we start reading
  delay(3000);

  // read temperature
  float temp = dht.readTemperature();
  int lightValue = analogRead(LDRPIN);

  // check if temp is null
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // print temp and lightValue to serial
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println(lightValue);

  // reset LEDs
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW);


  /*
   * In hindsight the logic here is abit messy
   * Primarily because of the inverted logic between light and temperature
   * Since darker = greater and lighter = lesser with light and the opposite for temperature
   * It works as intended but could for sure be refactored without return statements etc.
  */
  
  // if temp is lower and light is greater than level 1 
  // GREEN
  if (temp < TEMP_LEVEL_1 && lightValue > LIGHT_LEVEL_1) {
    digitalWrite(LED2, HIGH);
    return; // return to restart loop
  }
  // if temp is equal or greater than 1 but lower than 2 and light is equal or lesser than level 1 but greater than level 2
  // GREEN
  else if ((temp >= TEMP_LEVEL_1 && temp < TEMP_LEVEL_2) && (lightValue <= LIGHT_LEVEL_1 && lightValue > LIGHT_LEVEL_2)) {
    digitalWrite(LED2, HIGH);
    return; // return to restart loop
  }
  // if temp is equal or greater than 2 but less than 3 and light is equal or lesser to level 2 but greater than level 3
  // GREEN
  else if ((temp >= TEMP_LEVEL_2 && temp < TEMP_LEVEL_3) && (lightValue <= LIGHT_LEVEL_2 && lightValue > LIGHT_LEVEL_3)) { 
    digitalWrite(LED2, HIGH);
    return; // return to restart loop
  }
  // if temp is equal or greater than 3 and light is equal or lower than 3
  // GREEN
  else if (temp >= TEMP_LEVEL_3 && lightValue <= LIGHT_LEVEL_3) {
    digitalWrite(LED2, HIGH);
    return; // return to restart loop
  }

  // if light value is greater than 1 (very dark) but temperature is higher than level 1
  // RED (too warm)
  if (lightValue > LIGHT_LEVEL_1 && temp > TEMP_LEVEL_1) {
    digitalWrite(LED3, HIGH);
    return; // return to restart loop
  }
  //if lightvalue is less or equal to 1 but greater than 2
  else if (lightValue <= LIGHT_LEVEL_1 && lightValue > LIGHT_LEVEL_2) {
    // if temp is less than 1
    // BLUE (too cold)
    if (temp < TEMP_LEVEL_1) {
      digitalWrite(LED1, HIGH);
      return; // return to restart loop
    }
    // if temp is greater or equal to 2
    // RED (too warm)
    else if (temp >= TEMP_LEVEL_2) {
      digitalWrite(LED3, HIGH); 
      return; // return to restart loop
    }
  }
  // if light value is equal or lesser than 2 but greater than 3
  else if (lightValue <= LIGHT_LEVEL_2 && lightValue > LIGHT_LEVEL_3) {
    // temp is lesser than 2
    // BLUE (too cold)
    if (temp < TEMP_LEVEL_2) {
      digitalWrite(LED1, HIGH);
      return; // return to restart loop
    }
    // temp greater than 3
    // RED (too warm)
    else if (temp > TEMP_LEVEL_3) {
      digitalWrite(LED3, HIGH);
      return; // return to restart loop
    }
  }
  // if light value is greater or equal to 3 and temp is less than 3 (highest level)
  // BLUE (too cold)
  else if (lightValue <= LIGHT_LEVEL_3 && temp < TEMP_LEVEL_3) {
    digitalWrite(LED1, HIGH);
    // no need to return here since its the last statement of the loop
  }
}