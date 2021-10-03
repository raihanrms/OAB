#include <Servo.h>
#include <NewPing.h> 
int echoPinRight = 6;         // pin 6 to recieve echo from right sensor
int trigerPinRight = 7;       // pin 7 to trigger the right sensor
int echoPinMiddle = 8;        // pin 8 to recieve echo from middle sensor
int trigerPinMiddle = 9;      // pin 9 to trigger the middle sensor
int echoPinLeft = 13;         // pin 13 to recieve echo pin from left sensor
int trigerPinLeft = 10;       // pin 10 to trigger the left sensor
int motorA1 = 2;              // pin 2 for controlling motor A1
int motorA2 = 3;              // pin 3 for controlling motor A2
int motorB1 = 4;              // pin 4 for controlling motor B1
int motorB2 = 5;              // pin 5 for controlling motor B2
const int motorSpeed = 12;    // arduino pwm pin 11 to control motor speed
double echoValueright, echoValuemiddle, echoValueleft;  // initializing variable to recieve echo from the sensors
float cmRight, cmMiddle, cmLeft; // initializing variable to store distance measured of sensors in cm
Servo myservo;

void setup()
{ 
  Serial.begin(9600);  // starting serial communication to print values recieved by sensor on serial monitor
  myservo.attach(12); 
  pinMode(echoPinLeft, INPUT); // setting arduino pin as input
  pinMode(trigerPinLeft, OUTPUT); // setting arduino pin as output
  pinMode(echoPinMiddle, INPUT); // setting arduino pin as input
  pinMode(trigerPinMiddle, OUTPUT); // setting arduino on as output
  pinMode(echoPinRight, INPUT); // setting arduino pin as input
  pinMode(trigerPinRight, OUTPUT); // setting arduino pin as output
  pinMode(motorSpeed, OUTPUT); // setting arduino pin as output to control mototr speed
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  }
  
void loop()
{ 
  float cmR, cmM, cmL;  // initializing variables to store distance obtained from sensors in cm
  int maxRange = 40;  // setting max range 
  //analogWrite(motorSpeed, 50); // setting motor speed varying between 0-255
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

   
  cmR = sensorRight();
  cmM = sensorMiddle();
  cmL = sensorLeft();
   Serial.println();
   Serial.println("Distance from the object to each sensor");
  Serial.println();
  Serial.print(cmL);
  Serial.print("        ");
  Serial.print(cmM);
  Serial.print("        ");
  Serial.print(cmR);
   if ((cmM > maxRange) )
  {
    digitalWrite(motorA1,HIGH);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, HIGH);
    Serial.println();
    Serial.println("MOVE FORWARD");
  }
  if ((cmR < maxRange) && (cmL > maxRange) && (cmM < maxRange) )
  {
    digitalWrite(motorA1,LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    Serial.println();
    Serial.println("MOVE LEFT");
  }
  else if ((cmR > maxRange) && (cmL < maxRange) && (cmM < maxRange) )
  {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
     Serial.println();
Serial.println("MOVE RIGHT");
  }
    else if ((cmR < maxRange) && (cmL < maxRange) && (cmM < maxRange) )
  { 
  if (cmR>cmL && cmR>cmM)
  {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, HIGH);
       Serial.println();
Serial.println("MOVE RIGHT");
    }
   else if (cmR<cmL && cmL>cmM)
  {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
       Serial.println();
    Serial.println("MOVE LEFT");
    }
    else if(cmM>cmR && cmM>cmL)
    {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, HIGH);
       Serial.println();
    Serial.println("MOVE FORWARD");
    }
    else if (cmM == cmR == cmL )
     {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, LOW);
       Serial.println();
    Serial.println("STOP");
    }
    }
     else if ((cmR > maxRange) && (cmL > maxRange) && (cmM < maxRange) )
  { 
     if (cmL > cmR)
    {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      Serial.println();
Serial.println("MOVE LEFT");
    }
    else if (cmR > cmL)
    {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, HIGH);
            Serial.println();
Serial.println("MOVE RIGHT");
    }
}
  delay(2000);
}
// function to operate right sensor
float sensorRight()
{
  digitalWrite(trigerPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinRight, LOW);
  echoValueright = pulseIn(echoPinRight, HIGH);
  cmRight = echoValueright / 650;
  return (cmRight);
}
// function to operate middle sensor
float sensorMiddle()
{
  digitalWrite(trigerPinMiddle, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinMiddle, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinMiddle, LOW);
  echoValuemiddle = pulseIn(echoPinMiddle, HIGH);
  cmMiddle = echoValuemiddle / 650;
  return (cmMiddle);
}

// function to operate left sensor
float sensorLeft()
{
  digitalWrite(trigerPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinLeft, LOW);
  echoValueleft = pulseIn(echoPinLeft, HIGH);
  cmLeft = echoValueleft / 650;
  return (cmLeft);
}
