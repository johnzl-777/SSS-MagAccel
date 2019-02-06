#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>

/* INCOMPLETE unit vector struct */
typedef struct
{
  int x;
  int y;
  int z;
} U_vec;

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
  sensors_event_t accel_event, mag_event;
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(accel_event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accel_event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accel_event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(mag_event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(mag_event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(mag_event.magnetic.z); Serial.print("  ");Serial.println("uT");
  
  /*Acceleration Unit Vector*/

  Serial.println("");
  /* Delay before the next sample */
  delay(500);
}
