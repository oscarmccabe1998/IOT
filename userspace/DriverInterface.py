import struct, fcntl, os, sys
from dataclasses import dataclass
import ctypes
import json
import time 
import subprocess
from Capture import takePhoto

class pin(ctypes.Structure):
    _fields_ = [
        ('desc', ctypes.c_char * 16),
        ('pin', ctypes.c_int),
        ('value', ctypes.c_int),
        ('opt', ctypes.c_char)
    ]

class lkm_data(ctypes.Structure):
    _fields_ =[
        ('data', ctypes.c_char * 256),
        ('len', ctypes.c_long),
        ('type', ctypes.c_char)
    ]


class DriverOperations:
    def __init__(self):
        self.IOCTL_READ = 0x65
        self.IOCTL_WRITE = 0x66
        self.GPIO_READ = 0x67
        self.GPIO_WRITE = 0x68
        self.fd = os.open("/dev/GPIO_Driver_dev", os.O_RDWR)
        self.data = lkm_data()

    def writeToDriver(self, param):
        LKM_Message = fcntl.ioctl(self.fd, self.IOCTL_WRITE, str(param))
        self.checkLKMMessage(LKM_Message)

    def readFromDriver(self):
        LKM_Message = fcntl.ioctl(self.fd, self.IOCTL_READ, self.data)
        print(self.data.data)
        self.checkLKMMessage(LKM_Message)

    def writeToGPIO(self, apin):
        LKMOperation = fcntl.ioctl(self.fd, self.GPIO_WRITE, apin)
        print("written value to pin")
        
    def readFromGPIO(self, apin):
        res = fcntl.ioctl(self.fd, self.GPIO_READ, apin)
        print(res)
        print("read pin, check dmesg")
        print("look here")
        print("pin number", apin.pin, "value", apin.value)
        return apin.value

    def initGPIOState(self):
        pass

    def checkLKMMessage(self, message):
        if sys.getsizeof(message) < 0:

            print("failed")
        else:
            print(message)
            print("sucess")
    


def deviceInterfaces(interface):
    #with open('GPIODevices.json') as json_file:
    #    deviceData = json.load(json_file)
    #    Devices = deviceData.get('Device_pins')
    #    Indicators = deviceData.get('indicator_pins')
    #    print(Devices)
    #    print(Indicators)
    #    Door = Devices.get('Door_Relay')
    #    Door = dict(Door)
    #    print(Door)
    doorControl = pin()
    doorControl.pin = 2
    doorControl.value = 1
    noEntry = pin()
    noEntry.pin = 18
    noEntry.value = 1
    ableToEnter = pin()
    ableToEnter.pin = 3
    ableToEnter.value = 0
    deviceList = [doorControl, noEntry, ableToEnter]
    
    for item in deviceList:
        interface.writeToGPIO(item)
    print("default values active")

def unlockDoor(interface):
    doorControl = pin()
    doorControl.pin = 2
    doorControl.value = 0
    noEntry = pin()
    noEntry.pin = 18
    noEntry.value = 0
    ableToEnter = pin()
    ableToEnter.pin = 3
    ableToEnter.value = 1
    deviceList = [doorControl, noEntry, ableToEnter]
    for item in deviceList:
        interface.writeToGPIO(item)
    print("door open")
    interface.readFromGPIO(ableToEnter)

def checkForGuest(interface):
    buttonPin = pin()
    buttonPin.pin = 23
    while True:
        state = interface.readFromGPIO(buttonPin)
        if int(state) == 1:
            takePhoto()
            print("Someone is here")
            time.sleep(5)
            resetButton = pin()
            resetButton.pin = 23
            resetButton.value = 0
            interface.writeToGPIO(resetButton)




if __name__ == "__main__":
    #apin = pin()
    #apin.pin = 2
    #apin.value = 0
    #interface = DriverOperations()
    #interface.writeToGPIO(apin)
    #interface.writeToDriver("Test from param")
    #interface.readFromDriver()
    #interface.readFromGPIO(apin)
    interface = DriverOperations()
    interface.readFromDriver()
    deviceInterfaces(interface)
    time.sleep(1)
    unlockDoor(interface)
    time.sleep(1)
    deviceInterfaces(interface)
    checkForGuest(interface)