

#ifndef Drive_H
#define Drive_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
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
    frc::VictorSP * m_buddyclimb;
    frc::DoubleSolenoid * p_buddyclimb;
    

    public:
     Drive();  
     // Define Drive class functions here   
     void Joystick_Drive(double LeftStick, double RightStick);
     double deadband(double input, double deadband_size);
     void buddyclimb_motor(double input);
     void buddyclimb_out();
     void buddyclimb_in();
    

};
#endif