#ifndef Log_H
#define Log_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "frc/Spark.h"
#include "Robot.h"
#include "Log.h"
#include "frc/PowerDistributionPanel.h"

using namespace std;

class Log : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here

    public:
    Log();  
     // Define Log class functions here 
    void Dashboard();
    void PDPTotal();
    void CurrentCompare(int slot,double PWMin);
};

#endif
