#ifndef Paths_H
#define Paths_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Encoder.h"
#include "Robot.h"
#include "Paths.h"
#include <frc/ADXRS450_Gyro.h>

#include <frc/commands/Subsystem.h>


using namespace std;

class Paths : public frc::Subsystem {

 private:


 public:
  Paths();
  double ReturnTableVal(int count, int select);
 

};
#endif 