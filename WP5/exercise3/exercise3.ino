// File: exercise3.ino

/* 
 * WP5 - Exercise 3
 * John Dickson, Oliver Hansson, Sebastian VingÃ¥rd Larsson
 * 2026-03-XX
 * group: 27
 * Submission code: XXXXXX
 */


#include "DHT.h" // dht library

// dht pin and type
#define DHTPIN 12
#define DHTTYPE DHT11

// ldr pin
#define LDRPIN A0

// LED pins
#define LED1 5 // blue
#define LED2 7 // green
#define LED3 9 // red
#define LED_ERROR 11 // red ERROR


// temperature levels
#define TEMP_LEVEL_1 0
#define TEMP_LEVEL_2 24
#define TEMP_LEVEL_3 30

// light levels
#define LIGHT_LEVEL_1 28
#define LIGHT_LEVEL_2 20
#define LIGHT_LEVEL_3 7

// state enum
typedef enum {
  STATE_INIT,
  STATE_WAIT,
  STATE_READ_SENSORS,
  STATE_EVALUATE,
  STATE_DISPLAY,
  STATE_ERROR
} State;

// GLOBAL START
// INITialize and create our state struct and set initial state to STATE_INIT
State state = State::STATE_INIT;

// INITiailize and create dht
DHT dht(DHTPIN, DHTTYPE);

// for timing calculations
unsigned long lastUpdate = 0;
const unsigned long interval = 3000; // 3 seconds

// INITialize variables for temperature, lightValue and what LED we're lighting when we go to STATE_DISPLAY state
float temp = 0;
int lightValue = 0;
int activeLED = -1; // -1 means all off
// GLOBAL END

void setup() {
  Serial.begin(9600); // start serial
  while (!Serial); // ensure serial has started before we continue
}

// INITialize pins, and start dht
void init() {
  pinMode(LED1, OUTPUT); // blue
  pinMode(LED2, OUTPUT); // green
  pinMode(LED3, OUTPUT); // red
  pinMode(LED_ERROR, OUTPUT); // red ERROR
  
  dht.begin(); // start dht
}

void read_sensors() {
  temp = dht.readTemperature(); // read DHT for temperature
  lightValue = analogRead(LDRPIN); // read analog pin for light value
}

void evaluate() {
  activeLED = -1; // setting activeLED back to -1 to ensure our logic executes correctly

  // correct cases
  // if temp is less than level 1 and light is greater than level 1
  if (temp < TEMP_LEVEL_1 && lightValue > LIGHT_LEVEL_1) {
    activeLED = LED2; // green
  }
  // if temp is equal or greater than 1 but lower than 2 and light is equal or lesser than level 1 but greater than level 2
  else if ((temp >= TEMP_LEVEL_1 && temp < TEMP_LEVEL_2) && (lightValue <= LIGHT_LEVEL_1 && lightValue > LIGHT_LEVEL_2)) {
    activeLED = LED2; // green
  } 
  // if temp is equal or greater than 2 but less than 3 and light is equal or lesser to level 2 but greater than level 3
  else if ((temp >= TEMP_LEVEL_2 && temp < TEMP_LEVEL_3) && (lightValue <= LIGHT_LEVEL_2 && lightValue > LIGHT_LEVEL_3)) { 
    activeLED = LED2; // green
  }
  // if temp is equal or greater than 3 and light is equal or lower than 3
  else if (temp >= TEMP_LEVEL_3 && lightValue <= LIGHT_LEVEL_3) {
    activeLED = LED2; // green
  }
  // if activeLED remains -1, it means we havent found a correct case yet so we check incorrect ones
  if (activeLED == -1) {
    // if light greater (darker) than 1 and temp is greater than 1
    if (lightValue > LIGHT_LEVEL_1 && temp > TEMP_LEVEL_1) {
      activeLED = LED3; // RED (too warm)
    }
    // if light value is less (brighter) or equal to 1 and greater (darker) than 2
    else if (lightValue <= LIGHT_LEVEL_1 && lightValue > LIGHT_LEVEL_2) {
      if (temp < TEMP_LEVEL_1) activeLED = LED1; // too low temperature
      else if (temp >= TEMP_LEVEL_2) activeLED = LED3; // too high temperature
    }
    // if light is less (brighter) or equal to 2 and greater (darker) than 3
    else if (lightValue <= LIGHT_LEVEL_2 && lightValue > LIGHT_LEVEL_3) {
      if (temp < TEMP_LEVEL_2) activeLED = LED1; // too low temperature
      else if (temp > TEMP_LEVEL_2) activeLED = LED3; // too high temperature
    }
    // if light is less or equal to 3 (brightest) and temp is lesser than 3
    else if (lightValue <= LIGHT_LEVEL_3 && temp < TEMP_LEVEL_3) {
      activeLED = LED1; // too low temperature
    }
  }
}

void loop() {
  // our main state machine switch
  switch (state) {

    // STATE_INIT case
    case State::STATE_INIT:
      Serial.println("Initializing...");
      init(); // call init
      state = State::STATE_WAIT; // switch state
      Serial.println("Initialization complete!");
      break; // break case

    // STATE_WAIT case
    case State::STATE_WAIT:
      // non-blocking delay
      if (millis() - lastUpdate >= interval) {
        state = State::STATE_READ_SENSORS;
      }
      break; // break case

    // STATE_READ_SENSORS case
    case State::STATE_READ_SENSORS:
      Serial.println("Reading sensors...");
      read_sensors(); // update sensor data

      if (isnan(temp) || isnan(lightValue)) { // if no temp OR no lightValue, set state STATE_ERROR
        state = State::STATE_ERROR;
      } else { // else print for monitoring and set state STATE_EVALUATE
        Serial.print("Temp: "); Serial.println(temp);
        Serial.print("Light: "); Serial.println(lightValue);
        state = State::STATE_EVALUATE; // set STATE_EVALUATE
      }
      break; // break case

    // STATE_EVALUATE case
    case State::STATE_EVALUATE:
      Serial.println("Evaluating...");
      evaluate(); // evaluate the data
      
      state = State::STATE_DISPLAY; // set STATE_DISPLAY
      break; // break case

    // STATE_DISPLAY case
    case State::STATE_DISPLAY:
      // turn off all LEDs
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
      digitalWrite(LED3, LOW);

      Serial.println("Displaying...");

      // if activeLED is not -1, light the active one
      if (activeLED != -1) {
        digitalWrite(activeLED, HIGH);
      }

      // reset update timer
      lastUpdate = millis(); 
      state = State::STATE_WAIT; // set state to STATE_WAIT
      break; // break case

    case State::STATE_ERROR:
      Serial.println("Failed to read a sensor");
      digitalWrite(LED_ERROR, HIGH); // light red ERROR LED
      state = State::STATE_WAIT; // go back to waiting for next cycle
      break; // break case
  }
}