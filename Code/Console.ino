/// Prints line
void serialPrintLn(const String& message)
{
  if(DEBUG)
  {   
    Serial.println(message);
  }
}

/// Prints line with const value
void serialPrintLn(const String& message, const String& value)
{
  if(DEBUG)
  {   
    Serial.print(message); Serial.println(value);
  }
}

/// Prints line with string value
void serialPrintLn(const String& message, const int value)
{
  if(DEBUG)
  {   
    Serial.print(message); Serial.println(value);
  }
}
