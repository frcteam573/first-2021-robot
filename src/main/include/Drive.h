

#ifndef Drive_H
#define Drive_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "Robot.h"
#include "Drive.h"
#include "rev/CANSparkMax.h"

using namespace std;

class Drive : public frc::Subsystem {

    private:
    rev::CANSparkMax * m_leftdrive;
    rev::CANSparkMax * m_rightdrive;


    public:
     Drive();     
    void Joystick_Drive(double LeftStick, double RightStick);


};
#endif