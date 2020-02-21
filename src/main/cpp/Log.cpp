#include "frc\Joystick.h"
#include "frc/Spark.h"
#include "Robot.h"
#include "Log.h"
#include "frc/PowerDistributionPanel.h"

using namespace std;

int counter;

frc::PowerDistributionPanel Board;

Log::Log() : Subsystem("Led") {
    // Define CAN and PWM Ids used in Led here


    // Define motors, sensors, and pneumatics here

}

void Log::Dashboard (){

    double val;
    val=Board.GetCurrent(0);
    frc::SmartDashboard::PutString("Right Drive Motor 1",to_string(val));

    val=Board.GetCurrent(14);
    frc::SmartDashboard::PutString("Right Drive Motor 2",to_string(val));

    val=Board.GetCurrent(1);
    frc::SmartDashboard::PutString("Left Drive Motor 1",to_string(val));

    val=Board.GetCurrent(13);
    frc::SmartDashboard::PutString("Left Drive Motor 2",to_string(val));

    val=Board.GetCurrent(10);
    frc::SmartDashboard::PutString("Shooter Motor 2",to_string(val));

    val=Board.GetCurrent(11);
    frc::SmartDashboard::PutString("Shooter Motor 1",to_string(val));

    val=Board.GetCurrent(4);
    frc::SmartDashboard::PutString("Control Panel",to_string(val));

    val=Board.GetCurrent(12);
    frc::SmartDashboard::PutString("Intake Motor",to_string(val));

    val=Board.GetCurrent(6);
    frc::SmartDashboard::PutString("Buddy Climb Motor",to_string(val));

    val=Board.GetCurrent(3);
    frc::SmartDashboard::PutString("Right Climber",to_string(val));

    val=Board.GetCurrent(2);
    frc::SmartDashboard::PutString("Left Climber",to_string(val));

    val=Board.GetCurrent(9);
    frc::SmartDashboard::PutString("Conveyor Motor",to_string(val));


}

void Log::PDPTotal(){
	double val = Board.GetTotalCurrent();
	bool light;


	if (val > 250){

		counter = counter + 1;
		if (counter > 50){
			light = true;
		}
		else{
			light = false;
		}
	}
	else {
		counter = 0;
		light = false;
	}

	frc::SmartDashboard::PutBoolean("Over 250 Amps", light);
	//auto Gyrooutstr = std::to_string(counter);
	//frc::SmartDashboard::PutString("DB/String 5",Gyrooutstr);
}

void Log::CurrentCompare(int slot,double PWMin){

	double current = Board.GetCurrent(slot);

	if (abs(PWMin) > .2){
		if (abs(current) < 1){
			
			frc::SmartDashboard::PutString("No Current Draw",to_string(slot));
		}
	}
}