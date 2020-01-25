#include "frc\Joystick.h"
#include "frc/Spark.h"
#include "Robot.h"
#include "Log.h"
#include "frc/PowerDistributionPanel.h"

using namespace std;

frc::PowerDistributionPanel Board;

Log::Log() : Subsystem("Led") {
    // Define CAN and PWM Ids used in Led here


    // Define motors, sensors, and pneumatics here

}

void Log::Dashboard (){

    double val;
    val=Board.GetCurrent(0);
    frc::SmartDashboard::PutString("Right Drive Motor 1",to_string(val));

    val=Board.GetCurrent(1);
    frc::SmartDashboard::PutString("Right Drive Motor 2",to_string(val));

    val=Board.GetCurrent(14);
    frc::SmartDashboard::PutString("Left Drive Motor 1",to_string(val));

    val=Board.GetCurrent(15);
    frc::SmartDashboard::PutString("Left Drive Motor 2",to_string(val));

    val=Board.GetCurrent(10);
    frc::SmartDashboard::PutString("Shooter Motor 1",to_string(val));

    val=Board.GetCurrent(11);
    frc::SmartDashboard::PutString("Shooter Motor 1",to_string(val));

    val=Board.GetCurrent(4);
    frc::SmartDashboard::PutString("Control Panel",to_string(val));

    val=Board.GetCurrent(5);
    frc::SmartDashboard::PutString("Intake Motor",to_string(val));

    val=Board.GetCurrent(9);
    frc::SmartDashboard::PutString("Buddy Climb Motor",to_string(val));

    val=Board.GetCurrent(3);
    frc::SmartDashboard::PutString("Right Climber",to_string(val));

    val=Board.GetCurrent(2);
    frc::SmartDashboard::PutString("Left Climber",to_string(val));

    val=Board.GetCurrent(6);
    frc::SmartDashboard::PutString("Conveyor Motor",to_string(val));

}