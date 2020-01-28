

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



using namespace std;

Appendage::Appendage() : Subsystem("Appendage") {
    // Define CAN and PWM Ids used in Drive here
    
    int controlpanelID = 0;
    int controlpanelencID_a = 4;
    int controlpanelencID_b = 5;
    int shooterID = 2;
    int shooterID3 = 3;
    int shooterencID_a = 6;
    int shooterencID_b = 7;

    // Define motors, sensors, and pneumatics here
    m_controlpanel = new frc::VictorSP(controlpanelID);
    s_controlpanel_encoder = new frc::Encoder( controlpanelencID_a, controlpanelencID_b, false, frc::Encoder::k4X);
    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    rev::ColorSensorV3 m_colorSensor{i2cPort};
    rev::ColorMatch m_colorMatcher;
    m_shooter = new frc::VictorSP(shooterID);
    s_shooter_encoder = new frc::Encoder( shooterencID_a, shooterencID_b, false, frc::Encoder::k4X);
    m_shooter2 = new frc::VictorSP(shooterID3);
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
/*void Appendage::controlpanel_colorsense_init(){

  // Probably isn't needed. This stuff was added to peridoic function.
    
    static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

    m_colorMatcher->AddColorMatch(kBlueTarget);
    m_colorMatcher->AddColorMatch(kGreenTarget);
    m_colorMatcher->AddColorMatch(kRedTarget);
    m_colorMatcher->AddColorMatch(kYellowTarget);

}*/

void Appendage::controlpanel_colorsense_periodic(){
    // Fucntion spins contorl panel to specified color recieved from driver station
    std::string color_in = driverstation_color(); // Get color from driver station
    if (color_in != "z"){
      //Setup possible colors
      static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
      static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
      static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
      static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
      
      // Add colors to color matcher
      m_colorMatcher->AddColorMatch(kBlueTarget);
      m_colorMatcher->AddColorMatch(kGreenTarget);
      m_colorMatcher->AddColorMatch(kRedTarget);
      m_colorMatcher->AddColorMatch(kYellowTarget);
      
      frc::Color detectedColor = m_colorSensor->GetColor(); // Get color from sensor
      
      
      //Run the color match algorithm on our detected color

      std::string colorString;
      double confidence = 0.0;

      frc::Color matchedColor = m_colorMatcher->MatchClosestColor(detectedColor, confidence); // Determine color

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
          m_controlpanel->Set(0); // If color matches desired stop motor
      }
      else {
          m_controlpanel->Set(0.6); // if color doesn't match desired color keep spinning
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
void Appendage::shooter_pid(double setpoint){
    s_shooter_encoder->SetDistancePerPulse(1.0/1024.0);
    double encoder_val = s_shooter_encoder->GetRate(); // Get encoder value
    encoder_val = encoder_val*60;
    double error = setpoint - encoder_val; // Calculate current error
    error = deadband(error, 10); // Apply a deadband to help overshoot.
    double kpe = .0005; // P gain
    double output_e = error * kpe; // Calculate motor value
    //output_e = Threshold(output_e, 0.9); // Threshold motor value
    m_shooter->Set(output_e+.25); // Set motor to value
    m_shooter2->Set(output_e+.25);
    auto encoder_valstr = std::to_string(encoder_val);
    frc::SmartDashboard::PutString("DB/String 3",encoder_valstr);
    auto encoder_valstr2 = std::to_string(setpoint);
    frc::SmartDashboard::PutString("DB/String 2",encoder_valstr2);
    auto encoder_valstr3 = std::to_string(output_e+.25);
    frc::SmartDashboard::PutString("DB/String 1",encoder_valstr3);
}
