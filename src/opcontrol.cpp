#include "main.h"


void opcontrol()
{

    while(true)
    {
      setDriveMotors();
      Cycle();
      Indexing();
      Outtake();
      pros::delay(10);
    }
}
