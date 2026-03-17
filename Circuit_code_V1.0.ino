// Define pins to be used by Arduino
const int motorPinL = 3;
const int motorPinR = 4;
const int sensorPinL = 5;
const int sensorPinR = 6;

float error;

// Concept taken from:
// https://github.com/Alexander-Evans-Moncloa/robot-mouse/blob/main/mouse_code.cpp
// https://microcontrollerslab.com/pid-controller-implementation-using-arduino/

void setup() {
  Serial.begin(9600);

  pinMode(motorPinL, OUTPUT);
  pinMode(motorPinR, OUTPUT);
}

void loop() {
  // Proportional controller with an initial base speed
  float Kp = 0.4;
  float base_speed = 35.5;

  // Read sensors
  float L_sensor_Value = analogRead(sensorPinL);
  float R_sensor_Value = analogRead(sensorPinR);

  // To find normalised denominator
  float normDenom = L_sensor_Value + R_sensor_Value;

  // Prevent division by zero 
  if (normDenom == 0) {
    normDenom = 1;
  }

  // Calculate normalised error
  error = (L_sensor_Value - R_sensor_Value) / normDenom;

  // Correction using normalised error value 
  float correction = Kp * error;

  // Adjust motor outputs
  float leftOutput = base_speed - correction * 255.0;
  float rightOutput = base_speed + correction * 255.0;

  // Limit outputs to range of PWM values  
  leftOutput = constrain(leftOutput, 0, 255);
  rightOutput = constrain(rightOutput, 0, 255);

  // Condition for operation
  if (L_sensor_Value > 60 && R_sensor_Value > 60) {
    analogWrite(motorPinL, 0);
    analogWrite(motorPinR, 0);
  }
  else if (L_sensor_Value > 150 && R_sensor_Value > 150) {
    analogWrite(motorPinL, 255);
    analogWrite(motorPinR, 255);
  }
  else {
    analogWrite(motorPinL, leftOutput);
    analogWrite(motorPinR, rightOutput);
  }


  delay(10);
}

