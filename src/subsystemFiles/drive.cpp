#include "main.h"

//Helper Functions
void setDrive (int leftpower, int rightpower)
{
  DriveLeftFront = leftpower;
  DriveLeftBack = leftpower;
  DriveRightFront = rightpower;
  DriveRightBack = rightpower;
}

//OP Control Functions
void setDriveMotors ()
{
  int leftjoystickval = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightjoystickval = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if(abs(leftjoystickval) < 10)
    {
      leftjoystickval = 0;
    }
  if(abs(rightjoystickval) < 10)
    {
      rightjoystickval = 0;
    }

  /*  Kevin Limit
  if((leftjoystickval) > 110){
    leftjoystickval = 100;
  }
  if((rightjoystickval) > 110){
    rightjoystickval = 100;
  }
  */

  float leftjoystick = leftjoystickval^2/127;
  float rightjoystick = rightjoystickval^2/127;
  setDrive(leftjoystick, rightjoystick);
}
