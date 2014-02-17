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

   Joystick drive_stick;
   Joystick pickup_stick;
   Joystick launch_stick;
   Gyro gyro;
   Talon left_front;
   Talon left_back;
   Talon right_front;
   Talon right_back;
   Jaguar pickup;
   Encoder left_front_encoder;
   Encoder left_back_encoder;
   Encoder right_front_encoder;
   Encoder right_back_encoder;
   WheelVector input;
   WheelVector desired_out;
   LiveWindow *window;

public:
   RobotDemo() :

      drive_stick(1), pickup_stick(2), launch_stick(3), gyro(1), left_front(1), left_back(2), right_front(3), right_back(4), pickup(5),
            left_front_encoder(1, 2), left_back_encoder(3, 4), right_front_encoder(5, 6), right_back_encoder(7, 8)
   {
      this->SetPeriod(0); //Set update period to sync with robot control packets (20ms nominal)

      left_front_encoder.SetDistancePerPulse(1.0);
      left_front_encoder.SetPIDSourceParameter(Encoder::kRate);
      left_front_encoder.Start();

      left_back_encoder.SetDistancePerPulse(1.0);
      left_back_encoder.SetPIDSourceParameter(Encoder::kRate);
      left_back_encoder.Start();

      right_front_encoder.SetDistancePerPulse(1.0);
      right_front_encoder.SetPIDSourceParameter(Encoder::kRate);
      right_front_encoder.Start();

      right_back_encoder.SetDistancePerPulse(1.0);
      right_back_encoder.SetPIDSourceParameter(Encoder::kRate);
      right_back_encoder.Start();

      window = LiveWindow::GetInstance();
      window->AddSensor("Chasis", "Left-front-encoder", &left_front_encoder);
      window->AddSensor("Chasis", "Left-back-encoder", &left_back_encoder);
      window->AddSensor("Chasis", "Right-front-encoder", &right_front_encoder);
      window->AddSensor("Chasis", "Right-back-encoder", &right_back_encoder);

      window->AddActuator("Chasis", "Left-front-actuator", &left_front);
      window->AddActuator("Chasis", "Left-back-actuator", &left_back);
      window->AddActuator("Chasis", "Right-front-actuator", &right_front);
      window->AddActuator("Chasis", "Right-back-actuator", &right_back);
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
      gyro.Reset();
   }

   /**
    * Periodic code for teleop mode should go here.
    *
    * Use this method for code which will be called periodically at a regular
    * rate while the robot is in teleop mode.
    */
   void RobotDemo::TeleopPeriodic()
   {
      // Joystick
      desired_out = WheelVector::calc(drive_stick.GetX(), drive_stick.GetY(), drive_stick.GetTwist());
      desired_out.zero(0.1);
      // Sensors
      WheelVector actual_out(-left_front_encoder.GetRate(), -left_back_encoder.GetRate(), -right_front_encoder.GetRate(),
            -right_back_encoder.GetRate());
      actual_out = actual_out * RAD_TO_NORMAL;
      // Error
      WheelVector error = desired_out - actual_out;
      // Feedback
      input = input + error * K;
      input.limit(1.0);
      // desired_out.correct(error, input, 0.1);
      // Controllers
      left_front.Set(desired_out.getLeftFront());
      left_back.Set(desired_out.getLeftBack());
      right_front.Set(desired_out.getRightFront());
      right_back.Set(desired_out.getRightBack());

      // Pickup arm
      pickup.Set(pickup_stick.GetY());

      // Launcher
      pickup.Set(pickup_stick.GetY());

      // DEBUG
      printf("pickup:    %0.2f\n", pickup_stick.GetY());
      printf("gyro:      %0.2f\n", gyro.GetAngle());
      printf("desired:   left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", desired_out.getLeftFront(), desired_out.getLeftBack(),
            desired_out.getRightFront(), desired_out.getRightBack());
      printf("sensors:   left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", actual_out.getLeftFront(), actual_out.getLeftBack(),
            actual_out.getRightFront(), actual_out.getRightBack());
      printf("error:     left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", error.getLeftFront(), error.getLeftBack(),
            error.getRightFront(), error.getRightBack());
      printf("actuators: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n\n", input.getLeftFront(), input.getLeftBack(),
            input.getRightFront(), input.getRightBack());
      //printf("encoder: left(%0.2f, %0.2f), right(%0.2f, %0.2f)\n", 0.0, 0.0, encoder, 0.0);

      SmartDashboard::PutNumber("pickup", pickup_stick.GetY());
      SmartDashboard::PutNumber("gyro", gyro.GetAngle());
      SmartDashboard::PutNumber("desired(left-back)", desired_out.getLeftBack());

      SmartDashboard::PutNumber("desired(left-front)", desired_out.getLeftFront());
      SmartDashboard::PutNumber("desired(left-back)", desired_out.getLeftBack());
      SmartDashboard::PutNumber("desired(right-front)", desired_out.getRightFront());
      SmartDashboard::PutNumber("desired(right-back)", desired_out.getRightBack());

      SmartDashboard::PutNumber("sensor(left-front)", actual_out.getLeftFront());
      SmartDashboard::PutNumber("sensor(left-back)", actual_out.getLeftBack());
      SmartDashboard::PutNumber("sensor(right-front)", actual_out.getRightFront());
      SmartDashboard::PutNumber("sensor(right-back)", actual_out.getRightBack());

      SmartDashboard::PutNumber("error(left-front)", error.getLeftFront());
      SmartDashboard::PutNumber("error(left-back)", error.getLeftBack());
      SmartDashboard::PutNumber("error(right-front)", error.getRightFront());
      SmartDashboard::PutNumber("error(right-back)", error.getRightBack());

      SmartDashboard::PutNumber("feedback(left-front)", input.getLeftFront());
      SmartDashboard::PutNumber("feedback(left-back)", input.getLeftBack());
      SmartDashboard::PutNumber("feedback(right-front)", input.getRightFront());
      SmartDashboard::PutNumber("feedback(right-back)", input.getRightBack());

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

