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

#define ANGLE 30

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
   j2 = Robot::oi->getJoystick2();
   arm = RobotMap::pickupArm;
   rollers = RobotMap::pickupRollers;
   gyro = RobotMap::pickupArmAngleGyro;
   gyro->Reset();
}

// Called repeatedly when this Command is scheduled to run
void PickupBall::Execute()
{
  if (j2->GetRawButton(3))
   {
      rollers->Set(Relay::kForward);
   }
   else if (j2->GetRawButton(2))
   {
      rollers->Set(Relay::kReverse);
   }
   else
   {
      rollers->Set(Relay::kOff);
   }
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
  double input = j2->GetY();
  if ((RobotMap::lowerLimitSwitch->Get() && input > 0) ||
      (RobotMap::higherLimitSwitch->Get() && input < 0))
  {
     arm->Set(j2->GetY());
  }

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
