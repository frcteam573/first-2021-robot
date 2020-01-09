

#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

Drive::Drive() : Subsystem("Drive") {
    // Define CAN and PWM Ids used in Drive here
    int leftdriveID = 2;
    int rightdriveID = 3;

    // Define motors, sensors, and pneumatics here
    m_leftdrive = new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    m_rightdrive = new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
}

void Drive::Joystick_Drive(double LeftStick, double RightStick){
    // This function provides basic joystick control of the drive base

    m_leftdrive->Set(LeftStick);
    m_rightdrive->Set(RightStick);
    
}
