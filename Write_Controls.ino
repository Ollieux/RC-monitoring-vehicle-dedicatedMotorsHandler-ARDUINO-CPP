#include <Servo.h>
//TODO: int yValueStart;
// int xValueStart;
//bool valueStartSet = false;


#define rightBack A3
#define rightFront A2
#define leftBack A5
#define leftFront A4

#define enableLeft 5
#define enableRight 6

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

Servo servo;
int servoAngle = 90;

// void writeMotors(int xValue, int yValue);
void writeServo(String arg);
void moveAhead();
void moveBack();
void turnLeft();
void turnRight();
void motorsStop();
//void writeMotorsY(int yValue);
void writeMotorsYScaled(int yValue);

void setup()
{
  
  Serial.begin(115200);
  //Serial.begin(9600);
  servo.attach(10);
  servo.write(servoAngle);

  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftFront, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightFront, OUTPUT);
  pinMode(rightBack, OUTPUT);

  motorsStop();
}

// int ORIGIN = -85; // TODO: [-85, 0]
//int initialY = ORIGIN;
int yInitial;
int LOWER_BOUND_Y = -100;
int UPPER_BOUND_Y = 0;
String data;
int value;
void loop()
{
  //while(!Serial.available())
  //int x = Serial.read();

  //TODO:
  // if (!valueStartSet)
  // {
  // xValueStart = x;
  // yValueStart = y;
  // valueStartSet = true;
  // }
  // else
  // {
  // 


  if (Serial.available() > 0)
  {
//    String data;
    data = Serial.readStringUntil('#');
//    int separator = data.indexOf(',');

    if (data.startsWith("!"))
    {
      yInitial = data.substring(1).toInt();

      if (!((yInitial > UPPER_BOUND_Y - 5) || (yInitial < LOWER_BOUND_Y - 5)))
      {
        //writeMotorsY(yInital);
        writeMotorsYScaled(yInitial);
      }

     
//      LOWER_BOUND_Y += initialY - ORIGIN;
//      UPPER_BOUND_Y += initialY - ORIGIN;

      
    }
    else if (data.startsWith("%"))
    {
//      int num;
      value = data.substring(1).toInt();

//      if (num == 0)
//      {
//        digitalWrite(LED_BUILTIN, LOW);
//       
//      }
//      else
//      {
//        digitalWrite(LED_BUILTIN, HIGH); 
//      }


      if (!((yInitial > UPPER_BOUND_Y - 5) || (yInitial < LOWER_BOUND_Y - 5)))
      {
        //writeMotorsY(value);
        writeMotorsYScaled(value);
      }

      //// writeMotorsY(num);
      
    }
    
//    if (separator != -1)
//    {
//      int firstNum;
//      firstNum = data.substring(0, separator).toInt();
//      
//      int secondNum;
//      secondNum = data.substring(separator + 1).toInt();
//
//      if ((firstNum == 0) && (secondNum == 0))
//      {
//        digitalWrite(LED_BUILTIN, LOW); 
//      }
//      else
//      {
//        digitalWrite(LED_BUILTIN, HIGH); 
// 
//      }
//
//      writeMotors(firstNum, secondNum);
//    }
    else
    {
////      if (data == "Button clicked")
////      {
////        digitalWrite(LED_BUILTIN, LOW); 
////      }
////      else
////      {
////        digitalWrite(LED_BUILTIN, HIGH); 
        writeServo(data);
////      }
//    if(data == "0")
//      writeServo(data);
    }
  }
}

void writeServo(String arg)
{
  int angle = arg.toInt();
  
//  if(angle == 0)
//  {
//    return; 
//  }
  /**else**/ if (angle == 90 || angle == 0)
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
  
  //// servoAngle = ((servoAngle + angle) + 180) % 180;
  servo.write(servoAngle); 
}

/** void writeMotors(int xValue, int yValue)
{
  if (yValue < -85)
  {
    moveBack();
    rightMotorSpeed = map(yValue, -85, -120, 0, 255);
    leftMotorSpeed = map(yValue, -85, -120, 0, 255); 
  }

   else if (yValue > -80)
   {
    moveAhead();
    rightMotorSpeed = map(yValue, -80, 0, 0, 255);
    leftMotorSpeed = map(yValue, -80, 0, 0, 255); 
  }

  else
  {
    rightMotorSpeed = 0;
    leftMotorSpeed = 0;
  }

  if (xValue > 0)
  { // 2
    int xValueScaled = map(xValue, 0, 85, 0, 255); 
    rightMotorSpeed = rightMotorSpeed - xValueScaled; 
    leftMotorSpeed = leftMotorSpeed + xValueScaled;
    
    if (leftMotorSpeed > 255)
    {
      leftMotorSpeed = 255;
    }
    
    if (rightMotorSpeed < 0)
    {
      rightMotorSpeed = 0;
    }
  }
  
  else if (xValue < 0)
  {
    int xValueScaled = map(xValue, 0, -85, 0, 255); 
    rightMotorSpeed = rightMotorSpeed + xValueScaled; 
    leftMotorSpeed = leftMotorSpeed - xValueScaled;

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
} **/

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

void motorsStop()
{
  digitalWrite(leftBack, LOW);
  digitalWrite(leftFront, LOW);
  digitalWrite(rightBack, LOW);
  digitalWrite(rightFront, LOW);  
}

/**void writeMotorsY(int yValue)
{
  if (yValue > 0)
  {
    yValue = 0;
  }

  if (yValue < -120)
  {
    yValue = -120;
  }
  
  if (yValue < -85)
  {
    moveBack();
    rightMotorSpeed = map(yValue, -85, -120, 0, 255);
    leftMotorSpeed = map(yValue, -85, -120, 0, 255); 
  }

  else if (yValue > -80)
  {
    moveAhead();
    rightMotorSpeed = map(yValue, -80, 0, 0, 255);
    leftMotorSpeed = map(yValue, -80, 0, 0, 255); 
  }

  else
  {
    rightMotorSpeed = 0;
    leftMotorSpeed = 0;
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
} **/

void writeMotorsYScaled(int yValue)
{


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
  
