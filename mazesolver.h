#ifndef MAZESOLVER_H_INCLUDED
#define MAZESOLVER_H_INCLUDED
#include "NewPing.h"
#define MAX_DISTANCE 400 // Maximum distance



// Left sonar pin = echo - 8, trig - 9 max - 400cm, out of bound 2cm
// Front sonar pin = echo - 10, trig - 11
// Right sonar pin = echo - 12, trig  - 13


double leftDistance, frontDistance, rightDistance; // distance in CM

NewPing leftSonar(9, 8, MAX_DISTANCE);
NewPing frontSonar (11, 10, MAX_DISTANCE);
NewPing rightSonar (13, 12, MAX_DISTANCE);


void updateDistance()
{
    Serial.println("Updating distances: ");
    leftDistance = leftSonar.ping() / US_ROUNDTRIP_CM;
    frontDistance = frontSonar.ping() / US_ROUNDTRIP_CM;
    rightDistance = rightSonar.ping() / US_ROUNDTRIP_CM;

    Serial.println("Front: " + String(frontDistance) + " cm");
    Serial.println("Left: " + String(leftDistance) + " cm");
    Serial.println("Right: " + String(rightDistance) + " cm");
}



#endif // MAZESOLVER_H_INCLUDED
