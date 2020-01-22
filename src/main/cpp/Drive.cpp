

#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

Drive::Drive() : Subsystem("Drive") {
    // Define CAN and PWM Ids used in Drive here
    int leftdriveID = 2;
    int leftdriveID2 = 3;
    int rightdriveID = 4;
    int rightdriveID2 = 5;
    int buddyclimbID = 5;
    int buddyclimbpIDa = 6;
    int buddyclimbpIDb = 7;

    // Define motors, sensors, and pneumatics here
    m_leftdrive = new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive2 = new rev::CANSparkMax{leftdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    m_leftdrive2->SetInverted(true);
    m_rightdrive = new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_rightdrive2 = new rev::CANSparkMax{rightdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_buddyclimb = new frc::VictorSP(buddyclimbID);
    p_buddyclimb = new frc::DoubleSolenoid(1, buddyclimbpIDa, buddyclimbpIDb);
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
    m_leftdrive2->Set(LeftStick);
    m_rightdrive->Set(RightStick);
    m_rightdrive2->Set(RightStick);



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