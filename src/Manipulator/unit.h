#ifndef UNIT_H
#define UNIT_H
#include "../Module/commondata.h"

class Unit {
public:
    CommonData* common;

    int id;
    UnitData* data;
    long angularySpeed;
    FLOAT angle;

    Pins* pins;
    // State* state - probably can exist
    // pointer on commands' buffer


    Unit();
    virtual ~Unit();

    void init( CommonData*, int, UnitData*, Pins*);
    bool setAngle( FLOAT);
    bool setSpeed( long);
    // void update();

    int   getID();
    long  getMaxAngularySpeed();
    FLOAT getGearRatio();
    bool  getHaveInverseMove();
    FLOAT getMinAngle();
    FLOAT getMaxAngle();
    FLOAT getBeginAngle();
    FLOAT getAngle();
    long  getAngularySpeed();

    virtual void  initMotor();
    virtual bool  setMotorAngle( FLOAT);
    virtual FLOAT  getMotorAngle();
};

#endif // UNIT_H
