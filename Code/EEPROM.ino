const int EeepromAddress = 0;

/// Saves the current status into eeprom
void saveCurrentStatus(int currentStatus)
{
  serialPrintLn("Saving settings... ");
  // writes status to eeprom when car is off.
  EEPROM.write(EeepromAddress, currentStatus);
  serialPrintLn("Current Lid Status: ", currentStatus);
  serialPrintLn("Complete. ");  
}

/// Loads previous status into eeprom
int loadPreviousStatus()
{
  serialPrintLn("Loading settings... ");
  // reads the old lid status when the arduino is powered.
  int previousStatus = EEPROM.read(EeepromAddress);
  serialPrintLn("Previous lid Status: ", previousStatus);
  serialPrintLn("Complete. ");
  return previousStatus;
}
