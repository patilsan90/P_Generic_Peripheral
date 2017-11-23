#include <Arduino.h>

#define WATER_LEVEL_HIGH_STATUS 1 // Dimmer Circuit will be connected to this pin //1 is also on board LED

void setup()
{
    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
    analogWrite(WATER_LEVEL_HIGH_STATUS, 0);
    delay(2000);

    analogWrite(WATER_LEVEL_HIGH_STATUS, 255);
    delay(2000);
}