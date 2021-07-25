#ifndef UNITSERVO_H
#define UNITSERVO_H
#include "unit.h"
#include <Servo.h>

class UnitServo : public Unit {
    Servo* motor;

public:
    ~UnitServo();

    void  initMotor();
    bool  setMotorAngle( FLOAT);
    FLOAT getMotorAngle();
};

#endif // UNITSERVO_H
