#include <Ultrasonic.h>
#include <BitVoicer11.h>
#include <Stepper.h>
int blinkDelay = 250;
int sequenceDir = 0;
int lightLevel = 0;
const int twoTrig = 3;
const int twoEcho = 4;
// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
//names the variables
int duration;
int distance;
//Sets up the pins and default variables
int pinB = 5;
int pinG = 6;
//  IN1, 1N2, IN3, IN4
Stepper myStepper1 = Stepper(stepsPerRevolution, 10, 11, 12, 13);
Stepper myStepper2 = Stepper(stepsPerRevolution, 30, 31, 32, 33);
Stepper myStepper3 = Stepper(stepsPerRevolution, 40, 41, 42, 43);
//Creates a new instance of the BitVoicerSerial class
//Sets up serial port to 0
BitVoicerSerial bvSerial = BitVoicerSerial();
Ultrasonic ultrasonic(8,9);//(Trigger_Pin,Echo_Pin)

void setup() {
  pinMode(pinB, OUTPUT);
  pinMode(pinG, OUTPUT);
  // Set the speed to 5 rpm:
  myStepper1.setSpeed(5);
  myStepper2.setSpeed(5);
  myStepper3.setSpeed(5);
  Serial.begin(9600);
     }
void loop() {
  //Stepper Motor1
  Serial.println("clockwise");
  myStepper1.step(stepsPerRevolution);
  delay(500); 
  Serial.println("counterclockwise");
  myStepper1.step(-stepsPerRevolution);
  delay(500);

  
  //Stepper Motor2
  Serial.println("clockwise");
  myStepper2.step(stepsPerRevolution);
  delay(500); 
  Serial.println("counterclockwise");
  myStepper2.step(-stepsPerRevolution);
  delay(500);

  
  //Stepper Motor3
  Serial.println("clockwise");
  myStepper3.step(stepsPerRevolution);
  delay(500);
  Serial.println("counterclockwise");
  myStepper3.step(-stepsPerRevolution);
  delay(500);

  
  //for 2nd ultrasonic
  digitalWrite(twoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(twoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(twoTrig, LOW);
  duration = pulseIn(twoEcho, HIGH);
  distance=duration*0.034/2;
  Serial.print("2nd US Distance: ");
  Serial.println(distance);
  delay(1500);
  //reads data from library for 1st and prints
  Serial.println(ultrasonic.distanceRead());
  delay(1500);
  //Retrieves data from serial buffer 
  bvSerial.getData();
 
  //Quits the loop if no string data was returned from getData
  if (bvSerial.strData == "")
  {
    return;
  }
 
  //Each of the next 'if' statements performs a different
  //task based on the data received from BitVoicer
  if (bvSerial.strData == "trash")
  {
    digitalWrite(pinG, HIGH);
    bvSerial.strData = "";
    lightLevel = 255;
    delay(3000000);
  }
  else if (bvSerial.strData == "recycle")
  {
    digitalWrite(pinB, HIGH);
    bvSerial.strData = "";
    lightLevel = 255;
    
  }
  else if (bvSerial.strData == "t")
  {
    digitalWrite(pinG, HIGH);
    bvSerial.strData = "";
    lightLevel = 255;
  }
  else if (bvSerial.strData == "r")
  {
    digitalWrite(pinB, HIGH);
    bvSerial.strData = "";
    lightLevel = 255;
  }
  else
  {
    Serial.println("ERROR:" + bvSerial.strData);
    bvSerial.strData = "";
  }
}
