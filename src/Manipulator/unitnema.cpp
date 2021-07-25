#include "unitnema.h"

UnitNema::~UnitNema() { delete motor; }

void UnitNema::initMotor() {
    initSensor();
    
    // for nema pin n0 is dir
    // for nema pin n1 is step
    // for nema pin n2 is en
    motor = new Stepper( StepsPerRevolution, pins->n[0], pins->n[1]);
    pinMode( pins->n[2], OUTPUT);
    digitalWrite( pins->n[2], LOW);
    motor->setSpeed( data->maxAngularySpeed/360*60);

    this->angle = data->beginAngle;
    this->angle = getMotorAngle();
    setAngle( data->beginAngle);
}

bool UnitNema::setMotorAngle( FLOAT new_ang) {
    // converting speed from (degree per second) into (step per minute) and (angle) into (num of steps)
    long steps = long( (new_ang-angle) * data->gearRatio / 360.0 * StepsPerRevolution );
    motor->step( steps);

    angle = new_ang;
    return true;
}

FLOAT UnitNema::getMotorAngle() {
    // if( pins->n2 != NONE) return angle;
    // return FLOAT( analogRead( pins->n2), common->min_pot, common->max_pot, data.minAngle, data.maxAngle) );
    return angle;
}

void UnitNema::initSensor() { return; }
