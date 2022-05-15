#include "BluetoothSerial.h"
#include <WiFi.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// GPIO where LED is connected to
const int ledPin =  25;

      


// Handle received and sent messages
String message = "";
char incomingChar;

void printDeviceAddress() {
 
  const uint8_t* point = esp_bt_dev_get_address();
 
  for (int i = 0; i < 6; i++) {
 
    char str[3];
 
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
 
    if (i < 5){
      Serial.print(":");
    }
 
  }
  Serial.print("\n");
}



void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  

  SerialBT.begin("ESP32"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  printDeviceAddress();

  if(!SerialBT.begin("ESP32")){
    Serial.println("An error occurred initializing Bluetooth");
  }else{
    Serial.println("Bluetooth initialized");
  }

  SerialBT.write(1); // Starting signal to phone
}


boolean startSignalSent = false;

void loop() {
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

  if (SerialBT.connected()) {
      delay(5000);
      SerialBT.write(1);  
      startSignalSent = true;
  }

}
