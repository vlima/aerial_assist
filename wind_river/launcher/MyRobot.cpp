#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */
class RobotDemo: public IterativeRobot
{
   Joystick stick; // only joystick
   Talon bottom_talon;
   Talon top_talon;
   Victor victor;

public:
   RobotDemo() :
      stick(1), bottom_talon(2), top_talon(1), victor(6)
   {
      this->SetPeriod(0); //Set update period to sync with robot control packets (20ms nominal)
   }

   /**
    * Robot-wide initialization code should go here.
    * 
    * Use this method for default Robot-wide initialization which will
    * be called when the robot is first powered on.  It will be called exactly 1 time.
    */
   void RobotDemo::RobotInit()
   {
   }

   /**
    * Initialization code for disabled mode should go here.
    * 
    * Use this method for initialization code which will be called each time
    * the robot enters disabled mode. 
    */
   void RobotDemo::DisabledInit()
   {
   }

   /**
    * Periodic code for disabled mode should go here.
    * 
    * Use this method for code which will be called periodically at a regular
    * rate while the robot is in disabled mode.
    */
   void RobotDemo::DisabledPeriodic()
   {
   }

   /**
    * Initialization code for autonomous mode should go here.
    * 
    * Use this method for initialization code which will be called each time
    * the robot enters autonomous mode.
    */
   void RobotDemo::AutonomousInit()
   {
   }

   /**
    * Periodic code for autonomous mode should go here.
    *
    * Use this method for code which will be called periodically at a regular
    * rate while the robot is in autonomous mode.
    */
   void RobotDemo::AutonomousPeriodic()
   {
   }

   /**
    * Initialization code for teleop mode should go here.
    * 
    * Use this method for initialization code which will be called each time
    * the robot enters teleop mode.
    */
   void RobotDemo::TeleopInit()
   {
   }

   /**
    * Periodic code for teleop mode should go here.
    *
    * Use this method for code which will be called periodically at a regular
    * rate while the robot is in teleop mode.
    */
   void RobotDemo::TeleopPeriodic()
   {
      //if (stick.GetTrigger())
      {
         double power = stick.GetY();
         printf("launch:  power=%2.2f, shoot=%d\n", power, stick.GetTrigger() ? 1 : 0);
         bottom_talon.Set(power);
         top_talon.Set(power);
         victor.Set(power);
      }
      Wait(0.005); // wait for a motor update time
   }

   /**
    * Initialization code for test mode should go here.
    * 
    * Use this method for initialization code which will be called each time
    * the robot enters test mode.
    */
   void RobotDemo::TestInit()
   {
   }

   /**
    * Periodic code for test mode should go here.
    *
    * Use this method for code which will be called periodically at a regular
    * rate while the robot is in test mode.
    */
   void RobotDemo::TestPeriodic()
   {
   }

};

START_ROBOT_CLASS(RobotDemo)
;
