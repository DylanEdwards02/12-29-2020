#include "main.h"
int switchval;

void SKILLS()
{
  setTargetMove(30.0,30.0);
  while(inPosition==false)
  {
  }

}

void autonomous()
  {

pros::Task PIDTask(MovePID);
pros::Task SortTask(Cycle);

    switch (switchval)
    {
      case 0:
      //default case, no autonomous
      SKILLS();
        break;
      case 1:
  		//ThreePT();
        break;
  		case 2:
  		//TwoPTLeft();
        break;
      case 3:
      //ALTLeft();
        break;
      case 4:
      //TwoPTRight();
        break;
      case 5:
      //ALTRight();
        break;
      case 6:
      //SKILLS();
        break;
  		//default case
  		default:
  		break;

    }

}
