#include <Wire.h>

#define TCA6416A_ADDR 0x21

byte byteOne = 0xFA;
byte byteTwo = 0xFF;

void setup() {
  // Initialize the serial communication for logging
  Serial.begin(115200);

  // Initialize I2C communication as a slave
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  Wire1.begin(TCA6416A_ADDR);        // join I2C bus with address 0x21
  Wire1.setClock(400000);  // Set I2C frequency to 400kHz

  Wire1.onReceive(receiveEvent);      // define callback for I2C write requests
  Wire1.onRequest(requestEvent);      // define callback for I2C read requests

  Serial.println("I2C slave initialized.");
}

void loop() {

}

// Function to handle data received from the master device
void receiveEvent(int howMany) {
  Serial.print("Received: ");
  while (howMany--) {
    byte b = Wire1.read();  // read a byte
    Serial.print(" 0x");
    Serial.print(b, HEX);
    Serial.print(' ');
  }
  Serial.println();
}

// Function to send data when master requests data
void requestEvent() {
  Wire1.write(0xFA);
  Wire1.write(0xFA);

  Serial.print("Responded with 0x");
  Serial.print(byteOne, HEX);
  Serial.print(" 0x");
  Serial.print(byteTwo, HEX);
  Serial.println(' ');
}
