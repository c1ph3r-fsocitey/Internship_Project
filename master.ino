#include <Wire.h>
#include <NewPing.h>

const int lowerLimit = 30; // Set your lower distance limit here

NewPing ultrasonicSensor(9, 10); // Example: Trig pin to D9, Echo pin to D10

void setup() {
  Wire.begin(8);                // join I2C bus with address #8
  Wire.onRequest(sendDistance); // register event
  Serial.begin(9600);
}

void loop() {
  // No need for a specific loop in the Slave. The ultrasonic sensor reading
  // and data transmission are triggered by the master's requests.
}

void sendDistance() {
  uint16_t distance = getUltrasonicData();

  byte data[4];
  data[0] = 0;          // Placeholder for future use
  data[1] = distance >> 8;
  data[2] = distance & 0xFF;
  data[3] = 0;          // Placeholder for future use

  Wire.write(data, 4);  // Send data to the master
}

uint16_t getUltrasonicData() {
  // Example: Read distance from ultrasonic sensor
  unsigned int distance = ultrasonicSensor.ping_cm(); // Replace with your actual ultrasonic sensor reading logic

  if (distance > 0) {
    Serial.println(distance / 10.0);
    return distance; // Return the distance in millimeters
  } else {
    Serial.println("Error in ultrasonic sensor reading.");
    return 0;
  }
}
