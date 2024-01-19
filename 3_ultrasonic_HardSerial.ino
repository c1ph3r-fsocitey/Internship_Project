#include <AltSoftSerial.h>

AltSoftSerial mySerial1; // RX, TX for the first sensor
AltSoftSerial mySerial2; // RX, TX for the second sensor
AltSoftSerial mySerial3; // RX, TX for the third sensor

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
    // delay(100); // Introduce a delay between readings to allow AltSoftSerial to switch between instances
    readSensorData(mySerial2, "Sensor 2: ");
    // delay(100);
    readSensorData(mySerial3, "Sensor 3: ");
    // delay(100);
}

void readSensorData(AltSoftSerial& serial, const char* sensorName)
{
    if (serial.available() >= 4)
    {
        byte data[4];
        serial.readBytes(data, 4);

        uint16_t distance = (data[1] << 8) + data[2];

        Serial.print(sensorName);
        if (distance > lowerLimit)
        {
            Serial.println(distance / 10.0);
        }
        else
        {
            Serial.println("Below lower limit.");
        }
    }
}
