/* 
 Navi
 
 Controls the motor and sensor of the navigation display on the 2001 to 2008 Mazda 6. 
 Replacing the stock screen controller functionality with a customizable one.
 
 This is useful if you want to use the stock navigation enclosure with a tablet and want 
 to retain the same buttons and functionality of the original screen.
 
 This code can be used for RX-8 as well. ( modify tresholds for open, closed and tilted positions)
 
 The circuit:
 * 2 pushbuttons attached from pin 2 and 3 to GND (use existing buttons on Mazda 6 input screen / RX-8 buttons)
 * 1 BA6209 H-Bridge for controlling the motor with its inputs attached to pin 4 and 5.
 * 1 Potentiometer to control position. (included in stock nav enclosure) conected to analog pin 0
 * 1 Motor (included in stock nav enclosure)
 
 created 22 March 2014
 by Alejandro Mora
 
 */
 
// Includes
#include <EEPROM.h>
 
/// Constants.
const int SensorPin = A0;
const int ForwardPin = 4;
const int BackwardsPin = 5;
const int OpenClosePin = 2;
const int TiltPin = 3;
const int AccessoryPin = 6;
const int LEDPin = 13;

// Thresholds for positions.
const int OpenPositionMin = 145;
const int OpenPositionMax = 166;

const int ClosedPositionMin = 970;
const int ClosedPositionMax = 990;

const int tilt0PositionMin = 195;
const int tilt0PositionMax = 205;

const int tilt1PositionMin = 255;
const int tilt1PositionMax = 265;

// 90 degrees
const int tilt2PositionMin = 330;
const int tilt2PositionMax = 340;

// Status
const int ClosedStatus = 0;
const int OpenStatus = 1;
const int Tilt0Status = 2;
const int Tilt1Status = 3;
const int Tilt2Status = 4;

// Direction of movement
const int ForwardMovement = 0;
const int BackwardsMovement = 1;

const int OldLidStatusAddress = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Navi: Mazda 6 navigation screen controller");
  pinMode(ForwardPin, OUTPUT);
  pinMode(BackwardsPin, OUTPUT);  
  pinMode(LEDPin, OUTPUT);
  pinMode(OpenClosePin, INPUT_PULLUP);  
  pinMode(TiltPin, INPUT_PULLUP);
  pinMode(AccessoryPin, INPUT);
  
  // loads previous status from memory
  loadPreviousStatus();
  digitalWrite(LEDPin, LOW);
}

/// Status variables.
int oldPosition  = 0;
int oldAccessoryState = LOW;
int oldLidStatus = ClosedStatus;

int lidStatus = ClosedStatus;
int openCloseButtonState = HIGH;
int tiltButtonState = HIGH;
int accessoryState = LOW;

void loop() {  
  // stop all movement;
  stopMovement();
  
  // Poll ACC State
  accessoryState = digitalRead(AccessoryPin);  
  if(accessoryState == HIGH)
  {
    // ACC On
    digitalWrite(LEDPin, HIGH);
    // Poll Buttons
    openCloseButtonState = digitalRead(OpenClosePin);
    tiltButtonState = digitalRead(TiltPin);
    if(openCloseButtonState == LOW)
    {
      Serial.println("Accessory Power: ON ");
      Serial.println("Open/Close button pressed...");
      
      int currentPosition = readSensor();
      Serial.print("Current Position: "); Serial.println(currentPosition);
      if(ClosedPositionMin <= currentPosition && currentPosition <= ClosedPositionMax)
      {
        // if lid is closed, open it.
        openLid();
      }
      else 
      {  
        // else is open or tilted, close it.      
        closeLid();
      }
    }
    if(tiltButtonState == LOW && lidStatus != ClosedStatus)
    {
      Serial.println("Accessory Power: ON ");
      Serial.println("Tilt button pressed...");
      // if lid is open, tilt it.
      tiltLid();
    }
  }  
  idle();
}

/// Moves the lid forward.
void moveForward()
{
  digitalWrite(BackwardsPin, LOW);
  digitalWrite(ForwardPin, HIGH);
}

/// Moves the lid backwards
void moveBackwards()
{
  digitalWrite(ForwardPin, LOW);
  digitalWrite(BackwardsPin, HIGH);
}

/// Stops the motor movement.
void stopMovement()
{
  digitalWrite(ForwardPin, LOW);
  digitalWrite(BackwardsPin, LOW);
}

/// Saves the current status into eeprom
void saveCurrentStatus()
{
  Serial.println("Saving settings... ");
  // writes status to eeprom when car is off.
  EEPROM.write(OldLidStatusAddress, oldLidStatus);
  Serial.print("Current Lid Status: ");
  Serial.println(oldLidStatus);
  Serial.println("Complete. ");  
}

/// Loads previous status into eeprom
void loadPreviousStatus()
{
  Serial.println("Loading settings... ");
  // reads the old lid status when the arduino is powered.
  oldLidStatus = EEPROM.read(OldLidStatusAddress);
  Serial.print("Previous lid Status: ");
  Serial.println(oldLidStatus);
  Serial.println("Complete. ");  
}

/// Reads the lid position sensor, detecting its location.
int readSensor()
{
  return analogRead(SensorPin);
}

/// Closes the lid if its opened or tilted.
void closeLid()
{
  Serial.println("Closing Lid...");
  int newPosition = readSensor();
  while(OpenPositionMin <= newPosition && newPosition <= ClosedPositionMin)
  {
    moveForward();
    newPosition = readSensor();
    //Serial.print("New Position: "); Serial.println(newPosition);
  }
  stopMovement();   
  oldPosition = newPosition;
  lidStatus = ClosedStatus;
  Serial.println("Complete");
}

/// Opens the lid if its closed
void openLid()
{
  Serial.println("Opening Lid...");
  int newPosition = readSensor();
  while(OpenPositionMax <= newPosition && newPosition <= ClosedPositionMax)
  {
    moveBackwards();
    newPosition = readSensor();
    //Serial.print("New Position: "); Serial.println(newPosition);
  }
  stopMovement();
  oldPosition = newPosition; 
  lidStatus = OpenStatus;
  Serial.println("Complete");
}

// When ignition is turned on check for previous state, if the screen was opened
// then open it again, otherwise leave it closed. If the ignition is turned off,
// close the lid
void idle()
{
  // check if ACC is different from previous status
  if(oldAccessoryState != accessoryState)
  {    
    if(accessoryState == HIGH)
    {
      Serial.println("Accessory Power: ON ");
      // Ignition is on
      if(oldLidStatus == Tilt0Status ||
         oldLidStatus == Tilt1Status ||
         oldLidStatus == Tilt2Status ||
         oldLidStatus == OpenStatus)
      {
        Serial.println("Previous lid state: opened...");
        delay(3000);
        // If car is turned on and lid was open before, open it again.
        openLid();
      }
    }
    else
    {
      // Wait a bit to confirm the car is really off instead of being started.      
      delay(3000);
      // Read the pin again to confirm the car is off.
      accessoryState = digitalRead(AccessoryPin);
      if(accessoryState == LOW)
      {
        Serial.println("Accessory Power: OFF ");
        // The car has been turned off.
        digitalWrite(LEDPin, LOW);
        oldLidStatus = lidStatus;      
        if(lidStatus != ClosedStatus)
        {        
          // If car is turned off and lid is open, close lid.
          closeLid();
        }
        Serial.print("Saving current status...");   
        saveCurrentStatus();
        Serial.println("Complete."); 
      }      
    }    
  }  
  oldAccessoryState = accessoryState;    
}

/// Tilts the lid to any of the 3 possible positions. 
/// The lid needs to be opened for the tilting to work.
void tiltLid()
{
  Serial.println("Tilting Lid...");
  Serial.print("Current Status: "); Serial.println(lidStatus);  
  int currentStatus = lidStatus;
  int minPosition = 0;
  int maxPosition = 0;
  int movementDirection = 0;
  
  switch(currentStatus){
    case Tilt0Status:
      minPosition = OpenPositionMin;
      maxPosition = tilt1PositionMin;
      lidStatus = Tilt1Status;
      movementDirection = ForwardMovement;
      Serial.print("Moving: "); Serial.println(movementDirection);   
      break;
    case Tilt1Status:
      minPosition = OpenPositionMin;
      maxPosition = tilt2PositionMin;
      lidStatus = Tilt2Status;
      movementDirection = ForwardMovement;
      Serial.print("Moving: "); Serial.println(movementDirection);
      break;
    case Tilt2Status:
      minPosition = OpenPositionMax;
      maxPosition = ClosedPositionMax;
      lidStatus = OpenStatus;
      movementDirection = BackwardsMovement;
      Serial.print("Moving: "); Serial.println(movementDirection);
      break;  
    case OpenStatus:
    default:
      minPosition = OpenPositionMin;
      maxPosition = tilt0PositionMin;
      lidStatus = Tilt0Status;
      movementDirection = ForwardMovement;
      Serial.print("Moving: "); Serial.println(movementDirection);
      break;
  }
  
  int currentPosition = readSensor();  
  while(minPosition <= currentPosition && currentPosition <= maxPosition)
  {
    if(movementDirection == ForwardMovement)
    {
      moveForward();
    } 
    else
    {
      moveBackwards();
    }    
    currentPosition = readSensor();
    // Serial.print("New Position: "); Serial.println(currentPosition);
  }
  stopMovement();
  currentPosition = readSensor();
  Serial.print("New Position: "); Serial.println(currentPosition);
  Serial.print("New Status: "); Serial.println(lidStatus);  
  oldPosition = currentPosition; 
  Serial.println("Complete");
  delay(500);
}
