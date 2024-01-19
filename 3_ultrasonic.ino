#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

AltSoftSerial mySerial1(2, 3); // RX, TX for the first sensor
AltSoftSerial mySerial2(8 ,9);        // RX, TX for the second sensor
AltSoftSerial mySerial3(6, 7);

const int lowerLimit = 10; // Set your lower distance limit here

void setup()
{
    Serial.begin(57600);
    mySerial1.begin(9600);
    mySerial2.begin(9600);
    mySerial3.begin(9600);
}

void loop()
{
    readSensorData(mySerial1, "Sensor 1: ");
    readSensorData(mySerial2, "Sensor 2: ");
    readSensorData(mySerial3, "Sensor 3: ");
}

void readSensorData(AltSoftSerial& serial, const char* sensorName)
{
    while (serial.available() >= 4)
    {
        byte data[4];
        serial.readBytes(data, 4);

        Serial.print(sensorName);
        uint16_t distance = (data[1] << 8) + data[2];
        Serial.print(sensorName);
        Serial.print("Distance: ");
        Serial.println(distance / 10.0);
    }
    delay(100);
}
