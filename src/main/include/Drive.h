

#ifndef Drive_H
#define Drive_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

class Drive : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here
    rev::CANSparkMax * m_leftdrive;
    rev::CANSparkMax * m_rightdrive;


    public:
     Drive();  
     // Define Drive class functions here   
     void Joystick_Drive(double LeftStick, double RightStick);


};
#endif