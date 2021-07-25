#ifndef LED_H
#define LED_H
#include "../Module/commondata.h"

class Led{
    CommonData* common;

    int id;
    int r;
    int g;
    int b;

    Pins pins;

public:
    void init( CommonData*, int, const Pins&);
    void setColour( int, int, int);

    int getID();
    int getR();
    int getG();
    int getB();
};

#endif // LED_H
