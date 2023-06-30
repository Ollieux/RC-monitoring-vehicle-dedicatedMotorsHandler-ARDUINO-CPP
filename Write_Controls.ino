#include <Servo.h>


#define rightBack A3
#define rightFront A2
#define leftBack A5
#define leftFront A4

#define enableLeft 5
#define enableRight 6

const int LOWER_BOUND_X = -36;
const int UPPER_BOUND_X = 36;
const int LOWER_BOUND_Y = -65;
const int UPPER_BOUND_Y = 0;

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

Servo servo;
int servoAngle = 90;

boolean initialSet;
int xInitial;
int yInitial;
String data;
int value;

void writeServo(String arg);
void moveAhead();
void moveBack();
void turnLeft();
void turnRight();
void stopMotors();
void writeMotorsScaled(int xValue, int yValue);

void setup()
{
  Serial.begin(115200);
  
  servo.attach(10);
  servo.write(servoAngle);

  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);

  stopMotors();
}

void loop()
{
  
  if (Serial.available() > 0)
  {
    data = Serial.readStringUntil('#');
    int separator = data.indexOf(',');

    if (separator != -1)
    {  
      int firstNum = data.substring(1, separator).toInt();
      int secondNum = data.substring(separator + 1).toInt();
      
      writeMotorsScaled(firstNum, secondNum);
    }
    else
    {
       if (!data.startsWith("$"))
      {
        writeServo(data);
      }
        stopMotors();
        initialSet = false;
    }
  }
}

void writeServo(String arg)
{
  int angle = arg.toInt();

  if (angle == 90)
  {
    servoAngle = angle;
  }
  else
  {
    servoAngle += angle;

    if (servoAngle < 0)
    {
      servoAngle = 0;
    }
    else if (servoAngle > 180)
    {
      servoAngle = 180;
    }
  }
  servo.write(servoAngle); 
}

void writeMotorsScaled(int xValue, int yValue)
{
  if (!initialSet)
  {
    if (!((yValue < (UPPER_BOUND_Y - 5)) && (yValue > (LOWER_BOUND_Y + 5)))) 
    {
        return;
    }
    
    if (!((xValue < (UPPER_BOUND_X - 5)) && (xValue > (LOWER_BOUND_X + 5)))) 
    {
      return;
    }
         
     xInitial = xValue;
     yInitial = yValue;
     initialSet = true;
   }
  else
  {
    
    if (xValue < LOWER_BOUND_X)
    {
      xValue = LOWER_BOUND_X;
    }
    else if (xValue > UPPER_BOUND_X)
    {
      xValue = UPPER_BOUND_X;
    }
    
    if (yValue < LOWER_BOUND_Y)
    {
      yValue = LOWER_BOUND_Y;
    }
    else if (yValue > UPPER_BOUND_Y)
    {
      yValue = UPPER_BOUND_Y;
    }

    if (yValue < yInitial) //TODO?: + 3
    {
      moveBack();
    
      rightMotorSpeed = map(yValue, yInitial, LOWER_BOUND_Y, 0, 255);
      leftMotorSpeed = map(yValue, yInitial, LOWER_BOUND_Y, 0, 255); 
    }
    else if (yValue > yInitial) //TODO?: - 3
    {
      moveAhead();
    
      rightMotorSpeed = map(yValue, yInitial, UPPER_BOUND_Y, 0, 255);
      leftMotorSpeed = map(yValue, yInitial, UPPER_BOUND_Y, 0, 255); 
    }
    else
    {
      rightMotorSpeed = 0;
      leftMotorSpeed = 0;
    }

    if (xValue > xInitial)
    {
      int xValueScaled = map(xValue, xInitial, UPPER_BOUND_X, 0, 255);
      
      rightMotorSpeed = rightMotorSpeed - xValueScaled; 
      leftMotorSpeed = leftMotorSpeed + xValueScaled;
//      rightMotorSpeed = rightMotorSpeed + xValueScaled; 
//      leftMotorSpeed = leftMotorSpeed - xValueScaled;
    
    if (leftMotorSpeed > 255)
      {
        leftMotorSpeed = 255;
      }
    
    if (rightMotorSpeed < 0)
      {
        rightMotorSpeed = 0;
      }
    }
    else if (xValue < xInitial)
    {
      int xValueScaled = map(xValue, xInitial, LOWER_BOUND_X, 0, 255); 
      
      rightMotorSpeed = rightMotorSpeed + xValueScaled; 
      leftMotorSpeed = leftMotorSpeed - xValueScaled;
//      rightMotorSpeed = rightMotorSpeed - xValueScaled; 
//      leftMotorSpeed = leftMotorSpeed + xValueScaled;
      

      if (rightMotorSpeed > 255)
      {
        rightMotorSpeed = 255;
      }
    
      if (leftMotorSpeed < 0)
      {
        leftMotorSpeed = 0;
      }
    }

    if (rightMotorSpeed < 70)
    {
      rightMotorSpeed = 0;
    }

    if (leftMotorSpeed < 70)
    {
      leftMotorSpeed = 0;
    }

    analogWrite(enableLeft, leftMotorSpeed);
    analogWrite(enableRight, rightMotorSpeed);
  }
}
  
void moveAhead()
{
  digitalWrite(leftBack, HIGH);
  digitalWrite(leftFront, LOW);
  digitalWrite(rightBack, HIGH);
  digitalWrite(rightFront, LOW);  
}

void moveBack()
{
  digitalWrite(leftBack, LOW);
  digitalWrite(leftFront, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(rightFront, HIGH);  
}

void turnRight()
{
  digitalWrite(leftBack, HIGH);
  digitalWrite(leftFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(rightFront, HIGH);  
}

void turnLeft()
{
  digitalWrite(leftBack, LOW);
  digitalWrite(leftFront, HIGH);
  digitalWrite(rightBack, HIGH);
  digitalWrite(rightFront, LOW);
}

void stopMotors()
{
  digitalWrite(leftBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(rightFront, LOW);  
}
  
