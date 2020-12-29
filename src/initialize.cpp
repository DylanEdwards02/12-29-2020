#include "main.h"





int max_case = 6;

void lcd_center_button() {
 static bool cpressed = false;
 cpressed = !cpressed;
 if (cpressed) {

 } else {
   pros::lcd::clear_line(2);
 }
}
void lcd_left_button()
{
 static bool lpressed = false;
 lpressed = !lpressed;
 if (lpressed)
 {
   pros::lcd::clear_line(2);
   switchval--;
   if (switchval < 0)
   {
     switchval = 0;
   }
   pros::lcd::set_text(2, std::to_string(switchval));
 }
 else
 {
 }
}
void lcd_right_button()
{
 static bool rpressed = false;
 rpressed = !rpressed;
 if (rpressed)
 {
   pros::lcd::clear_line(2);
   switchval++;
   if (switchval > max_case)
   {
     switchval = 0;
   }
   pros::lcd::set_text(2, std::to_string(switchval));
 }
 else
 {
 }
}

void up_button()
{
 if (pros::c::adi_digital_read('C') > 0)
 {
   pros::lcd::clear_line(2);
   switchval++;
   if (switchval > max_case)
   {
     switchval = 0;
   }
   pros::lcd::set_text(2, std::to_string(switchval));
 }
 else
 {
 }
}

void autonselector ()
{
  while(1==1)
  {
    if(pros::c::adi_digital_read('A') > 0)
    {
      break;
    }
    up_button();
    pros::delay(200);
  }
}
void my_task_fn(void* param) {
  printf("Hello %s\n", (char*)param);
  // ...
}
void initialize() {

  pros::lcd::initialize();
  pros::c::adi_analog_calibrate('A');
  DriveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  DriveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intakeR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intakeL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRollers.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  pros::delay(50);
pros::lcd::initialize();
pros::lcd::set_text(1, "355E COMPETITION CODE");

//  pros::adi_port_config_e_t(D);
//Bump Switches Defined Here
pros::ADIDigitalIn switchTop ('A');
pros::ADIDigitalIn switchBottom ('B');
pros::ADIDigitalIn AutoUP ('C');
pros::ADIDigitalIn AutoDOWN ('D');

pros::lcd::register_btn1_cb(lcd_center_button);
pros::lcd::register_btn0_cb(lcd_left_button);
pros::lcd::register_btn2_cb(lcd_right_button);
//autonselector();

pros::Task my_task (my_task_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");
pros::Task MoveTask (MovePID, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My PIDMove");
pros::Task SortTask (CycleAuto, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My SortTask");
pros::c::taskDelete(my_task);
}




void disabled()   {}

void competition_initialize()   {}
