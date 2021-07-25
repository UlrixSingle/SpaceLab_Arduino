#ifndef UNITNEMA_H
#define UNITNEMA_H
#include "unit.h"
#include <Stepper.h>

class UnitNema : public Unit {
public:
    const long StepsPerRevolution = 200;
    Stepper* motor;


    ~UnitNema();

    virtual void initMotor();
    virtual bool setMotorAngle( FLOAT);
    virtual FLOAT getMotorAngle();

    virtual void initSensor();
};

#endif // UNITNEMA_H
