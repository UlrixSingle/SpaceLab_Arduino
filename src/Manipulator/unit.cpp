#include "unit.h"

Unit::Unit() {
    id = -1;
    data = nullptr;
    angularySpeed = 0;
    angle = 0;
    pins = nullptr;
}

Unit::~Unit() {}

void Unit::init( CommonData* common, int id, UnitData* data, Pins* pins) {
    this->common = common;
    this->id = id;
    this->data = data;
    angularySpeed = data->maxAngularySpeed;
    angle = data->beginAngle;
    this->pins = pins;
    
    initMotor();
}

bool Unit::setAngle( FLOAT ang) {
    if( data == nullptr) return false;
    if( ang < data->minAngle || ang > data->maxAngle)
        return false;
    return setMotorAngle( ang);
}

bool Unit::setSpeed( long v) {
    if( v < 0 || v > data->maxAngularySpeed)
        return false;
    angularySpeed = v;
    return true;
}

int   Unit::getID()               { return id; }
long  Unit::getMaxAngularySpeed() { return data->maxAngularySpeed; }
FLOAT Unit::getGearRatio()        { return data->gearRatio; }
bool  Unit::getHaveInverseMove()  { return data->haveInverseMove; }
FLOAT Unit::getMinAngle()         { return data->minAngle; }
FLOAT Unit::getMaxAngle()         { return data->maxAngle; }
FLOAT Unit::getBeginAngle()       { return data->beginAngle; }
FLOAT Unit::getAngle()            { return angle; }
long  Unit::getAngularySpeed()    { return angularySpeed; }

void Unit::initMotor() { return; }

bool Unit::setMotorAngle( FLOAT new_ang) { return true; }

FLOAT Unit::getMotorAngle() { return 0; }

void initSensor() { return; }
