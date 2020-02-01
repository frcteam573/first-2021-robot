/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------
------------------------------NAMING CONVENTION---------------------------------

MOTORS: m_function  ex: m_leftdrive
SENSORS: s_type  ex: s_gyro
CONTROLLERS: c#_type_name  ex: c1_btn_a
PNEUMATICS: p_type
BRANCHES OF CODE: section/what you're working on     ex: Drive/JoystickControl
                  also: merge into master before each event, create event, create 
                  event branch and merge every night
--------------------------------------------------------------------------------
*/
#include "Robot.h"
#include "Drive.h"
#include "Led.h"
#include "Appendage.h"
#include "NetworkTables/NetworkTable.h"
#include "NetworkTables/NetworkTableInstance.h"
#include <iostream>
#include "Log.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Compressor.h>

void Robot::RobotInit() {
  bool leftbuttonstate = false;
  bool rightbuttonstate = false;
  int shootercounter = 0;
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Set default positions and values upon start up.
  MyDrive.buddyclimb_in();
  bool buddyclimb_enable = false;
  MyDrive.buddyclimb_motor(0);
  bool climb_enable = false;
  MyDrive.shift_low();
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  
}


/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {

  MyAppendage.controlpanel_colorsense_init(); //Initalize the color sensor
  
}

void Robot::TeleopPeriodic() {


// Read in camera Stuff
  
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  
  table->PutNumber("ledMode", 0);
  table->PutNumber("camMode", 0);

  // -----------PIPELINE STUFF-----------//
  table->PutNumber("pipeline", 0);

  //--------CAMERA VALUES-----------------//
  float camera_x = table->GetNumber("tx", 0);
  float camera_exist = table->GetNumber("tv", 0);
  float image_size = table->GetNumber("ta", 0);
  float camera_y = table->GetNumber("ty", 0);
  float camera_s = table->GetNumber("ts", 0);

  // values to dashboard
  auto leftinstr = std::to_string(camera_x);
  frc::SmartDashboard::PutString("Limelight-TX", leftinstr);

  auto sstr = std::to_string(camera_s);
  frc::SmartDashboard::PutString("Limelight-TS", sstr);

  auto ystr = std::to_string(camera_y);
  frc::SmartDashboard::PutString("Limelight-TY", ystr);
  
  double d = MyDrive.camera_getdistance(camera_y);

  auto dstr = std::to_string(d);
  frc::SmartDashboard::PutString("Limelight-Distance", dstr);

  //create compressor

  Compressor = new frc::Compressor(1);


  

  //********** Read in Joystick Values ******************************************
  //------------- Driver Controller ---------------------------------------------

  double c1_joy_leftdrive = controller1.GetRawAxis(1);
  double c1_joy_rightdrive = controller1.GetRawAxis(5);
  bool c1_btn_back = controller1.GetRawButton(7);
  bool c1_btn_start = controller1.GetRawButton(8);
  double c1_righttrigger = controller1.GetRawAxis(3);
  double c1_lefttrigger = controller1.GetRawAxis(2);
  bool c1_leftbmp = controller1.GetRawButton(5);
  bool c1_rightbmp = controller1.GetRawButton(6);
  bool c1_btn_b = controller1.GetRawButton(2);

  //-----------------------------------------------------------------------------
  //------------ Operator Controller --------------------------------------------
  bool c2_btn_a = controller2.GetRawButton(1);
  bool c2_btn_b = controller2.GetRawButton(2);
  bool c2_btn_y = controller2.GetRawButton(4);
  bool c2_btn_x = controller2.GetRawButton(3);
  bool c2_btn_lb = controller2.GetRawButton(5);
  bool c2_btn_rb = controller2.GetRawButton(6);
  double c2_dpad = controller2.GetPOV(0);
  bool c2_btn_back = controller2.GetRawButton(7);
  bool c2_btn_start = controller2.GetRawButton(8);
  bool c2_rightbumper = controller2.GetRawButton(6);
  bool c2_leftbumper = controller2.GetRawButton(5);
  bool c2_right_trigger = controller2.GetRawAxis(3);
  bool c2_left_trigger = controller2.GetRawAxis(2);

  //----------------------------------------------------------------------------
  // ***************************************************************************
  //************* Drive Code ***************************************************

  bool aligned = false;
  
  if (c1_btn_b && camera_exist == 1){

    aligned = MyDrive.camera_centering(camera_x, camera_s, d);
    
  }
  else {

    MyDrive.Joystick_Drive(c1_joy_leftdrive,c1_joy_rightdrive); // Basic joystick drive
    

  }
  
  

  //------------ Shifting Logic ----------------------------------------
  if (c1_leftbmp){
    MyDrive.shift_low();

  }
  else if (c1_rightbmp){
    MyDrive.shift_high();
  }
  else {
    MyDrive.shift_auto();
  }
  //--------------------------------------------------------------------
//******************************************************************************
//************* Appendage Code *************************************************

  

//--------------- control panel ------------------------------------------------- 
if (!buddyclimb_enable){

    if (c2_btn_b){
      MyAppendage.control_panel(0.6);
    }
    else if (c2_btn_y){
      MyAppendage.controlpanel_rotation_auto();
    }
    else if (c2_btn_x){
      MyAppendage.controlpanel_colorsense_periodic();
    }
    else {
      MyAppendage.control_panel(0);
    }

  }
//-----------------------------------------------------------------------------
//----------- buddy climb ----------------------------------------------------- 

if (c2_btn_back && c2_btn_start){

  buddyclimb_enable = true;

}

if (buddyclimb_enable){

    if (c2_btn_b){
      MyDrive.buddyclimb_in();
    }
    else if (c2_btn_y){
      MyDrive.buddyclimb_out();
    }
    if (c2_btn_a){
      MyDrive.buddyclimb_motor(0.8);
    }
    else {
      MyDrive.buddyclimb_motor(0);
    }

}
//------------------------------------------------------------------------
//----------- climber code -----------------------------------------------

if (c1_btn_back && c1_btn_start){

  climb_enable = true;

}

if (climb_enable){
  

  if (c1_lefttrigger > 0.5 && c1_righttrigger < 0.5){

    MyDrive.climb(0.7);

  }
  if (c1_lefttrigger < 0.5 && c1_righttrigger > 0.5){

    MyDrive.climb(-0.7);
  }
}


// ---- shooter trim value ---------//
if (c2_dpad > 45 && c2_dpad < 135){
  if (!leftbuttonstate){
    leftbuttonstate = true;
    shootercounter--;
  }
}
else{leftbuttonstate=false;}
if (c2_dpad > 225 && c2_dpad < 315){
  if (!rightbuttonstate){
  
    rightbuttonstate = true;
    shootercounter++;
  }
}
else {rightbuttonstate=false;}


//intake code
if(c2_rightbumper){ 
  MyAppendage.intake_out();
  MyAppendage.intakemotor(0.8);
  MyAppendage.conveyor_motor(0.8);
  MyAppendage.conveyor_close();
}

else if (c2_leftbumper){
  MyAppendage.intakemotor(-0.8);
  MyAppendage.conveyor_motor(-0.8);
  MyAppendage.conveyor_close();
}
else {
  MyAppendage.intakemotor(0);
  MyAppendage.intake_in();
  MyAppendage.conveyor_open();
}


// ---------- compressor start/stop --------------------

if (climb_enable || c2_left_trigger > 0.5){

  Compressor->Stop();
}
else {

  Compressor->Start();
}



//------------------------------------------------------------
//----------shooter modes-------------------------------------

bool wheel_speed = false;
auto shootertrimstr = std::to_string(shootercounter);
frc::SmartDashboard::PutString("Shooter Trim", shootertrimstr);
if (c2_left_trigger > 0.5){

  wheel_speed = MyAppendage.shooter_pid(d, shootercounter);
  
  if (aligned && wheel_speed && c2_right_trigger > 0.5){

    MyAppendage.conveyor_motor(0.8);
  
  }
  else {

    MyAppendage.conveyor_motor(0);

  }

}
//---------------------LED CODE----------------------------------
bool ready_to_fire = false;
if (camera_exist && aligned && wheel_speed){

  MyLed.led_control("Hot_Pink");
  ready_to_fire = true;
  
}
else if ((camera_exist && !aligned && wheel_speed) || (camera_exist && aligned && !wheel_speed)){

  MyLed.led_control("Blue");
  
}

else if (camera_exist && !aligned && !wheel_speed){

  MyLed.led_control("White");
  
}
else {

  MyLed.led_control("Black");
  
}
bool camera_exist1 = false;
if (camera_exist == 1){
  camera_exist1 = true;
}

  frc::SmartDashboard::PutBoolean("Ready to Fire", ready_to_fire);
  frc::SmartDashboard::PutBoolean("In Camera", camera_exist1);
  frc::SmartDashboard::PutBoolean("Wheel at Speed", wheel_speed);
  frc::SmartDashboard::PutBoolean("Aligned", aligned);

// --------- dashboard code ---------------

MyLog.Dashboard();
MyLog.PDPTotal();
MyDrive.dashboard();
MyAppendage.dashboard();



} // End of TeleOpPeriodic


void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
