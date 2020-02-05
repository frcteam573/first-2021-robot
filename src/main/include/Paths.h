#ifndef Paths_H
#define Paths_H

#pragma once

#include <frc/commands/Subsystem.h>


using namespace std;

class Paths : public frc::Subsystem {

 private:


 public:
  Auto();
  double ReturnTableVal(int count, int select);
 

};
#endif 