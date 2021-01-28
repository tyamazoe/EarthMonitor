# EarthMonitor
M5Atom Earth Sensor monitor program.

## ble_earth/ble_earth.ino
- M5Atom program.
- Read Earth sensor value. [EARTH Sensor](https://docs.m5stack.com/#/en/unit/earth)

  analogRead_value = analogRead(32);

  digitalRead_value = digitalRead(26);

- Broadcast sensor data in BLE advertise packet every 10 minutes.

## raspi/earth_scan.py
- python script runs on RaspBerry Pi.
- Install bluepy library
- Monotor BLE advertize packet with 0xffff test manufacture id from M5Atom
```
pi@raspi:~/earth $ sudo python3 earth_scan.py

deviceId: 0x0101, analogRead: 4095, digitalRead: 1
deviceId: 0x0101, analogRead: 4095, digitalRead: 1
deviceId: 0x0101, analogRead: 4095, digitalRead: 1
```
