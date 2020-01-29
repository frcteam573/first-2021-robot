

#ifndef Appendage_H
#define Appendage_H

#pragma once

#include <frc/commands/Subsystem.h>
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "Robot.h"
#include "Appendage.h"
#include "frc\Encoder.h"
#include <frc/util/color.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include <frc/DriverStation.h>
#include "rev/CANSparkMax.h"


using namespace std;

class Appendage : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here
    frc::VictorSP * m_controlpanel;
    frc::Encoder * s_controlpanel_encoder;
    rev::ColorSensorV3 *m_colorSensor;
    rev::ColorMatch * m_colorMatcher;
    rev::CANSparkMax * m_shooter;
    rev::CANSparkMax * m_shooter2;
    frc::Encoder * s_shooter_encoder;


    

    public:
     Appendage();  
     // Define Appendage class functions here   
    
     double deadband(double input, double deadband_size);
     double Threshold(double in,double thres);
     void control_panel(double input);
     void controlpanel_rotation_auto();
     void controlpanel_colorsense_periodic();
     //void controlpanel_colorsense_init();
     std::string driverstation_color();
    void shooter_pid (double setpoint);
    

};
#endif