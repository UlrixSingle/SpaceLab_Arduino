#include "unitservo.h"

UnitServo::~UnitServo() { delete motor; }

void UnitServo::initMotor() {
    motor = new Servo;
    motor->attach( pins->n[0]);
    motor->write(data->beginAngle);
    angle = data->beginAngle;
}

bool UnitServo::setMotorAngle( FLOAT new_ang) {
    //Serial.print( angle);
    //Serial.print( " ");
    //Serial.println( new_ang);
    int dirStep = 1 - int(angle > new_ang)*2;
    
    if( data->maxAngularySpeed - angularySpeed < 10)
        motor->write( new_ang*data->gearRatio);
    while( abs(angle-new_ang) > common->precision) {
        motor->write( angle*data->gearRatio);
        angle += dirStep;
        delay( 1000/angularySpeed);
    }
    
    return true;
}

FLOAT UnitServo::getMotorAngle() { return angle; }
