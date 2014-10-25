// Direction of movement
const int ForwardMovement     = 0;
const int BackwardsMovement   = 1;

// Thresholds for positions.
const int OpenPositionMin     = 145;
const int OpenPositionMax     = 166;

const int ClosedPositionMin   = 970;
const int ClosedPositionMax   = 990;

const int tilt0PositionMin    = 195;
const int tilt0PositionMax    = 205;

const int tilt1PositionMin    = 255;
const int tilt1PositionMax    = 265;

const int tilt2PositionMin    = 330;   // 90 degrees
const int tilt2PositionMax    = 340;

// Status
const int ClosedStatus        = 0;
const int OpenStatus          = 1;
const int Tilt0Status         = 2;
const int Tilt1Status         = 3;
const int Tilt2Status         = 4;

// Definitions
typedef struct LidPosition { 
  int MaxPosition; 
  int MinPosition; 
  int MovementDirection;
  int LidStatus;
};

typedef struct CurrentStatus { 
  int oldAccessoryState;
  int oldLidStatus;
  int lidStatus;
  int openCloseButtonState;
  int tiltButtonState;
  int accessoryState;
};

/// Returns the position range for the specified state
LidPosition getPositionRangeFromStatus(int currentLidStatus);

// Get the position range from the next tilted status using the current lid status
LidPosition getNextTiltedStatusPositions(int currentLidStatus);
