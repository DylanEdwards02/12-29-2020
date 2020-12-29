#include "main.h"

int TargetMove;
int MoveTarget;
int TargetTurnL;
int TargetTurnR;
int TypeMove = 0;
bool InPosition;
int counter;
int Timeout;
int actiondistance;
bool actionflag;
bool taskStarted;
int InchtoTicks(float inches)
{
	return(inches * 542.16)/(PI * 3.25); //Was 900
}

int DegstoTicksL(float degrees)
{
	return(degrees/360)*(1.08*3.14)* (542.16);
	//not sure what 1.08 means
}

int DegstoTicksR(float degrees)
{
	return-((degrees/360)*(1.08*3.14)* (542.16));
	//not sure what 1.08 means
}

void setTargetMove(float inches, float actiondistanceinches)
{
	//set motor encoders to 0
	DriveLeftBack.tare_position();
	DriveRightBack.tare_position();
	MoveTarget = InchtoTicks(inches);

	//MoveTarget=(360/(PI * 4.0) * 1.5) * inches;
	//Converts from inches to ticks
	actiondistance = InchtoTicks(actiondistanceinches);
	taskStarted = false;
	InPosition = false;
	actionflag = false;
	counter = 0;
	TypeMove = 0;
	//Clear Timer
	Timeout = ((abs(inches) / 15.0) * 1000) + 1000;
}

void setTargetTurn(float degrees)
{
	DriveLeftBack.tare_position();
	DriveRightBack.tare_position();
	TargetTurnL= DegstoTicksL(degrees);
	TargetTurnR= DegstoTicksR(degrees);
	InPosition = false;
	counter = 0;
	TypeMove = 1;
}

void MovePID(void*)
{
	pros::lcd::set_text(3, "Here");
	float PGain = 0.1;
	float PGainTurn = 1;
	float LMError = 0;
	float last_LMError;
	float RMError = 0;
	float last_RMError;
	float RFValue;
	float LFValue;
	float RIError = 0;
	float LIError = 0;
	float IGain = 0.01;
	float IGainTurn = 0.03;
	float DGain = 0.1;
	float DGainTurn = 0;
	float DRError;
	float DLError;
	DriveLeftBack.tare_position();
	DriveRightBack.tare_position();
	//Target = ticks;
	bool SetPosition = false;
	int Tolerance = InchtoTicks(1);
	//resetMotorEncoder(dLeft);
	//resetMotorEncoder(dRight);
	int IntergralZone = InchtoTicks(3);
	int IntergralZoneTurnL = DegstoTicksL(7);
	int IntergralZoneTurnR = DegstoTicksR(7);

	while(true)
	{
		if(TypeMove == 0)
		{
			//controller.print(0, 0, "Counter: %d", counter);
			//lcd::print(5, "counter: %d", counter);
      LMError = MoveTarget - DriveLeftBack.get_position();
      //LMError = MoveTarget - nMotorEncoder[dLeft]; //Finds how far off the target we are
			if((MoveTarget - DriveLeftBack.get_position()) < 0)
				{
					// Passed destination
				  LIError = 0;
				}

				if (abs(LMError) < IntergralZone)
				{
					LIError = (LIError + LMError);
				}
				else
				{
					LIError = 0;
				}

				DLError = last_LMError - LMError;
				last_LMError = LMError;

			LFValue = (LMError * PGain) + (LIError * IGain) + (DLError * DGain); //Finds the P value
			//motor[dLeft] = LFValue;
      DriveLeftBack.move_velocity(LFValue);
      DriveLeftFront.move_velocity(LFValue);


      RMError = MoveTarget - DriveRightBack.get_position();
			//RMError = MoveTarget - nMotorEncoder[dRight];
			if((last_RMError * RMError) < 0)
			{
				// Passed destination
			  RIError = 0;
			}
			last_RMError = RMError;

			if (abs(RMError) < IntergralZone)
			{
				RIError = (RIError + RMError);
			}
			else
			{
				RIError = 0;
			}

			DRError = last_RMError - RMError;
			last_RMError = RMError;

			RFValue = (RMError * PGain) + (RIError * IGain) + (DRError * DGain); //Determines Power Given to the motors
			//motor[dRight] = RFValue;
      DriveRightBack.move_velocity(RFValue);
      DriveRightFront.move_velocity(RFValue);

			if (((abs(LMError)) < Tolerance) && ((abs(RMError)) < Tolerance))
			{
				counter = counter + 1;
			}
			/*
			else if(time1[T1] > Timeout) //Time Out Option *need to learn timers*
			{
				counter = 51;
				actionflag = true;
			}
			*/
			else
			{
				counter = 0;
			}
			if (counter > 50)
			{
				//writeDebugStream("InPos\n");
				InPosition = true;
			}
			if (abs(LMError) < actiondistance)
			{
				//writeDebugStream("ActFlag\n");
				actionflag = true;
			}
			pros::lcd::print(5, "counter: %d/n", counter);
			pros::lcd::print(5, "LeftError: %f/n", LMError);
			pros::lcd::print(5, "RightError: %f/n", RMError);
		}

		if(TypeMove == 1)
		{


			LMError = TargetTurnL - DriveLeftBack.get_position(); //Finds how far off the target we are
			if (abs(LMError) < IntergralZoneTurnL)
			{
				LIError = (LIError + LMError);
			}
			else
			{
				LIError = 0;
			}
			LFValue = (LMError * PGainTurn) + (LIError * IGainTurn); //Finds the power value

			DriveLeftBack.move_velocity(LFValue);
      DriveLeftFront.move_velocity(LFValue);

			RMError = TargetTurnR - DriveRightBack.get_position();
			if (abs(LMError) < IntergralZoneTurnR)
			{
				LIError = (LIError + LMError);
			}
			else
			{
				LIError = 0;
			}
			RFValue = (RMError * PGainTurn) + (RIError * IGainTurn);

			DriveRightBack.move_velocity(RFValue);
      DriveRightFront.move_velocity(RFValue);
			if (((abs(LMError)) < Tolerance) && ((abs(RMError)) < Tolerance))
			{
				counter = counter + 1;
			}
			else
			{
				counter = 0;
			}
			if (counter > 50)
			{
				InPosition = true;
			}

		}

		pros::delay(10);

	}
}
