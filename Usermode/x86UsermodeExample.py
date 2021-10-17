#CSGO Example (x86)
from ctypes import *
from sys import platform
import os
import keyboard

dwEntityList = (0x4DBC5B4)
dwForceAttack = (0x31ECB34)
dwLocalPlayer = (0xDA244C)
m_fFlags = (0x104)
m_iCrosshairId = (0x11438)
m_iTeamNum = (0xF4)

scriptPath = str(os.path.dirname(__file__))

DriverPath = scriptPath + "\\PyDriverUsermode.dll"
Driver = cdll.LoadLibrary(DriverPath)
print("Successfully loaded ", Driver)

processHandle = c_char_p(bytes("csgo.exe", encoding="ascii"))
moduleBase = c_char_p(bytes("client.dll", encoding="ascii")) #Driver is hard coded to use Client.dll anyways...

Driver.ProcessID(processHandle)
modBase = Driver.ModuleBaseAddress(moduleBase)

while True:
    #triggerbot
    player = Driver.ReadInt(modBase + dwLocalPlayer)
    entity_id = Driver.ReadInt(player + m_iCrosshairId)
    entity = Driver.ReadInt(modBase + dwEntityList + (entity_id - 1) * 0x10)

    entity_team = Driver.ReadInt(entity + m_iTeamNum)
    player_team = Driver.ReadInt(player + m_iTeamNum)

    if entity_id > 0 and entity_id <= 64 and player_team != entity_team:
        Driver.WriteInt(modBase + dwForceAttack, 6)

    if keyboard.is_pressed('end'):
            exit(0)