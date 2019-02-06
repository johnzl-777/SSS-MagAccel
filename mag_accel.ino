#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include "unit_vec.h"

/* Assign ID to accelerometer */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(88888);
/* Assign unique ID to magnetometer */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(77777);

void setup(void)
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  
  // Initialise acceleromter 
  if(!accel.begin())
  {
    // Error detecting accelerometer
    Serial.println("No Accelerometer Detected!");
    while(1);
  }

  // Enable auto-gain
  mag.enableAutoRange(true);

  //Init sensor
  if(!mag.begin())
  {
    // Error detecting magnetometer
    Serial.println("No Magnetometer Detected!");
  }
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;

  /*Declare General Unit Vector */
  Uvec unit_accel, unit_mag;
  
  /*Magnetometer Unit Vector*/
  accel.getEvent(&event);
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  gen_unit_vec(event.acceleration.x, event.acceleration.y, event.acceleration.z, &unit_accel);
  print_unit_vec(unit_accel);

  mag.getEvent(&event);
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  
  /*Magnetometer Unit Vector*/
  gen_unit_vec(event.magnetic.x, event.magnetic.y, event.magnetic.z, &unit_mag);
  print_unit_vec(unit_mag);
  
  Serial.println("");
  /* Delay before the next sample */
  delay(500);
}
