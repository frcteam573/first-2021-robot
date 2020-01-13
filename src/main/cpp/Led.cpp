

#include "frc\Joystick.h"
#include "frc/Spark.h"
#include "Robot.h"
#include "Led.h"


using namespace std;

Led::Led() : Subsystem("Led") {
    // Define CAN and PWM Ids used in Led here
    int LedID = 1;

    // Define motors, sensors, and pneumatics here
    m_leds = new frc::Spark(LedID);
}

void Led::led_control(std::string input){
    // LED control through Blinkin need to add to if else tree if adding any new patterens or colors
    // Pattern list http://www.revrobotics.com/content/docs/REV-11-1105-UM.pdf
    if(input == "Orange"){
        m_leds->Set(0.65);
    }
    else if (input == "Blue"){
        m_leds->Set(0.87);
    }
    else{
        m_leds->Set(0.99);
    }
    
}
