#include <Arduino.h>
#include "mazesolver.h"

void loop()
{
    switch(direction())
    {
    case 'f':
        setMotors(speed, speed);
        delay(1);
        break;
    case 'l':
        setMotors(0, speed);
        delay(1);
        break;
    case 'r':
        setMotors(speed, 0);
        delay(1);
        break;
    default:
        setMotors(0,0);
        break;
    }

}
