#Assault Cube Example (x64)
from ctypes import *
import ctypes
from sys import platform
import os
import keyboard

#Ammo Pointer is "ac_client.exe"+00109B74 (OFFSET 0x150)
oPlayer = 0x00109B74
iAmmo = 0x150

scriptPath = str(os.path.dirname(__file__))

DriverPath = scriptPath + "\\PyDriverUsermode.dll"
Driver = cdll.LoadLibrary(DriverPath)
print("Successfully loaded ", Driver)

processHandle = c_char_p(bytes("ac_client.exe", encoding="ascii"))

Driver.ProcessID(processHandle)
modBase = Driver.ModuleBaseAddress(processHandle)

while True:
    #Driver.TestFunction()
    player = Driver.ReadInt(modBase + oPlayer)
    Driver.WriteInt(player + iAmmo, 999) #infinite ammo

    if keyboard.is_pressed('end'):
            exit(0)