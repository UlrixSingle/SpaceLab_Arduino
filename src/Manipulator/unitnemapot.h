#ifndef UNITNEMAPOT_H
#define UNITNEMAPOT_H
#include "unitnema.h"
#include "pot.h"

class UnitNemaPot : public UnitNema {
    Pot pot;

public:
    bool setMotorAngle( FLOAT);
    FLOAT getMotorAngle();

    void initSensor();
};

#endif // UNITNEMAPOT_H
