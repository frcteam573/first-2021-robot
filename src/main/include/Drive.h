

#ifndef Drive_H
#define Drive_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "frc/AnalogGyro.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

class Drive : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here
    rev::CANSparkMax * m_leftdrive;
    rev::CANSparkMax * m_leftdrive2;
    rev::CANSparkMax * m_rightdrive;
    rev::CANSparkMax * m_rightdrive2;
    frc::Encoder * s_leftdrive_enc;
    frc::Encoder * s_rightdrive_enc;
    frc::AnalogGyro * s_gyro;

    public:
     Drive();  
     // Define Drive class functions here   
     void Joystick_Drive(double LeftStick, double RightStick);
     double deadband(double input, double deadband_size);
     void drive_PID(double setpoint_left_pos, double setpoint_right_pos, double setpoint_left_speed, double setpoint_right_speed, double heading, int count);
    

};
#endif