#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX for A02YYUW ultrasonic sensor

#define SLAVE_ADDRESS 9  // I2C address of the slave Arduino Mega
const int lowerLimit = 30; // Set your lower distance limit here

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}

void loop() {
  // Your main loop code goes here
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    int command = Wire.read();

    if (command == 1) {
      // Request to send ultrasonic sensor data
      int distance = readUltrasonicSensor();
      
      // Send the data to the master over I2C
      Wire.beginTransmission(SLAVE_ADDRESS);
      Wire.write(distance >> 8);  // High byte
      Wire.write(distance & 0xFF); // Low byte
      Wire.endTransmission();
    }
  }
}

int readUltrasonicSensor() {
  mySerial.write('R'); // Trigger the A02YYUW ultrasonic sensor to start ranging

  delay(100); // Wait for the sensor to measure the distance

  if (mySerial.available() >= 4) {
    byte data[4];
    mySerial.readBytes(data, 4);

    uint16_t distance = (data[1] << 8) + data[2];

    if (distance > lowerLimit) {
      Serial.println(distance / 10.0);
      return distance;
    } else {
      Serial.println("Below lower limit.");
      return 0; // Return 0 if distance is below the lower limit
    }
  }

  return 0; // Return 0 if data is not available
}
