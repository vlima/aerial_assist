// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::chassisleft_front = NULL;
Encoder* RobotMap::chassisleft_front_encoder = NULL;
SpeedController* RobotMap::chassisleft_back = NULL;
Encoder* RobotMap::chassisleft_back_encoder = NULL;
SpeedController* RobotMap::chassisright_front = NULL;
Encoder* RobotMap::chassisright_front_encoder = NULL;
SpeedController* RobotMap::chassisright_back = NULL;
Encoder* RobotMap::chassisright_back_encoder = NULL;
SpeedController* RobotMap::pickupArm = NULL;
Relay* RobotMap::pickupRollers = NULL;
Gyro* RobotMap::pickupArmAngleGyro = NULL;
SpeedController* RobotMap::launcherLauncherController = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	chassisleft_front = new Talon(1, 1);
	lw->AddActuator("Chassis", "left_front", (Talon*) chassisleft_front);
	
	chassisleft_front_encoder = new Encoder(1, 1, 1, 2, false, Encoder::k4X);
	lw->AddSensor("Chassis", "left_front_encoder", chassisleft_front_encoder);
	chassisleft_front_encoder->SetDistancePerPulse(1.0);
        chassisleft_front_encoder->SetPIDSourceParameter(Encoder::kRate);
        chassisleft_front_encoder->Start();
	chassisleft_back = new Talon(1, 2);
	lw->AddActuator("Chassis", "left_back", (Talon*) chassisleft_back);
	
	chassisleft_back_encoder = new Encoder(1, 3, 1, 4, false, Encoder::k4X);
	lw->AddSensor("Chassis", "left_back_encoder", chassisleft_back_encoder);
	chassisleft_back_encoder->SetDistancePerPulse(1.0);
        chassisleft_back_encoder->SetPIDSourceParameter(Encoder::kRate);
        chassisleft_back_encoder->Start();
	chassisright_front = new Talon(1, 3);
	lw->AddActuator("Chassis", "right_front", (Talon*) chassisright_front);
	
	chassisright_front_encoder = new Encoder(1, 5, 1, 6, false, Encoder::k4X);
	lw->AddSensor("Chassis", "right_front_encoder", chassisright_front_encoder);
	chassisright_front_encoder->SetDistancePerPulse(1.0);
        chassisright_front_encoder->SetPIDSourceParameter(Encoder::kRate);
        chassisright_front_encoder->Start();
	chassisright_back = new Talon(1, 4);
	lw->AddActuator("Chassis", "right_back", (Talon*) chassisright_back);
	
	chassisright_back_encoder = new Encoder(1, 7, 1, 8, false, Encoder::k4X);
	lw->AddSensor("Chassis", "right_back_encoder", chassisright_back_encoder);
	chassisright_back_encoder->SetDistancePerPulse(1.0);
        chassisright_back_encoder->SetPIDSourceParameter(Encoder::kRate);
        chassisright_back_encoder->Start();
	pickupArm = new Jaguar(1, 6);
	lw->AddActuator("Pickup", "Arm", (Jaguar*) pickupArm);
	
	pickupRollers = new Relay(1, 1);
	lw->AddActuator("Pickup", "Rollers", pickupRollers);
	
	pickupArmAngleGyro = new Gyro(1, 1);
	lw->AddSensor("Pickup", "ArmAngleGyro", pickupArmAngleGyro);
	pickupArmAngleGyro->SetSensitivity(0.007);
	launcherLauncherController = new Victor(1, 5);
	lw->AddActuator("Launcher", "LauncherController", (Victor*) launcherLauncherController);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}