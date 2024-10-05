#include <Wire.h>

#define TCA6416A_ADDR 0x21

int counter = 0;
byte byteOne = 0xFA;
byte byteTwo = 0xFF;

void setup() {
  // Initialize the serial communication for logging
  Serial.begin(115200);

  // Initialize I2C communication as a master
  Wire.begin();
  Wire.setClock(400000);  // Set I2C frequency to 400kHz

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
  byte data[2]; // buffer to store received data
  int dataIndex = 0;

  Wire.beginTransmission(TCA6416A_ADDR);
  Wire.write(0x01);
  Wire.endTransmission(false);

  // Check if there's any I2C communication
  if (Wire.requestFrom(TCA6416A_ADDR, 2)) { // Request up to 10 bytes
    while (Wire.available()) {
      data[dataIndex++] = Wire.read();
    }
    
    // Interpret the data
    interpretData(data, dataIndex);
  }

  Wire.endTransmission();

  delay(8); // Delay a bit before checking again
}

void interpretData(byte* data, int len) {
  if (len == 0) return;

  Serial.print("Received Data: ");
  for (int i = 0; i < len; i++) {
    Serial.print("0x");
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println(" ");

  // Interpret based on the datasheet
  if (data[0] == 0x00) {
    Serial.println("Reading Input Port Register");
  } else {
    byteOne = data[0];
    byteTwo = data[1];
  }

  // Add other interpretations as necessary based on the datasheet
}

// Function to handle data received from the master device
void receiveEvent(int howMany) {
  Serial.print("Received: ");
  while (howMany--) {
    byte b = Wire1.read();  // read a byte
    Serial.print(b, HEX);
    Serial.print(' ');
  }
  Serial.println();
}

// Function to send data when master requests data
void requestEvent() {
  Wire1.write(0xFA);
  Wire1.write(0xFA);

  // if (counter <= 128 && counter > 0) Wire1.write(0xFA);
  // else Wire1.write(0xFF);

  // counter++;
  // if (counter > 256) counter = 0;

  Serial.print("Responded with 0x");
  Serial.print(byteOne, HEX);
  Serial.print(" 0x");
  Serial.print(byteTwo, HEX);
  Serial.println(' ');
}
