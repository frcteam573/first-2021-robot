

#include "frc\Joystick.h"
#include "Robot.h"
#include "Drive.h"
#include "rev/CANSparkMax.h"

using namespace std;

Drive::Drive() : Subsystem("Drive") {
    int leftdriveID = 2;
    int rightdriveID = 3;

    m_leftdrive = new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    m_rightdrive = new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
}

void Drive::Joystick_Drive(double LeftStick, double RightStick){

        m_leftdrive->Set(LeftStick);
        m_rightdrive->Set(RightStick);
    

    }
