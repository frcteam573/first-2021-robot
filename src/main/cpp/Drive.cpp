

#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Encoder.h"
#include "Robot.h"
#include "Drive.h"


using namespace std;

Drive::Drive() : Subsystem("Drive") {
    // Define CAN and PWM Ids used in Drive here
    int leftdriveID = 2;
    int leftdriveID2 = 3;
    int rightdriveID = 4;
    int rightdriveID2 = 5;
    int driveshiftIDa = 2;
    int driveshiftIDb = 3;
    int buddyclimbID = 11;
    int buddyclimbpIDa = 6;
    int buddyclimbpIDb = 7;
    int leftclimbID = 6;
    int rightclimbID = 7;
    int leftdriveencID_a = 2;
    int leftdriveencID_b = 3;
    int rightdriveencID_a = 0;
    int rightdriveencID_b = 1;    



    // Define motors, sensors, and pneumatics here
    m_leftdrive = new rev::CANSparkMax{leftdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive2 = new rev::CANSparkMax{leftdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    m_leftdrive->SetInverted(true);
    m_leftdrive2->SetInverted(true);
    m_rightdrive = new rev::CANSparkMax{rightdriveID, rev::CANSparkMax::MotorType::kBrushless};
    m_rightdrive2 = new rev::CANSparkMax{rightdriveID2, rev::CANSparkMax::MotorType::kBrushless};
    s_leftdrive_enc = new frc::Encoder( leftdriveencID_a, leftdriveencID_b, false, frc::Encoder::k4X);
    s_rightdrive_enc = new frc::Encoder( rightdriveencID_a, rightdriveencID_b, false, frc::Encoder::k4X);
    p_driveshift = new frc::DoubleSolenoid(1, driveshiftIDa, driveshiftIDb);
    m_buddyclimb = new rev::CANSparkMax{buddyclimbID, rev::CANSparkMax::MotorType::kBrushless};
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
    m_leftdrive2->Set(LeftStick);
    m_rightdrive->Set(RightStick);
    m_rightdrive2->Set(RightStick);



}

void Drive::buddyclimb_motor(double input){ 
    //Runs buddy climb roller
    m_buddyclimb->Set(input);

}

void Drive::buddyclimb_out(){
    // Deploy buddy climb claw
    p_buddyclimb->Set(frc::DoubleSolenoid::Value::kForward);

}

void Drive::buddyclimb_in(){
    // Retract buddy climb claw
    p_buddyclimb->Set(frc::DoubleSolenoid::Value::kReverse);
    
}

void Drive::climb(double input){
    // Run climber motors
    m_leftclimb->Set(input);
    m_rightclimb->Set(input);

}

void Drive::shift_low(){
    // Set drive transmissions into low gear
    p_driveshift->Set(frc::DoubleSolenoid::Value::kReverse);

}

void Drive::shift_high(){
    // Set drive transmissions into high gear
    p_driveshift->Set(frc::DoubleSolenoid::Value::kForward);

}

void Drive::shift_auto(){
    // Auto shifting logic

    double enc_left_rate = s_leftdrive_enc->GetRate();
    double enc_right_rate = s_rightdrive_enc->GetRate();

    enc_left_rate = enc_left_rate * -1; //Inverting left drive rate
    double enc_avg_rate = (enc_left_rate + enc_right_rate)/2; // Avg rate
    enc_avg_rate = abs(enc_avg_rate); // Absolute value in encoder rate

    if (enc_left_rate * enc_right_rate > 0){ // Checking if left and right side are going the same direction

        if (enc_avg_rate > 5000){ // 5000 is a fake number 
            // If wheel speed is high enough shift into high gear
            shift_high();
        }
        
    }
    else {
        // Default is low gear
        shift_low();
    }

    

}