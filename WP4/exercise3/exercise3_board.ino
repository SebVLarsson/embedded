/*
 * Group 27
 * John Dickson
 * Sebastian Vingård Larsson
 * Oliver Hansson
 * Submission Code: XlvS5W
*/

#include <Adafruit_NeoPixel.h> // neopixel ring library
#include <FspTimer.h> // fsp timer library

// defining our pins
#define PIXEL_PIN   6 // neopixel ring
#define PIXEL_COUNT 12 // amount of LEDs in neopixel ring
#define RED_LED     3 // red LED pin
#define SENSOR_PIN  A0 // LDR sensor

// defining our timer frequency
#define TIMER_FREQUENCY 10.0f // 10 hz = 100ms

// initializing our FspTimer
FspTimer g_timer;

// initializing our NeoPixel ring
Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// initializing our light values to compare for updates
uint16_t g_lightValue;
volatile uint16_t g_newLightValue;

// timer callback function
void timerCallback(timer_callback_args_t __attribute((unused)) *p_args) {
  g_newLightValue = analogRead(SENSOR_PIN); // read LDR sensor
}

// timer start funciton
bool beginTimer() {
  // telling the system we will use the pwm timer regardless of its opinions
  FspTimer::force_use_of_pwm_reserved_timer();

  // a bunch of ifs to see if the timer started correctly, was setup correctly etc
  if (!g_timer.begin(TIMER_MODE_PERIODIC, GPT_TIMER, 0, TIMER_FREQUENCY, 0.0f, timerCallback)) return false;
  if (!g_timer.setup_overflow_irq()) return false;
  if (!g_timer.open()) return false;
  if (!g_timer.start()) return false;

  // if all above were not true, we know the timer is working correctly so return true
  return true;
}

// setup function
void setup(void) {
  // begin serial reader
  Serial.begin(9600);
  // just variable mumbo jumbo giving both the initialized variables an arbitrary starting value
  g_lightValue = g_newLightValue = 335;
  // setting red LEDs pinmode
  pinMode(RED_LED, OUTPUT);
  // red LED digitalWrite
  digitalWrite(RED_LED, LOW);

  ring.begin(); // start ring
  ring.show(); // clear ring
  beginTimer(); // start FspTimer
}


// main loop
void loop() {

  // if to ensure we only update if the value has changed
  if (g_lightValue != g_newLightValue) {
    // set light value to the new value
    g_lightValue = g_newLightValue;
    // for debugging/calibrating
    Serial.println(g_lightValue);
    
    // map to set a span of values of which we operate within
    // our ldr is extremely narrow for some reason
    int ledCount = map(g_lightValue, 80, 125, 0, PIXEL_COUNT);

    // constrain to valid range
    ledCount = constrain(ledCount, 0, PIXEL_COUNT);

    // clear the ring
    ring.clear();

    // loop through the individual LEDs and light each one individually
    // based on values read via light sensor
    for (int i = 0; i < ledCount; i++) {
      ring.setPixelColor(i, ring.Color(0, 150, 255)); // blue-ish
    }

    // send data to ring to light what is supposed to link
    ring.show();

    // if all pixels in the ring is lit, we light the red LED
    if (ledCount >= PIXEL_COUNT) {
      digitalWrite(RED_LED, HIGH);
    } else { // otherwise red LED turned off
      digitalWrite(RED_LED, LOW);
    }
  }
}