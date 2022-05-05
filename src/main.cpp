#include <Arduino.h>
#include "BluetoothSerial.h"
// Bluetooth Serial object
BluetoothSerial SerialBT;

// Handle received and sent messages
String message = "";
char incomingChar;

void setup() {
  Serial.begin(115200);
  // Bluetooth device name
  SerialBT.begin("ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println();


}

void loop() {
  // Serial.print("ESP Board MAC Address:  ");
  // Serial.println(WiFi.macAddress());
  
  // Read received messages (LED control command)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();

    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  
  delay(20);
}
