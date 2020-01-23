

#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

Drive::Drive() : Subsystem("Drive") {
    // Define CAN and PWM Ids used in Drive here
    //int leftdriveID = 2;
    //int leftdriveID2 = 3;
    //int rightdriveID = 4;
    //int rightdriveID2 = 5;
    int buddyclimbID = 5;
    int buddyclimbpIDa = 6;
    int buddyclimbpIDb = 7;
    int leftclimbID = 6;
    int rightclimbID = 7;

    // Define motors, sensors, and pneumatics here
    m_leftdrive = new frc::VictorSP(1); //new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    //m_leftdrive2 = new rev::CANSparkMax{leftdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    //m_leftdrive2->SetInverted(true);
    m_rightdrive = new frc::VictorSP(0); //new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
    //m_rightdrive2 = new rev::CANSparkMax{rightdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_buddyclimb = new frc::VictorSP(buddyclimbID);
    p_buddyclimb = new frc::DoubleSolenoid(1, buddyclimbpIDa, buddyclimbpIDb);
    m_leftclimb = new rev::CANSparkMax{leftclimbID, rev::CANSparkMax::MotorType::kBrushless};
    m_rightclimb = new rev::CANSparkMax{rightclimbID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftclimb->SetInverted(true);
}

double Drive::deadband(double input, double deadband_size){
    if (abs(input) < deadband_size){
        input = 0;
    }
    return input;
}
void Drive::Joystick_Drive(double LeftStick, double RightStick){
    // This function provides basic joystick control of the drive base
    
    // cubing function
    LeftStick = LeftStick * LeftStick * LeftStick;
    RightStick = RightStick * RightStick * RightStick;

    // deadband
    LeftStick = deadband (LeftStick, 0.05);
    RightStick = deadband (RightStick, 0.05);

    m_leftdrive->Set(LeftStick);
    //m_leftdrive2->Set(LeftStick);
    m_rightdrive->Set(RightStick);
    //m_rightdrive2->Set(RightStick);



}

void Drive::buddyclimb_motor(double input){

    m_buddyclimb->Set(input);

}

void Drive::buddyclimb_out(){

    p_buddyclimb->Set(frc::DoubleSolenoid::Value::kForward);

}

void Drive::buddyclimb_in(){

    p_buddyclimb->Set(frc::DoubleSolenoid::Value::kReverse);
    
}

void Drive::climb(double input){
    
    m_leftclimb->Set(input);
    m_rightclimb->Set(input);

}

bool Drive::camera_centering(float camera_x, float camera_s, double d){

    double setpoint = 0;
    double x = 30;
    

    if (camera_s < -85 && camera_s > -90){

        camera_s = camera_s + 90;

    }

    if (camera_s > -5 && camera_s < 5){

        setpoint = 90 - ((d * sin(camera_s*3.1415/180)/(d * cos(camera_s*3.14159/180) + x))*180/3.14159);

    }
    else {

        setpoint = 0;

    }

    auto setpointstr = std::to_string(setpoint);
    frc::SmartDashboard::PutString("DB/String 5", setpointstr);
    




    double error = 0 - camera_x;
    double kp_c = .025;
    double output = kp_c * error;
    
    m_leftdrive->Set(output);
    //m_leftdrive2->Set(output);
    m_rightdrive->Set(-output);
    //m_rightdrive2->Set(-output);
  
}

double Drive::camera_getdistance(float camera_y){

    double h2 = 92; // height to the center of the vision target on the goal
    double h1 = 39.75; // height of camera on robot
    double a1 = 0; // angle of the camera on the robot relative to the ground
    double a2 = camera_y;

    double d = (h2-h1)/tan((a1+a2)*3.14159/180);

    auto dstr = std::to_string(d);
    frc::SmartDashboard::PutString("DB/String 3", dstr);

}