
#include "frc\Joystick.h"
#include "rev/CANSparkMax.h"
#include "frc/VictorSP.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Encoder.h"
#include "Robot.h"
#include "Paths.h"
#include <frc/ADXRS450_Gyro.h>

 

using namespace std;



Paths::Paths() : Subsystem("Paths") {}






double Paths::ReturnTableVal(int count, int select, int brian){
    // Table Definitions

    // path 1

    // picking data from multiple paths 

    auto mode = frc::SmartDashboard::GetString("Autonomous","0");
    auto a_left = 0;//path_1_left;
    auto a_right = 0;//path_1_right;
    auto a_length = 0;//path_1_length;
    
    /*if (mode=="0"){
        a_left = path_1_left;
        a_right = path_1_right;
        a_length = path_1_length;
    }
    else if (mode=="1"){
        a_left = Barrel_left;
        a_right = Barrel_right;
        a_length = path_2_length;

    
    }
    else if (mode=="2"){
        if (brian==1){
            a_left = path_b_left;
            a_right = path_b_right;
            a_length = path_3_length;
        }else{
            a_left = path_a_left;
            a_right = path_a_right;
            a_length = path_a_length;
        }
        

    }
    else if (mode=="3"){
        if (brian==1){
            a_left = push2_left;
            a_right = push2_right;
            a_length = push2_length;
        }
        else if (brian==2){
            a_left = push3_left;
            a_right = push3_right;
            a_length = push3_length;
        }

        else if (brian==3){
            a_left = push4_left;
            a_right = push4_right;
            a_length = push4_length;
        }
        else{
            a_left = push1_left;
            a_right = push1_right;
            a_length = push1_length;
        }
    }
    else if (mode=="5"){
        a_left = path_1_left;
        a_right = path_1_right;
        a_length = path_1_length;
    }*/
    

    double dist_conv = 1; //ticks to feet
    double speed_conv = 1; //feet/s

    double output;

    // picking table entries to send back 

    /*if (select == 0){
        output = (a_left [count] [1]) * dist_conv; 
    }
    if (select == 1){
        output = (a_left [count] [2]) * speed_conv;
    }
    if (select == 2){
        output = (a_right [count] [1]) * dist_conv;
    }
    if (select == 3){
        output = (a_right [count] [2]) * speed_conv;  
    }
    if (select == 4){
        output = a_left [count] [3];
    }

    if (select==5){
        output = a_length;
    }*/


    return output;

}





