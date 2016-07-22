#include <Wire.h>
int HMC6352SlaveAddress = 0x42;
int HMC6352ReadAddress = 0x41; //"A" in hex, A command is: 
int headingValue;


void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  //"Get Data. Compensate and Calculate New Heading"
  Wire.beginTransmission(HMC6352SlaveAddress);
  Wire.write(HMC6352ReadAddress);              // The "Get Data" command
  Wire.endTransmission();

  //time delays required by HMC6352 upon receipt of the command
  //Get Data. Compensate and Calculate New Heading : 6ms
  delay(6);

  Wire.requestFrom(HMC6352SlaveAddress, 2); //get the two data bytes, MSB and LSB

  //"The heading output data will be the value in tenths of degrees
  //from zero to 3599 and provided in binary format over the two bytes."
  byte MSB = Wire.read();
  byte LSB = Wire.read();

  float headingSum = (MSB << 8) + LSB; //(MSB / LSB sum)
  float headingInt = headingSum / 10;  
  //int ana=(float)analogRead(A0)/1023*360;
  int brightness=(float)analogRead(A0)/1023*255;
  analogWrite(2, brightness);
 // Serial.print(ana);
  Serial.print("\n");
  int sensorValue = analogRead(0);       // read analog input pin 0 i.e. the compas value
  //converting the raw data into a calibrated distance (see the conversion curve)
  sensorValue=(float)analogRead(0)/1023*360;
 
 // if ((sensorValue<=7&&sensorValue>=0) ) sensorValue=7; //remove the noise when under 7cm
  //if (sensorValue>100 || sensorValue<0)  sensorValue=100; //remove the noise when over 100 cm
  Serial.println(sensorValue);  // prints the rest of the string and add and end of line char

  delay(100);
}
