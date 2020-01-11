

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



using namespace std;

Appendage::Appendage() : Subsystem("Appendage") {
    // Define CAN and PWM Ids used in Drive here
    
    int controlpanelID = 0;
    int controlpanelencID_a = 4;
    int controlpanelencID_b = 5;

    // Define motors, sensors, and pneumatics here
    m_controlpanel = new frc::VictorSP(controlpanelID);
    s_controlpanel_encoder = new frc::Encoder( controlpanelencID_a, controlpanelencID_b, false, frc::Encoder::k4X);
    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    rev::ColorSensorV3 m_colorSensor{i2cPort};
    rev::ColorMatch m_colorMatcher;


    }

double Appendage::deadband(double input, double deadband_size){
    if (abs(input) < deadband_size){
        input = 0;
    }
    return input;
}

double Appendage::Threshold(double in,double thres){

  double out = in;
  if (in>thres){
    out = thres;
  }
  if(in<-1*thres){
    out = -1*thres;
  }
  return out;
}

// manual control panel control
void Appendage::control_panel(double input){
    m_controlpanel->Set(input);
}
// automatic control panel control
void Appendage::controlpanel_rotation_auto(){
    double setpoint = 100;
    double encoder_val = s_controlpanel_encoder->Get();
    double error = setpoint - encoder_val;
    error = deadband(error, 10);
    double kpe = .025;
    double output_e = error * kpe;
    //output_e = Threshold(output_e, 0.9);
    m_controlpanel->Set(output_e);
    //auto encoder_valstr = std::to_string(encoder_val);
    //frc::SmartDashboard::PutString("DB/String 3",encoder_valstr);
}

// color sensing control panel
void Appendage::controlpanel_colorsense_init(){

    static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

    m_colorMatcher->AddColorMatch(kBlueTarget);
    m_colorMatcher->AddColorMatch(kGreenTarget);
    m_colorMatcher->AddColorMatch(kRedTarget);
    m_colorMatcher->AddColorMatch(kYellowTarget);

}

void Appendage::controlpanel_colorsense_periodic(){
    std::string color_in = driverstation_color();
    if (color_in != "z"){
    static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

    m_colorMatcher->AddColorMatch(kBlueTarget);
    m_colorMatcher->AddColorMatch(kGreenTarget);
    m_colorMatcher->AddColorMatch(kRedTarget);
    m_colorMatcher->AddColorMatch(kYellowTarget);
    
    frc::Color detectedColor = m_colorSensor->GetColor();
    
    /**
     * Run the color match algorithm on our detected color
     */
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher->MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget) {
      colorString = "B";
    } else if (matchedColor == kRedTarget) {
      colorString = "R";
    } else if (matchedColor == kGreenTarget) {
      colorString = "G";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Y";
    } else {
      colorString = "Unknown";
    }

    if (colorString == color_in){
        m_controlpanel->Set(0);
    }
    else {
        m_controlpanel->Set(0.6);
    }

    /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
    /*frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);*/
    }
  }


// driver station data
std::string Appendage::driverstation_color(){
    std::string output = "z";
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    if(gameData.length() > 0)
    {
    switch (gameData[0])
    {
        case 'B' :
        output = 'B';
        //Blue case code
        break;
        case 'G' :
        output = 'G';
        //Green case code
        break;
        case 'R' :
        output = 'R';
        //Red case code
        break;
        case 'Y' :
        output = 'Y';
        //Yellow case code
        break;
        
    }
    }
    return output; 
}

