/******************************************************************************
 *             Access Control System                                          *
 *                                                                            *
 *             Description:                                                   *
 *             This project simulates an entry and exit system of             *
 *             an urbanization that can grant access when the PIR             *
 *             detects a person.                                              *
 ******************************************************************************/

// Include the servo motor library
#include <Servo.h>

/*******************************PINS DECLARATION*******************************/
// Pin where the trigger of the Ultrasound Sensor is connected
const int TRIGGER = 2;
// Pin where the echo of the Ultrasound Sensor is connected
const int ECHO = 3;
// Pin where the buzzer is connected
const int BUZZER = 9;
// Pin where the red LED is connected
const int RED_LED = 8;
// Pin where the yellow LED is connected
const int YELLOW_LED = 12;
// Pin where the green LED is connected
const int GREEN_LED = 13;
// Pin where the PIR sensor is connected
const int PIR_SENSOR = 4;

/*****************************CONSTANTS AND OBJECT*****************************/
// Minimum distance to stop the mechanical arm from going down
const int MIN_DIST = 90; 
// Frequency of the buzzer
const int FREQUENCY = 500;
// Time related with the tone of the buzzer
const int TIMER = 500; 
// Create servo object to control the servo
Servo myServo;  

/************************************SETUP*************************************/
void setup() {
  // Begin the serial connection for debugging with 9600 bits per second
  Serial.begin(9600);
  // Set the output pins
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT); 
  pinMode(TRIGGER, OUTPUT);
  // Set the input pins
  pinMode(ECHO, INPUT);
  pinMode(PIR_SENSOR, INPUT);
  // Set where the servo is connected
  myServo.attach(5);
  /*************Set default state************/
  // Turn on the red LED
  digitalWrite(RED_LED, HIGH);
  // Move the Servo motor to 0 degrees
  servoDefault();
}


/********************************MAIN PROGRAM**********************************/
void loop() {
  // Determine if the PIR sensor detects movements
  if(motionDetected())
  {// There is a movement detected by the PIR sensor
    // Print a message into the serial monitor for debugging purposes
    Serial.println("Motion detected");
    // Call the subroutine that make the mechanical arm to rise
    armUpProtocol();
    // Wait for 4 seconds
    delay(4000);
    // Call the subroutine that make the mechanical arm to go down
    armDownProtocol();
  }
  else
  {// There is no motion detected by the PIR sensor
    // Print a message into the serial monitor for debugging purposes
    Serial.println("No motion detected");
  }
}

/*******************************Subroutines***********************************/
/**
 * Subroutine to read the distance detected by the ultrasound sensor
 * 
 * @return distance to the object in centimeters
 */
float readUltrasound()
{
  // Declare the variable that will hold the distance in centimeters
  float cm;
  // Make the ultrasonic sensor produce a sound wave
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Determine the time that the sound wave takes to return 
  // and convert time into distance (centimeters)
  cm = pulseIn(ECHO, HIGH) / 58.4; 
  // Keep two decimal places
  cm = (int(cm * 100.0)) / 100.0; 
  // Print the distance in the Serial monitor for debugging purposes
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  // Return the distance
  return cm;
}

/**
 * Subroutine that helps us to determine if there is movement 
 * detected by the PIR sensor
 * 
 * @return boolean value indicating if there was motion detected
 *              true - motion detected
 *              false - motion not detected
 */
boolean motionDetected()
{
  // Read from the PIR sensor
  int pirReading = digitalRead(PIR_SENSOR);
  // Verify the reading, if the reading is HIGH,
  // this means that the PIR sensor has detected a movement
  if(pirReading==HIGH)
  {
    // Print a message in the serial monitor for debugging pusposes
    Serial.println("PIR sensor activated");
    // Return true, to indicate that there has been a movement
    return true;
  }
  // Print a message in the serial monitor for debugging purposes
  Serial.println("PIR sensor OFF");
  // Return false to indicate that there is no movement detected
  return false;
}

/**
 * Subroutine that helps us to set the servo motor to its 
 * default position at 0 degrees
 */
void servoDefault()
{
  myServo.write(0);
}

/**
 * Subroutine that helps us raise the mechanical hand
 */
void armUpProtocol()
{
  // Turn off the red LED, indicating that where going to start this protocol
  digitalWrite(RED_LED, LOW);
  // Loop that will make the servo motor move from 0 degrees to 90 degrees
  // using steps of 10 degrees
  for(int degree = 10; degree <= 90; degree = degree + 10)
  {
    // Turn on the yellow LED
    digitalWrite(YELLOW_LED, HIGH);
    // Turn on the buzzer
    tone(BUZZER, FREQUENCY);
    // Wait 'TIMER' milliseconds
    delay(TIMER);
    // Move the servo motor to 'i' degrees
    myServo.write(i);
    // Turn off the buzzer
    noTone(BUZZER);
    // Wait 'TIMER' milliseconds
    delay(TIMER);
    // Turn off the yellow LED
    digitalWrite(YELLOW_LED, LOW);
    // Wait 'TIMER' milliseconds
    delay(TIMER);
  }
  // Turn on the green LED, to indicate the end of the protocol
  digitalWrite(GREEN_LED, HIGH);
}

/**
 * Subroutine that helps us lower the mechanical hand
 */
void armDownProtocol()
{
  // Turn off the green LED, to indicate the begging of the protocol
  digitalWrite(GREEN_LED, LOW);
  // Declare and initialize the variable that will hold the degrees
  // that will be assigned to the servo motor
  int degree = 80;
  // While we do not lower the mechanical arm completely, do the following:
  while(degree != -10)
  {
    // Loop to lower the mechanical arm, the servo will move using
    // steps of 10 degrees
    for(degree; degree >= 0; degree = degree - 10)
    {
      // Turn on the yellow LED
      digitalWrite(YELLOW_LED, HIGH);
      // Turn on the buzzer
      tone(BUZZER, FREQUENCY);
      // Wait 'TIMER' milliseconds
      delay(TIMER);
      // Move the servo to 'degree' degrees
      myServo.write(degree);
      // Turn off the buzzer
      noTone(BUZZER);
      // Wait 'TIMER' milliseconds
      delay(TIMER);
      // Turn off the yellow LED
      digitalWrite(YELLOW_LED, LOW);
      // Wait 'TIMER' milliseconds
      delay(TIMER);
      // Verify if there is an object detected by the distance sensor 
      if(readUltrasound()<= MIN_DIST)
      {
        // If there is an object, we start to rise the arm
        // from the current position up to the 90 degrees
        for(degree; degree <= 90; degree = degree + 10)
        {
          // Turn on the yellow LED
          digitalWrite(YELLOW_LED, HIGH);
          // Turn on the buzzer
          tone(BUZZER, FREQUENCY);
          // Wait 'TIMER' milliseconds
          delay(TIMER);
          // Move the servo to 'degree' degrees
          myServo.write(degree);
          // Turn off the buzzer
          noTone(BUZZER);
          // Wait 'TIMER' milliseconds
          delay(TIMER);
          // Turn off the yellow LED
          digitalWrite(YELLOW_LED, LOW);
          // Wait 'TIMER' milliseconds
          delay(TIMER);
        }
        // While there is an object close enough, keep the arm up at 90 degrees
        while(readUltrasound()<= MIN_DIST)
        {
          // Turn on the buzzer
          tone(BUZZER, FREQUENCY);
          // Turn on the green LED
          digitalWrite(GREEN_LED, HIGH);
        }
        // Turn off the green LED
        digitalWrite(GREEN_LED, LOW);
      }
    }
  }
  // Turn on the red LED, to indicate the end of the protocol
  digitalWrite(RED_LED, HIGH);
}
