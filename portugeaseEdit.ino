#include <NewPing.h>

#define MAX_DISTANCE 100
#define min 5

int rightBoundMax = 8;
int rightBoundMin = 4;

int speedReducer = 30;


NewPing leftSonar(9, 8, MAX_DISTANCE);
NewPing frontSonar(11, 10, MAX_DISTANCE);
NewPing rightSonar(13, 12, MAX_DISTANCE);


int leftMotor[] = { 3, 4 };
int rightMotor[] = { 5, 6 };

int speed = 150; // Change it at your will

int left, front, right;


void setMotors(int l, int r)
{
	if (l >= 0 && r >= 0)
	{
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}

	else if (l < 0 && r < 0)
	{
		r = -r;
		l = -l;
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}

	else if (l > 0 && r < 0)
	{
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}

	else if (l < 0 && r > 0)
	{
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}

	else
	{
		digitalWrite(leftMotor[0], LOW);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		digitalWrite(rightMotor[1], LOW);
	}
}


int leftDistance()
{
	return leftSonar.ping() / US_ROUNDTRIP_CM;
}

int rightDistance()
{
	return rightSonar.ping() / US_ROUNDTRIP_CM;
}

int frontDistance()
{
	return frontSonar.ping() / US_ROUNDTRIP_CM;
}


void setup()
{
	Serial.begin(9600);
	for (int i = 0; i < 2; i++){
		pinMode(leftMotor[i], OUTPUT);
		pinMode(rightMotor[i], OUTPUT);
	}
	Serial.println("Serial initialized");
	delay(3000);
  /* add setup code here */

}

void loop()
{
	front = frontDistance();
	left = leftDistance();
	right = rightDistance();

	if (front > min){
		if (right > rightBoundMin && right < rightBoundMax){
			setMotors(speed - speedReducer, speed);
		}

		if (right >= rightBoundMax){
			setMotors(speed, speed - speedReducer);
		}

		if (right < rightBoundMin){
			setMotors(speed - speedReducer, speed);
		}
	}
  /* add main program code here */

}
