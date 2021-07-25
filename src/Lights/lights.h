#ifndef LIGHTS_H
#define LIGHTS_H
#include "../Module/module.h"
#include "led.h"

class Lights : public Module{
    Led** leds; // array of leds

public:
    Lights( CommonData*);
    virtual ~Lights();

    void init( int);
    void doTask( Task*);

private:
    bool setLedColour( int, int, int, int);
};

#endif // LIGHTS_H
