#include "led.h"

void Led::init( CommonData* common, int id, const Pins& pins) {
    this->common = common;
    this->id = id;
    this->pins = pins;

    r = 0;
    g = 0;
    b = 0;

    for( int i = 0; i < 3; i++) {
        analogWrite( pins.n[i], 255);
        delay( 100);
    }

    for( int i = 0; i < 3; i++) {
        analogWrite( pins.n[i], 0);
        delay( 100);
    }
}

void Led::setColour( int r, int g, int b) {
    if( (0 <= r < 256) && (0 <= g < 256) && (0 <= b < 256) ) {
        this->r = r;
        this->g = g;
        this->b = b; 
    }
    
    analogWrite( pins.n[0], this->r);
    analogWrite( pins.n[1], this->g);
    analogWrite( pins.n[2], this->b);
}

int Led::getID() { return id; }
int Led::getR()  { return r; }
int Led::getG()  { return g; }
int Led::getB()  { return b; }
