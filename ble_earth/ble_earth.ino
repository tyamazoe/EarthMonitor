#include "M5Atom.h"
#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEBeacon.h"
#include "esp_sleep.h"

#define GPIO_DEEP_SLEEP_DURATION     600  // sleep x seconds and then wake up

uint16_t analogRead_value = 0;
uint16_t digitalRead_value = 0;
uint16_t device_id = 0x0101;        // your any sensor device id

BLEAdvertising *pAdvertising;

void readEarthSensor() {
  analogRead_value = analogRead(32);
  digitalRead_value = digitalRead(26);
  Serial.printf("0x%04x, %d, %d\n", device_id, digitalRead_value, analogRead_value);
}

void setAdvData() {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  oAdvertisementData.setFlags(0x06); // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
  std::string strServiceData = "";
  strServiceData += (char)0x08;   // length
  strServiceData += (char)0xff;   // AD Type 0xFF: Manufacturer specific data
  strServiceData += (char)0xff;   // Test manufacture ID
  strServiceData += (char)0xff;   // Test manufacture ID
  strServiceData += (char)((device_id >> 8) & 0xff);
  strServiceData += (char)(device_id & 0xff);
  strServiceData += (char)((analogRead_value >> 8) & 0xff);
  strServiceData += (char)(analogRead_value & 0xff);
  strServiceData += (char)(digitalRead_value & 0xff);

  oAdvertisementData.addData(strServiceData);
  pAdvertising->setAdvertisementData(oAdvertisementData);
}

void setup() {
  M5.begin(true, false, true);
  delay(10);
  Serial.begin(115200);
  M5.dis.clear();
  pinMode(26, INPUT);
  Serial.println("\nEarth Test");

  // Create the BLE Device
  BLEDevice::init("Earth_Beacon");
  pAdvertising = BLEDevice::getAdvertising();

  // Read earth sensor value
  readEarthSensor();
  // set advertizing packet data
  setAdvData();

  // Start advertising
  pAdvertising->start();
  Serial.println("Advertizing started...");
  delay(1200);
  pAdvertising->stop();
  Serial.printf("enter deep sleep\n");
  esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
  Serial.printf("in deep sleep\n");
}

void loop() {
}
