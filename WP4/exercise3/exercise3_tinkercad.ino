/*
 * Group 27
 * John Dickson
 * Sebastian Vingård Larsson
 * Oliver Hansson
 * Submission Code: XlvS5W
*/

#include <Adafruit_NeoPixel.h> // neopixel ring library

// defining our pins
#define PIXEL_PIN   6 // neoring
#define PIXEL_COUNT 12 // neoring pixel count
#define RED_LED     3 // red led
#define SENSOR_PIN  A0 // ldr sensor

// INTERRUPT_FREQ is in seconds
#define CLOCK_SPEED 16000000
#define PRESCALER 1024
#define INTERRUPT_FREQ 1

// initializing our NeoPixel ring
Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// initializing our light values to compare for updates
uint16_t g_lightValue; // ldr is 10 bit based so we need 16bit int
volatile uint16_t g_newLightValue; // same here
volatile bool g_shouldToggleLEDs = false; // control bool for toggle
volatile bool g_readSensor = false;  // control bool for interrupt routing and updating


// setup function
void setup(void) {
  // begin serial reader
  Serial.begin(9600);
  // just variable mumbo jumbo giving both the initialized variables an arbitrary starting value
  g_lightValue = g_newLightValue = 0;
  // setting red LEDs pinmode
  pinMode(RED_LED, OUTPUT);
  // red LED digitalWrite
  digitalWrite(RED_LED, LOW);

  ring.begin(); // start ring
  ring.show(); // clear ring

  // set up the interrupt functionality
  // to perform an interrupt once every second
  cli(); // stop interrupts
  
  TCCR1A = 0; // set TCCR1A reg to 0
  TCCR1B = 0; // set TCCR1B reg to 0
  TCNT1 =  0; // init counter to 0
  
  // IMPORTANT! Value MUST be less than 65536 for
  // timer1. Even less for timer0 and timer2.
  // Set compare match regs to 1Hz (1 second)
  OCR1A = CLOCK_SPEED / (INTERRUPT_FREQ * PRESCALER) - 1; // (16*10⁶) / (1 * 1024) - 1
    
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  
  // Set CS10 and CS12 bits for the 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei(); // allow interrupts
}


// main loop
void loop() {

  	// if to ensure we only update if the value has changed
  	if (g_readSensor) {
    	// for debugging/calibrating
	    Serial.println(g_lightValue);
  		// read the sensor
    	g_newLightValue = analogRead(SENSOR_PIN);
      	g_readSensor = false;
  	}
  
  	// if the old lightValue and the new are different
  	// then we go into the logic to light LEDs according to value
	if ((g_shouldToggleLEDs = (g_lightValue != g_newLightValue))) {
  		g_lightValue = g_newLightValue;  
    
    	// map to set a span of values of which we operate within
    	// our ldr is extremely narrow for some reason
    	int ledCount = map(g_lightValue, 0, 918, 0, PIXEL_COUNT);

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
	    } else { // otherwise we dont
    		digitalWrite(RED_LED, LOW);
    	}
      	// reset toggle to false
	    g_shouldToggleLEDs = false;
    }
}

// Interrupt Service Routine
ISR(TIMER1_COMPA_vect) {
  	// read sensor every interrupt by setting true here so that the loop knows to read
	g_readSensor = true;
}