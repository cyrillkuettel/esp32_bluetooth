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


// runs only once
void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);

  SerialBT.begin("ESP32"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  printDeviceAddress();

}

// Handle received and sent messages
char incomingChar;

void loop() {
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    Serial.write(incomingChar);  
  }

  delay(20);

}
