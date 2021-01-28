# -*- coding: utf-8 -*-
from bluepy.btle import DefaultDelegate, Scanner, BTLEException
import sys
import struct
import time

class ScanDelegate(DefaultDelegate):
  def __init__(self):
    DefaultDelegate.__init__(self)

  def handleDiscovery(self, dev, isNewDev, isNewData):
    #print("addr: {0}, addrType: {1}, rssi: {2}".format(dev.addr, dev.addrType, dev.rssi))
    if isNewDev or isNewData:
      for (adtype, desc, value) in dev.getScanData():
        if desc == 'Manufacturer':
          #print(adtype, desc, value)
          if value[0:4] == 'ffff':
            #print("addr: {0}, addrType: {1}, rssi: {2}".format(dev.addr, dev.addrType, dev.rssi))
            self.parseManufacturerData(value[4:])

  def parseManufacturerData(self, data):
    (id, a_dat, d_dat) = struct.unpack('>HHb', bytes.fromhex(data[0:]))
    print("deviceId: 0x{0:04x}, analogRead: {1}, digitalRead: {2}".format(id, a_dat, d_dat))


if __name__ == "__main__":
  scanner = Scanner().withDelegate(ScanDelegate())
  while True:
    try:
      scanner.scan(3.0)
    except BTLEException:
      print(BLEException)
