// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Drive.h"

Drive::Drive() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void Drive::Initialize() {
	drive_stick = Robot::oi->getJoystick1();
	left_front = RobotMap::chassisleft_front;
	left_back = RobotMap::chassisleft_back;
	right_front = RobotMap::chassisright_front;
	right_back = RobotMap::chassisright_back;
	   
}
// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
   
   // Joystick
   desired_out = WheelVector::calc(drive_stick->GetX(), drive_stick->GetY(), drive_stick->GetTwist());
   desired_out.zero(0.1);
   // Sensors
//   WheelVector actual_out(-left_front_encoder.GetRate(), -left_back_encoder.GetRate(), -right_front_encoder.GetRate(),
//         -right_back_encoder.GetRate());
//   actual_out = actual_out * RAD_TO_NORMAL;
//   // Error
//   WheelVector error = desired_out - actual_out;
//   // Feedback
//   input = input + error * K;
//   input.limit(1.0);
   // desired_out.correct(error, input, 0.1);
   // Controllers
   left_front->Set(desired_out.getLeftFront());
   left_back->Set(desired_out.getLeftBack());
   right_front->Set(desired_out.getRightFront());
   right_back->Set(desired_out.getRightBack());
	
}
// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void Drive::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {
}
