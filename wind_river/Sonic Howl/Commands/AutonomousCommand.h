// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousCommand: public Command
{
public:
   AutonomousCommand();
   virtual void Initialize();
   virtual void Execute();
   virtual bool IsFinished();
   virtual void End();
   virtual void Interrupted();

private:
   enum AutoStates { STATE_POSITIONING, STATE_EXTEND_ARMS, STATE_PICKUP_BALL, STATE_AIM, STATE_SHOOT, STATE_WINING_THE_GAME };
   
   // Forward
   double _positioning_count;
   double _positioning_speed;
   // Extend
   double _extend_rollers_count;
   double _extend_rollers_speed;
   double _extend_arm_count;
   double _extend_arm_speed;
   // Pickup
   double _pickup_move_count;  
   double _pickup_move_speed;
   double _pickup_roller_count;
   // Aim
   double _aim_move_count;  
   double _aim_move_speed;
   double _aim_arm_count;  
   double _aim_arm_speed;
   double _aim_roller_count;
   // Shoot
   double _shoot_arm_count;  
   double _shoot_arm_speed;
   double _shoot_delay_count;
   double _shoot_speed;

   // States
   AutoStates _state;
   int _count;
   
   SpeedController* _left_front;
   SpeedController* _left_back;
   SpeedController* _right_front;
   SpeedController* _right_back;
   SpeedController *_arm;
   SpeedController *_roller_arm;
   Relay *_rollers;
   DigitalInput *_lower_limit_switch;
   DigitalInput *_higher_limit_switch;
   SpeedController *_launcher;
   Gyro *gyro;

   void SetArm(double speed);
   void PositioningState();
   void ExtendArmsState();
   void PickupBallState();
   void AimState();
   void ShootState();
   void WinningState();
};

#endif
