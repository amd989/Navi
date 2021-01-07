/// Reads the value of the specified pin
int readPin(int pin)
{
  return digitalRead(pin);
}

/// Turns on the ACC LED
void turnOnAccLed()
{
  digitalWrite(LEDPin, HIGH);
}

/// Turns off the ACC LED
void turnOffAccLed()
{
  digitalWrite(LEDPin, LOW);
}
