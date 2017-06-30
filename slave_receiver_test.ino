// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
const int len_Array = 15;
bool data [len_array];
void setup() {
  Wire.begin(4);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(1);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int i = 0;
  while (0 < Wire.available()) { // loop through all but the last
    bool c = Wire.read(); // receive byte as a character
    Serial.print(c);
    if (i < len_array)
      data[i] = c;
    i++;
  }
  Serial.println(" ");
  Serial.println("data buffer");
  for (int i = 0 ; i < len_array ; i++)
  {
    Serial.print(data[i]);
  }
  Serial.println(" ");
}
