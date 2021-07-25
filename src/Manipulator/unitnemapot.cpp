#include "unitnemapot.h"

void UnitNemaPot::initSensor() {
    pot.init( common, 1, pins->n[4], pins->n[5], {pins->n[3]});
}

FLOAT UnitNemaPot::getMotorAngle() {
    pot.update();
    return pot.getAngle();
}

bool UnitNemaPot::setMotorAngle( FLOAT new_ang) {
    // converting speed from (degree per second) into (step per minute) and (angle) into (num of steps)
    angle = getMotorAngle();
    
    if( pins->n[3] != NONE) {
        if( new_ang < angle) {
            while( new_ang < angle) {
                // Serial.println( angle);
                motor->step( 1);
                angle = getMotorAngle();
            }
        }
        
        else if( new_ang > angle) {
            while( new_ang > angle) {
                // Serial.println( angle);
                motor->step( -1);
                angle = getMotorAngle();
            }
        }
    }

    angle = getMotorAngle();
    // return (common->ABS(angle-new_ang) < common->precision);
    return true;
}
