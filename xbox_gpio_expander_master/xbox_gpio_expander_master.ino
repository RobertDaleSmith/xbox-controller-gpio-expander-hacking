#include <Wire.h>

// Assume the TCA6416A has a default address of 0x40. Adjust if necessary.
#define TCA6416A_ADDR 0x21 

void setup() {
  // Initialize the serial communication for logging
  Serial.begin(115200);

  // Initialize I2C communication as a master
  Wire.begin();
  Wire.setClock(400000);  // Set I2C frequency to 400kHz
  
  Serial.println("I2C Sniffer Started");
}

void loop() {
  Wire.beginTransmission(TCA6416A_ADDR);
  Wire.write(0x00);
  Wire.endTransmission(true);

  byte data[2]; // buffer to store received data
  int dataIndex = 0;

  // Check if there's any I2C communication
  if (Wire.requestFrom(TCA6416A_ADDR, 2)) { // Request up to 10 bytes
    while (Wire.available()) {
      data[dataIndex++] = Wire.read();
    }
    
    // Interpret the data
    interpretData(data, dataIndex);
  }

  delay(8); // Delay a bit before checking again
}

void interpretData(byte* data, int len) {
  if (len == 0) return;

  Serial.print("Received Data: ");
  for (int i = 0; i < len; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Interpret based on the datasheet
  if (data[0] == 0x00) {
    Serial.println("Reading Input Port Register");
  }

  // if (data[0] == 0x10) {
  //   init();
  //   Serial.println("INIT");
  // }
  
  // Add other interpretations as necessary based on the datasheet
}

void init() {

  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x48);
  // Wire.write(0xFB);
  // Wire.write(0xBF);
  // Wire.endTransmission(false);
  Wire.beginTransmission(TCA6416A_ADDR);
  Wire.write(0x46);
  Wire.write(0xFB);
  Wire.write(0xBF);
  Wire.endTransmission(false);
  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x06);
  // Wire.write(0xFF);
  // Wire.write(0xBF);
  // Wire.endTransmission(false);
  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x02);
  // Wire.write(0xFF);
  // Wire.write(0xFF);
  // Wire.endTransmission(false);

  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x48);
  // Wire.endTransmission(false);
  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x46);
  // Wire.endTransmission(false);
  // Wire.beginTransmission(TCA6416A_ADDR);
  // Wire.write(0x06);
  // Wire.endTransmission(false);
}
