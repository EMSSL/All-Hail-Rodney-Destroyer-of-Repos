// Code to use accelerometer
//
// PINOUTS:
// ADXL335  to   UNO
// Vin      ->   +5V
// 3Vo      ->   AREF
// GND      ->   GND
// Zout     ->   A2
// Yout     ->   A1
// Xout     ->   A0

// libraries
#include <math.h>    

// pins
const int xInput = A0;    // x acceleration, 0-1023 returned
const int yInput = A1;    // y acceleration, 0-1023 returned
const int zInput = A2;    // z acceleration, 0-1023 returned

// raw ranges
int zRawMin = 401;
int zRawMax = 664;

int yRawMin = 396;
int yRawMax = 633;

int xRawMin = 396;
int xRawMax = 617;

// Take multiple samples to reduce noise
const int sampleSize = 10;



// Set it up once...
void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  Serial.println("Serial begin!");
  Serial.println(""); 
}


// Loop over and over...
void loop() {
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);
  Serial.print("X Accl raw: ");
  Serial.println(xRaw);
  Serial.print("Y Accl raw: ");
  Serial.println(yRaw);
  Serial.print("Z Accl raw: ");
  Serial.println(zRaw);

  // // Convert raw values to g fractions
  long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
  long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
  long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);
  Serial.print("X Accl [g]: ");
  Serial.println(xScaled);
  Serial.print("Y Accl [g]: ");
  Serial.println(yScaled);
  Serial.print("Z Accl [g]: ");
  Serial.println(zScaled);

  // Calculate angle
  double ang = atan2((double) zScaled, (double) xScaled);
  Serial.print("Theta [deg]: ");
  Serial.println(ang*180/3.1415927 - 90);
  Serial.println("");

  delay(500);
  
}


// Read "sampleSize" samples and report the average
int ReadAxis(int axisPin) {
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++) {
    reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
