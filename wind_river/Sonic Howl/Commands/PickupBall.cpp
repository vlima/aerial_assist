// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "PickupBall.h"

//#define USE_GYRO
#define UP_ANGLE 60
#define DOWN_ANGLE 0

PickupBall::PickupBall()
{
   // Use requires() here to declare subsystem dependencies
   // eg. requires(chassis);
   // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
   Requires(Robot::pickup);
   // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void PickupBall::Initialize()
{
   _joystick2 = Robot::oi->getJoystick2();
   _joystick3 = Robot::oi->getJoystick3();
   _arm = RobotMap::pickupArm;
   _roller_arm = RobotMap::pickupRollerArm;
   _rollers = RobotMap::pickupRollers;
   _gyro = RobotMap::pickupArmAngleGyro;
   _gyro->Reset();
   _lower_limit_switch = RobotMap::lowerLimitSwitch;
   _higher_limit_switch = RobotMap::higherLimitSwitch;
   _lower_limit_switch1 = RobotMap::lowerLimitSwitch1;
   _higher_limit_switch1 = RobotMap::higherLimitSwitch1;
   _up = false;
   _down = false;
}

// Called repeatedly when this Command is scheduled to run
void PickupBall::Execute()
{
   if (_joystick2->GetRawButton(3))
   {
      _rollers->Set(Relay::kForward);
   }
   else if (_joystick2->GetRawButton(2))
   {
      _rollers->Set(Relay::kReverse);
   }
   else
   {
      _rollers->Set(Relay::kOff);
   }

#ifdef USE_GYRO		
   if (_joystick3->GetRawButton(3))
   {
      _up = true;
      _down = false;
   }
   else if (_joystick3->GetRawButton(2))
   {
      _up = false;
      _down = true;
   }

   double CurrentAngle = (double) ((int) _gyro->GetAngle() % 360);
   printf("CurrentAngle = %f\n",CurrentAngle);
   if (_up)
   {
      if (CurrentAngle - UP_ANGLE > 5)
      {
         _roller_arm->Set(-0.4);
      }
      else if (CurrentAngle - UP_ANGLE < -5)
      {
         _roller_arm->Set(0.4);
      }
      else
      {
         _roller_arm->Set(0);
      }
   }
   else if(_down)
   {
      if (CurrentAngle - DOWN_ANGLE > 10)
      {
         _roller_arm->Set(-0.4);
      }
      else if (CurrentAngle - DOWN_ANGLE < -10)
      {
         _roller_arm->Set(0.4);
      }
      else
      {
         _roller_arm->Set(0);
      }
   }
#else
   
   double rollerInput = _joystick3->GetY();
   //printf("lowerLimitSwitch = %d input = %f\n",lowerLimitSwitch->Get(),rollerInput);
   //printf("higherLimitSwitch = %d\n",higherLimitSwitch->Get());

   if ((!_lower_limit_switch1->Get() && rollerInput < 0) || (!_higher_limit_switch1->Get() && rollerInput > 0))
   {
      _roller_arm->Set(0.0);
   }
   else
   {
      _roller_arm->Set(rollerInput);
   }
#endif

   /* 
    int max_angle = 75;
    int min_angle = 10;

    double input = j2->GetY();
    double CurrentAngle = (double) ((int) gyro->GetAngle() % 360);
    SmartDashboard::PutNumber("Current Angle", CurrentAngle);
    if (input < 0.2 && input > -0.2)
    {
    if (CurrentAngle - ANGLE > 5)
    {
    arm->Set(-0.4);
    }
    else if (CurrentAngle - ANGLE < -5)
    {
    arm->Set(0.4);
    }
    else
    {
    arm->Set(0);
    }
    }
    else
    {
    if (input > 0 && CurrentAngle > max_angle)
    arm->Set(0);
    else if (input < 0 && CurrentAngle < min_angle)
    arm->Set(0);
    if (input > 0 && CurrentAngle > max_angle / 1.5)
    arm->Set((j2->getY) * 0.5);
    else if (input < 0 && CurrentAngle < min_angle * 1.5)
    arm->Set((j2->getY) * 0.5);
    else
    arm->Set(j2->GetY());
    }
    */
   double input = -_joystick2->GetY();
   //printf("lowerLimitSwitch = %d input = %f\n",lowerLimitSwitch->Get(),input);
   //printf("higherLimitSwitch = %d\n",higherLimitSwitch->Get());
   _arm->Set(input);
   //  if((!lowerLimitSwitch->Get() && input < 0 && !j2->GetRawButton(7)) ||
   //	 (!higherLimitSwitch->Get() && input > 0 && !j2->GetRawButton(7)))  
   //  {
   //	  arm->Set(0.0);
   //	  printf("input = 0.0\n");
   //  }else
   //  {
   //	  //printf("input = %d\n",input);
   //	  printf("input = %f\n",input);
   //	  arm->Set(input);
   //  }

}

// Make this return true when this Command no longer needs to run execute()
bool PickupBall::IsFinished()
{
   return false;
}

// Called once after isFinished returns true
void PickupBall::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickupBall::Interrupted()
{

}
