/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include "frc\Joystick.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// Include subsystem header files here
#include "Drive.h"
#include "Led.h"
#include "Appendage.h"

#include "Log.h"
#include "NetworkTables/NetworkTable.h"
#include "NetworkTables/NetworkTableInstance.h"
#include <frc/Compressor.h>



class Robot : public frc::TimedRobot {
 public:
  //Include subsystem object defenitions here
  Drive MyDrive;
  Led MyLed;
  Appendage MyAppendage;
  Log MyLog;
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  

  


 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  frc::Joystick controller1{0}; // Driver controller
  frc::Joystick controller2{1}; // Operator controller
  bool leftbuttonstate;
  bool rightbuttonstate;
  int shootercounter;
  bool buddyclimb_enable;
  bool climb_enable;
  float camera_x;
  float camera_exist;
  float image_size;
  frc::Compressor * Compressor;
};
