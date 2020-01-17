

#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "frc/AnalogGyro.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

Drive::Drive() : Subsystem("Drive") {
    // Define CAN and PWM Ids used in Drive here
    int leftdriveID = 2;
    int leftdriveID2 = 3;
    int rightdriveID = 4;
    int rightdriveID2 = 5;
    int leftdriveencID_a = 2;
    int leftdriveencID_b = 3;
    int rightdriveencID_a = 0;
    int rightdriveencID_b = 1;

    // Define motors, sensors, and pneumatics here
    m_leftdrive = new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive2 = new rev::CANSparkMax{leftdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    m_leftdrive2->SetInverted(true);
    m_rightdrive = new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_rightdrive2 = new rev::CANSparkMax{rightdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    s_leftdrive_enc = new frc::Encoder( leftdriveencID_a, leftdriveencID_b, false, frc::Encoder::k4X);
    s_rightdrive_enc = new frc::Encoder( rightdriveencID_a, rightdriveencID_b, false, frc::Encoder::k4X);
    s_gyro = new frc::AnalogGyro(1);
}

double Drive::deadband(double input, double deadband_size){
    if (abs(input) < deadband_size){
        input = 0;
    }
    return input;
}
void Drive::Joystick_Drive(double LeftStick, double RightStick){
    // This function provides basic joystick control of the drive base
    
    // cubing function
    LeftStick = LeftStick * LeftStick * LeftStick;
    RightStick = RightStick * RightStick * RightStick;

    // deadband
    LeftStick = deadband (LeftStick, 0.05);
    RightStick = deadband (RightStick, 0.05);

    m_leftdrive->Set(LeftStick);
    m_leftdrive2->Set(LeftStick);
    m_rightdrive->Set(RightStick);
    m_rightdrive2->Set(RightStick);



}



void Drive::drive_PID(double setpoint_left_pos, double setpoint_right_pos, double setpoint_left_speed, double setpoint_right_speed, double heading, int count) {
  
  if(count ==0){
    //Gyro->Reset();
    s_leftdrive_enc->Reset();
    s_rightdrive_enc->Reset();
  }
  double encoder_val_left = s_leftdrive_enc->Get();
  double encoder_val_right = s_rightdrive_enc->Get();
  //double encoder_speed_left = s_leftdrive_enc->GetRate();
  //double encoder_speed_right = s_rightdrive_enc->GetRate();
  double gyro_val = s_gyro->GetAngle();

  double error_left_pos = setpoint_left_pos - encoder_val_left;
  double error_right_pos = setpoint_right_pos - encoder_val_right;
  //double error_left_speed = setpoint_left_speed - encoder_speed_left;
  //double error_right_speed = setpoint_right_speed - encoder_speed_right;
  double error_heading = heading - gyro_val;

  double max_speed = 13; //ft/s
  double kp_speed = -1/max_speed;
  double kp_pos = -0.025;
  double kph = -0.01;  //0.01;

  double output_left = (error_left_pos * kp_pos) + kp_speed*setpoint_left_speed;
  double output_right = (error_right_pos * kp_pos) + kp_speed*setpoint_right_speed;

  double turn_val = kph * error_heading;
  //double output_left = (error_left_pos * kp_pos) + (error_left_speed * kp_speed) * .05;
  //double output_right = (error_right_pos * kp_pos) + (error_right_speed * kp_speed) * .05;

  m_leftdrive->Set(output_left + turn_val);
  m_leftdrive2->Set(output_left + turn_val);
  m_rightdrive->Set(output_right - turn_val);
  m_rightdrive2->Set(output_right - turn_val);

  /*auto Left_encoderstr = std::to_string(output_left);
  frc::SmartDashboard::PutString("DB/String 6",Left_encoderstr);
  auto Right_encoderstr = std::to_string(error_left_pos);
  frc::SmartDashboard::PutString("DB/String 7",Right_encoderstr);
  Right_encoderstr = std::to_string(setpoint_left_pos);
  frc::SmartDashboard::PutString("DB/String 8",Right_encoderstr);
  Right_encoderstr = std::to_string(setpoint_left_speed);
  frc::SmartDashboard::PutString("DB/String 9",Right_encoderstr);*/
}