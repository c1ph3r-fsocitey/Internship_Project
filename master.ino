#include <Wire.h>

#define SLAVE_ADDRESS 9  // I2C address of the slave Arduino Mega

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // Read data from the ultrasonic sensor on the Mega
  int distance = readDistanceFromMega();
  
  // Send the data to the Serial Monitor
  Serial.print("Distance from Mega: ");
  Serial.println(distance);

  // Send the data to the Mega over I2C
  sendDataToMega(distance);

  delay(1000);  // Add a delay to control the frequency of data transmission
}

int readDistanceFromMega() {
  Wire.requestFrom(SLAVE_ADDRESS, 1);  // Request 1 byte from the Mega
  while (Wire.available() < 1);       // Wait until data is received
  return Wire.read();                  // Read and return the received data
}

void sendDataToMega(int data) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(data);  // Send the data to the Mega
  Wire.endTransmission();
}
