

#ifndef Led_H
#define Led_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "frc/Spark.h"
#include "Robot.h"
#include "Led.h"


using namespace std;

class Led : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here
    frc::Spark * m_leds;


    public:
    Led();  
     // Define Led class functions here 
     void led_control(std::string input);

};
#endif