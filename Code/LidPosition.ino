/// Returns the position range for the specified state
LidPosition getPositionRangeFromStatus(int currentLidStatus)
{
  LidPosition lidPosition; 
  switch(currentLidStatus)
  {
     case Tilt0Status:
      lidPosition.MinPosition = tilt0PositionMin;
      lidPosition.MaxPosition = tilt0PositionMax;
      break;
    case Tilt1Status:
      lidPosition.MinPosition = tilt1PositionMin;
      lidPosition.MaxPosition = tilt1PositionMax;
      break;
    case Tilt2Status:
      lidPosition.MinPosition = tilt2PositionMin;
      lidPosition.MaxPosition = tilt2PositionMax;
      break;  
    case OpenStatus:
    default:
      lidPosition.MinPosition = OpenPositionMin;
      lidPosition.MaxPosition = OpenPositionMax;
      break;
  }
  
  return lidPosition;
}

// Get the position range from the next tilted status using the current lid status
LidPosition getNextTiltedStatusPositions(int currentLidStatus)
{
  LidPosition lidPosition;
  switch(currentLidStatus){
    case Tilt0Status:
      lidPosition.MinPosition = OpenPositionMin;
      lidPosition.MaxPosition = tilt1PositionMin;
      lidPosition.LidStatus = Tilt1Status;
      lidPosition.MovementDirection = ForwardMovement;
      break;
    case Tilt1Status:
      lidPosition.MinPosition = OpenPositionMin;
      lidPosition.MaxPosition = tilt2PositionMin;
      lidPosition.LidStatus = Tilt2Status;
      lidPosition.MovementDirection = ForwardMovement;
      break;
    case Tilt2Status:
      lidPosition.MinPosition = OpenPositionMax;
      lidPosition.MaxPosition = ClosedPositionMax;
      lidPosition.LidStatus = OpenStatus;
      lidPosition.MovementDirection = BackwardsMovement;      
      break;  
    case OpenStatus:
    default:
      lidPosition.MinPosition = OpenPositionMin;
      lidPosition.MaxPosition = tilt0PositionMin;
      lidPosition.LidStatus = Tilt0Status;
      lidPosition.MovementDirection = ForwardMovement;
      break;
  }
  serialPrintLn("Moving: ", lidPosition.MovementDirection);
}

/// Checks whether the lid is closer or not.
boolean isLidClosed()
{
  int currentPosition = readSensor();
  serialPrintLn("Current Position: ", currentPosition);
  return ClosedPositionMin <= currentPosition && currentPosition <= ClosedPositionMax;
}

/// Checks whether the lid is opened or not.
boolean isLidOpen()
{
  return currentStatus.lidStatus != ClosedStatus;
}
