

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
#include <frc/DoubleSolenoid.h>



using namespace std;

Appendage::Appendage() : Subsystem("Appendage") {
    // Define CAN and PWM Ids used in Drive here
    
    int controlpanelID = 0;
    int controlpanelencID_a = 4;
    int controlpanelencID_b = 5;
    int intakeIDa = 0;
    int intakeIDb = 1;
    int intakeIDc = 8;

    // Define motors, sensors, and pneumatics here
    m_controlpanel = new frc::VictorSP(controlpanelID);
    s_controlpanel_encoder = new frc::Encoder( controlpanelencID_a, controlpanelencID_b, false, frc::Encoder::k4X);
    //i2cPort = new frc::I2C;
    m_colorSensor = new rev::ColorSensorV3(frc::I2C::Port::kOnboard);
    m_colorMatcher = new rev::ColorMatch;
    m_intake = new frc::VictorSP(intakeIDc);
    p_intake = new frc::DoubleSolenoid(1, intakeIDa, intakeIDb);


    }
double Appendage::deadband(double input, double deadband_size){
  // Deadband function - Takes input and checks it againist a provided deadband
  // then returns the value or zero depending if it is within or outside of the deadband.
    if (abs(input) < deadband_size){
        input = 0;
    }
    return input;
}

double Appendage::Threshold(double in,double thres){
// Threshold function - Takes and input and crops it based upon and the provided threshold value
// Works with positive and negative inputs. Threshold value should always be positive.
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
  // Spins the control panel 4 times automatically. Assumes control panel encoder is set to 
  // zero when the function is called.
    double setpoint = 100; // Must be updated once mechanism is created.
    double encoder_val = s_controlpanel_encoder->Get(); // Get encoder value
    double error = setpoint - encoder_val; // Calculate current error
    error = deadband(error, 10); // Apply a deadband to help overshoot.
    double kpe = .025; // P gain
    double output_e = error * kpe; // Calculate motor value
    //output_e = Threshold(output_e, 0.9); // Threshold motor value
    m_controlpanel->Set(output_e); // Set motor to value
    //auto encoder_valstr = std::to_string(encoder_val);
    //frc::SmartDashboard::PutString("DB/String 3",encoder_valstr);
}

// color sensing control panel
void Appendage::controlpanel_colorsense_init(){


  //Any updates here also have to be done in Appendage.h
  static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
  static constexpr frc::Color kWhiteTarget = frc::Color(0.365, 0.464, 0.169);

  m_colorMatcher->AddColorMatch(kBlueTarget);
  m_colorMatcher->AddColorMatch(kGreenTarget);
  m_colorMatcher->AddColorMatch(kRedTarget);
  m_colorMatcher->AddColorMatch(kYellowTarget);
  m_colorMatcher->AddColorMatch(kWhiteTarget);

}

void Appendage::controlpanel_colorsense_periodic(){
    // Fucntion spins contorl panel to specified color recieved from driver station
    std::string color_in = driverstation_color(); // Get color from driver station
    if (color_in != "z"){

      frc::Color detectedColor = m_colorSensor->GetColor();
    
    // Get raw RGB values from color sensor and display on DS
    /*frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    auto encoder_valstr = std::to_string(detectedColor.red);
    frc::SmartDashboard::PutString("DB/String 0",encoder_valstr);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    auto encoder_valstr1 = std::to_string(detectedColor.blue);
    frc::SmartDashboard::PutString("DB/String 1",encoder_valstr1);
    auto encoder_valstr2 = std::to_string(detectedColor.green);
    frc::SmartDashboard::PutString("DB/String 2",encoder_valstr2); */
      
    //Run the color match algorithm on our detected color

      std::string colorString;
      double confidence = 0.99;

      frc::Color matchedColor = m_colorMatcher->MatchClosestColor(detectedColor, confidence); // Determine color

      if (matchedColor == kBlueTarget) {
        colorString = "B";
      } else if (matchedColor == kRedTarget) {
        colorString = "R";
      } else if (matchedColor == kGreenTarget) {
        colorString = "G";
      } else if (matchedColor == kYellowTarget) {
        colorString = "Y";
      } else if (matchedColor == kWhiteTarget) {
        colorString = "W";
      } else {
        colorString = "Unknown";
      }
      //Display what color is seen on DS
      frc::SmartDashboard::PutString("DB/String 5", colorString);
      if (colorString == color_in){
          m_controlpanel->Set(0); // If color matches desired stop motor
      }
      else {
          m_controlpanel->Set(0.6); // if color doesn't match desired color keep spinning
      }
    }
  }


// driver station data
std::string Appendage::driverstation_color(){
    // This function reads desired color in from driver station or gives a placeholder if no color is given.
    std::string output = "z"; // Create default value
    std::string gameData;
    gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage(); // Read in message
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

void Appendage::intakemotor(double input){

    m_intake->Set(input);

}

void Appendage::intake_out(){

    p_intake->Set(frc::DoubleSolenoid::Value::kForward);

}

void Appendage::intake_in(){

    p_intake->Set(frc::DoubleSolenoid::Value::kReverse);
    
}