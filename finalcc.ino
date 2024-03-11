#include <FastLED.h>
#include <Wire.h>
#include <Arduino_LSM6DS3.h>

const float alpha = 0.95;  // Weight for the complementary filter
float pitch = 0, roll = 0, yaw = 0;

float x, y, z;
float xAcceleration, yAcceleration, zAcceleration;
float xGyro, yGyro, zGyro;
float accelYaw;
unsigned long previousTime = 0;

#define NUM_LEDS 96  //defines number of leds
#define DATA_PIN 2   //defines data pin

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // Turn the LED on, then pause
  unsigned long currentTime = millis();
  float elapsedTime = (currentTime - previousTime) / 1000.0;  // Time elapsed in seconds

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(x, y, z);
    // Extract X, Y, and Z-axis acceleration data
    xAcceleration = x;  // X-axis acceleration
    yAcceleration = y;  // Y-axis acceleration
    zAcceleration = z;  // Z-axis acceleration

    IMU.readGyroscope(x, y, z);
    xGyro = x;  // X-axis gyroscope
    yGyro = y;  // Y-axis gyroscope
    zGyro = z;  // Z-axis gyroscope

    float accelPitch = atan2(-yAcceleration, sqrt(xAcceleration * xAcceleration + zAcceleration * zAcceleration)) * 180.0 / PI;
    float accelRoll = atan2(xAcceleration, zAcceleration) * 180.0 / PI;
    accelYaw = atan2(xAcceleration, sqrt(yAcceleration * yAcceleration + zAcceleration * zAcceleration)) * 180.0 / PI;
    //the yaw result is kind of weird, going to leave for now but this needs to be checked later.


    Serial.print("Pitch: ");
    Serial.print(accelPitch);
    Serial.print(" Roll: ");
    Serial.print(accelRoll);
    Serial.print(" Yaw: ");
    Serial.println(accelYaw);

    // int mappedValue1 = map(accelYaw, -90, 90, 0, 15);  // Map accelYaw from -90 to 90 to 0 to 6, this code essentially "assigns" a center to our yaw value
    // mappedValue1 = constrain(mappedValue1, 0, 15);

    fill_solid(leds, NUM_LEDS, CRGB::Black);  //turns all leds that are not currently assigned to anything to black

    // Ensure mappedValue stays within the LED range
    int mappedValue1 = map(accelYaw, -90, 90, 0, 15);
    mappedValue1 = constrain(mappedValue1, 0, 15);

    

    int mappedValue2 = map(accelYaw, -90, 90, 31, 16);
    mappedValue2 = constrain(mappedValue2, 16, 31);

    

    int mappedValue3 = map(accelYaw, -90, 90, 32, 47);
    mappedValue3 = constrain(mappedValue3, 32, 47);

    

    int mappedValue4 = map(accelYaw, -90, 90, 63, 48);
    mappedValue4 = constrain(mappedValue4, 48, 63);

    

    int mappedValue5 = map(accelYaw, -90, 90, 64, 79);
    mappedValue5 = constrain(mappedValue5, 64, 79);

    

    int mappedValue6 = map(accelYaw, -90, 90, 95, 80);
    mappedValue6 = constrain(mappedValue6, 80, 95);


    leds[mappedValue1] = CHSV(224, 200, 150);
    leds[mappedValue2] = CHSV(224, 200, 150);
    leds[mappedValue3] = CHSV(224, 200, 150);
    leds[mappedValue4] = CHSV(224, 200, 150);
    leds[mappedValue5] = CHSV(224, 200, 150);
    leds[mappedValue6] = CHSV(224, 200, 150);
    
    nearbyLeds(mappedValue1);
    nearbyLeds(mappedValue2);
    nearbyLeds(mappedValue3);
    nearbyLeds(mappedValue4);
    nearbyLeds(mappedValue5);
    nearbyLeds(mappedValue6);

    FastLED.show();  //turns on leds based on these values
  }

  delay(50);
}

void nearbyLeds(int mappedValue) {  //this code lights the values around our lights
  if (mappedValue - 1 > -1) {
    leds[mappedValue - 1] = CHSV(67, 255, 50);
  }
  if (mappedValue + 1 < NUM_LEDS) {
    leds[mappedValue + 1] = CHSV(67, 255, 50);
  }
  if (mappedValue - 2 > -2) {
    leds[mappedValue - 2] = CHSV(96, 255, 20);
  }
  if (mappedValue + 2 < NUM_LEDS + 2) {
    leds[mappedValue + 2] = CHSV(96, 255, 20);
  }
  if (mappedValue - 3 > -3) {
    leds[mappedValue - 3] = CHSV(96, 255, 20);
  }
  if (mappedValue + 3 < NUM_LEDS + 3) {
    leds[mappedValue + 3] = CHSV(96, 255, 20);
  }
  if (mappedValue - 4 > -4) {
    leds[mappedValue - 4] = CHSV(96, 255, 20);
  }
  if (mappedValue + 4 < NUM_LEDS + 4) {
    leds[mappedValue + 4] = CHSV(96, 255, 20);
  }
  if (mappedValue - 5 > -5) {
    leds[mappedValue - 5] = CHSV(96, 255, 20);
  }
  if (mappedValue + 5 < NUM_LEDS + 5) {
    leds[mappedValue + 5] = CHSV(96, 255, 20);
  }

  if (mappedValue - 6 > -6) {
    leds[mappedValue - 6] = CHSV(96, 255, 20);
  }
  if (mappedValue + 6 < NUM_LEDS + 6) {
    leds[mappedValue + 6] = CHSV(96, 255, 20);
  }
}


    int index = mappedValue + i;
    if (index >= minRange && index <= maxRange && i != 0) {
      if (index >= 0 && index < NUM_LEDS) {
        leds[index] = CHSV(67, 255, 50);  // LEDs adjacent to the mapped value
      }
    }
  }
}