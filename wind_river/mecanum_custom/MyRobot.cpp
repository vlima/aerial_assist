#include "WPILib.h"
#include "WheelVector.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */
class RobotDemo: public IterativeRobot
{
private:
   static const double RAD_TO_NORMAL = 1.0 / 850;
   static const double K = 0.8;
   
   Joystick stick; // only joystick
   Talon left_front;
   Talon left_back;
   Talon right_front;
   Talon right_back;
   Encoder left_front_encoder;
   Encoder left_back_encoder;
   Encoder right_front_encoder;
   Encoder right_back_encoder;
   WheelVector input;
   WheelVector desired_out;
   
public:
   RobotDemo() :
      stick(1), left_front(1), left_back(2), right_front(3), right_back(4),
      left_front_encoder(1, 2), left_back_encoder(3, 4), right_front_encoder(5, 6), right_back_encoder(7, 8)
   {
      this->SetPeriod(0); //Set update period to sync with robot control packets (20ms nominal)
      left_front_encoder.SetDistancePerPulse(1.0);
      left_back_encoder.SetDistancePerPulse(1.0);
      right_front_encoder.SetDistancePerPulse(1.0);
      right_back_encoder.SetDistancePerPulse(1.0);
      left_front_encoder.Start();
      left_back_encoder.Start();
      right_front_encoder.Start();
      right_back_encoder.Start();
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
      desired_out = WheelVector::calc(stick.GetX(), stick.GetY(), stick.GetTwist());
      desired_out.zero(0.1);

      WheelVector actual_out(left_front_encoder.GetRate(), left_back_encoder.GetRate(), right_front_encoder.GetRate(), right_back_encoder.GetRate());

      actual_out = actual_out * RAD_TO_NORMAL;
      input = input + (desired_out - actual_out) * K;
      input.limit(1.0);

      printf("gamepad: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", desired_out.getLeftFront(), desired_out.getLeftBack(), desired_out.getRightFront(), desired_out.getRightBack());
      printf("sensors: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", actual_out.getLeftFront(), actual_out.getLeftBack(), actual_out.getRightFront(), actual_out.getRightBack());
      printf("output:  left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n\n", input.getLeftFront(), input.getLeftBack(), input.getRightFront(), input.getRightBack());
      //printf("encoder: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", 0.0, 0.0, encoder, 0.0);

      left_front.Set(input.getLeftFront());
      left_back.Set(input.getLeftBack());
      right_front.Set(input.getRightFront());
      right_back.Set(input.getRightBack());
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

