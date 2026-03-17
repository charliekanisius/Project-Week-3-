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
  //Define values for kp and speed
  float Kp = 0.4;
  float base_speed = 100.0;
//Get sensor reading
  float L_sensor_Value = analogRead(sensorPinL);
  float R_sensor_Value = analogRead(sensorPinR);
//Calculation for normalised error
  float normDenom = L_sensor_Value + R_sensor_Value;
//Condition to avoid dividing by zero 
  if (normDenom == 0)
   normDenom = 1;

  float error = (L_sensor_Value - R_sensor_Value)/normDenom;
  float correction = Kp*error;

  float leftOutput = base_speed - correction*255.0;
  float rightOutput = base_speed + correction*255.0;
//Keeping speed of wheels within PWM values 60 to 150 
  leftOutput = constrain(leftOutput, 60, 150);
  rightOutput = constrain(rightOutput, 60, 150);
//To keep as integer values 
  analogWrite(motorPinL, (int)leftOutput);
  analogWrite(motorPinR, (int)rightOutput);

  delay(10);
}
