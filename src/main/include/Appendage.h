

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
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc\I2C.h>
using namespace std;

class Appendage : public frc::Subsystem {

    private:
    // Define motor, sensors, and pnematic pointers here
    rev::CANSparkMax * m_controlpanel;
    frc::Encoder * s_controlpanel_encoder;
    rev::ColorSensorV3 *m_colorSensor;
    //frc::I2C * i2cPort;
    rev::ColorMatch * m_colorMatcher;

    //Any updates here also have to be done in controlpanel_colorsense_init
    static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
    static constexpr frc::Color kWhiteTarget = frc::Color(0.365, 0.464, 0.169);


    public:
     Appendage();  
     // Define Appendage class functions here   
    
     double deadband(double input, double deadband_size);
     double Threshold(double in,double thres);
     void control_panel(double input);
     void controlpanel_rotation_auto();
     void controlpanel_colorsense_periodic();
     void controlpanel_colorsense_init();
     std::string driverstation_color();
    

};
#endif