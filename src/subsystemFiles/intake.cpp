#include "main.h"
//Helper Functions
void setIntake (int IntakePower)
{
  intakeL = IntakePower;
  intakeR = IntakePower;
}

void setBack (int BackRollerPower)
{
  backRoller = BackRollerPower;
}

void setFront(int FrontRollerPower)
{
  frontRollers = FrontRollerPower;
}

//OP Control Functions
void CycleAuto(void*)
{
  if(1==1)//controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
  {
    setIntake(127);
    setFront(127);
    setBack(127);
    pros::lcd::set_text(2, "FLAG");
  }
  else
  {
    setIntake(0);
    setBack(0);
    setFront(0);
  }
}

void Cycle()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
  {
    setIntake(127);
    setFront(127);
    setBack(127);
    pros::lcd::set_text(2, "FLAG");
  }
  else
  {
    setIntake(0);
    setBack(0);
    setFront(0);
  }
}

float DistanceValue = 0;
int OpticalRedValue = 0;
int OpticalBlueValue = 0;
int OpticalBallValue = 0;

void Indexing()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
  {
    if(pros::c::distance_get(6) < DistanceValue)
    {
      setIntake(127);
      setFront(50);
      setBack(-50);
    }
    else if(pros::c::optical_get_hue(7) < OpticalBallValue)
    {
      setIntake(127);
      setFront(0);
      setBack(0);
    }
    else
    {
      setIntake(127);
      setFront(50);
      setBack(127);
    }
  }
}

void Outtake()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    setIntake(-127);
  }
  else
  {
  }
}
