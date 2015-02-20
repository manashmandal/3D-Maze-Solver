#include <NewPing.h>
#define max_distance 400

int Speed = 200;

int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};

NewPing leftSonar(13, 12, max_distance);
NewPing frontSonar(11, 10, max_distance);
NewPing rightSonar(9, 8, max_distance);

unsigned int left, front, right;

void setMotors(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0 && rightSpeed >= 0)
  {
   analogWrite(leftMotor[0], leftSpeed);   /*   Forward  */
   analogWrite(leftMotor[1], 0);
   analogWrite(rightMotor[0], rightSpeed);
   analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed < 0 && rightSpeed < 0)
  {
    leftSpeed = -leftSpeed;
    rightSpeed = -rightSpeed;
    
    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);    /* Backward */
  }
  
  else if (leftSpeed == 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor[0], 0);                     /*Left */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed >= 0 && rightSpeed == 0)
  
  {
    analogWrite(leftMotor[0], leftSpeed);
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);  /*right */
    analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed >= 0 && rightSpeed <= 0)
  {
    rightSpeed = - rightSpeed;
    analogWrite(leftMotor[0], leftSpeed);  /* turn clockwise */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);
  }
  
  else if (leftSpeed <= 0 && rightSpeed >= 0)
  {
    
    leftSpeed = - leftSpeed;
    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);   /* turn anti clockwise */
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  } 
  
}



void updateDistance()
{
  Serial.println("Updating distance");
  left = leftSonar.ping() / US_ROUNDTRIP_CM;
  right = rightSonar.ping() / US_ROUNDTRIP_CM;
  front = frontSonar.ping() / US_ROUNDTRIP_CM;
  Serial.println("Front: " + String(front) + " cm");
  Serial.println("Left: " + String(left) + " cm");
  Serial.println("Right: " + String(right) + " cm");
  delay(10);
}

char decideDirection()
{
  updateDistance();
  if (front > left && front > right) return 'f';
  else if (left > front && left > right) return 'l';
  else if (right > front && right > left) return 'r';
  else return 's';
}
  

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Serial.begin(9600);
  Serial.println("Ready for printing");
  for (int i = 0; i < 2; i++){
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  switch(decideDirection()){
    case 'f':
      setMotors(Speed, Speed);
      delay(1);
      break;
    case 'l':
      setMotors(0, Speed);
      delay(1);
      break;
    case 'r':
      setMotors(Speed, 0);
      delay(1);
      break;
    default:
      setMotors(0,0);
      break;  
  }
}
