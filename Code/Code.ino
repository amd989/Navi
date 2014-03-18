int sensorPin = A0;
int forwardPin = 30;
int backwardsPin = 31;
int openClosePin = 32;
int tiltPin = 33;
int accessoryPin = 34;

int openPositionMin = 150;
int openPositionMax = 166;
int closedPositionMin = 970;
int closedPositionMax = 988;

int ClosedStatus = 0;
int OpenStatus = 1;
int Tilt0 = 2;
int Tilt1 = 3;
int Tilt2 = 4;

void setup() {
  Serial.begin(9600);
  Serial.println("Navi: Mazda 6 navigation interface");
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardsPin, OUTPUT);
  pinMode(openClosePin, INPUT);
  pinMode(accessoryPin, INPUT);
  //pinMode(tiltPin, INPUT);
}

long oldPosition  = 0;
int lidStatus = 0;
int openCloseButtonState = 0;
int tiltButtonState = 0;
int accessoryState = 0;

void loop() {  
  // stop all movement;
  stopMovement();  
  accessoryState = digitalRead(accessoryPin);
  openCloseButtonState = digitalRead(openClosePin);
  //tiltButtonState = digitalRead(tiltPin);
  
  if(accessoryState == HIGH)
  {
    if(openCloseButtonState == LOW)
    {
      Serial.println("Accessory Power: ON ");
      Serial.println("Open/Close button pressed...");
      int currentPosition = readSensor();
      Serial.print("Current Position: "); Serial.println(currentPosition);
      if(closedPositionMin <= currentPosition && currentPosition <= closedPositionMax)
      {
        openLid();
      }
      else if(openPositionMin <= currentPosition && currentPosition <= openPositionMax)
      {
        closeLid();
      }
    }
  }
}

void moveForward()
{
  digitalWrite(backwardsPin, LOW);
  digitalWrite(forwardPin, HIGH);
}

void moveBackwards()
{
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardsPin, HIGH);
}

void stopMovement()
{
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardsPin, LOW);
}

void saveCurrentStatus()
{
  
}

void loadPreviousStatus()
{

}

int readSensor()
{
  return analogRead(sensorPin);
}

void closeLid()
{
  Serial.println("Closing Lid...");
  int newPosition = readSensor();
  while(openPositionMin <= newPosition && newPosition <= openPositionMax)
  {
    moveForward();
    newPosition = readSensor();
    Serial.print("New Position: ");
    Serial.println(newPosition);
    //delay(10);
  }
  stopMovement();   
  oldPosition = newPosition;
  lidStatus = ClosedStatus;
  Serial.println("Complete");
}

void openLid()
{
  Serial.println("Opening Lid...");
  int newPosition = readSensor();
  while(closedPositionMin <= newPosition && newPosition <= closedPositionMax)
  {
    moveBackwards();
    newPosition = readSensor();
    Serial.print("New Position: ");
    Serial.println(newPosition);
    //delay(10);
  }
  stopMovement();
  oldPosition = newPosition; 
  lidStatus = OpenStatus;
  Serial.println("Complete");
}
