#ifndef POT_H
#define POT_H
#include "../Module/commondata.h"

// Pot think what max angle what can reach any motor is 180 degrees

class Pot{
    CommonData* common;
  
    int id;
    int val;
    int minVal;
    int maxVal;
    
    Pins pins;

public:
    Pot() {
        id = -1;
        val = 0;
        minVal = 0;
        maxVal = 0;
    }

    void init( CommonData* common, int id, int minVal, int maxVal, const Pins& pins) {
        this->common = common;
        this->id = id;
        this->minVal = minVal;
        this->maxVal = maxVal;
        this->pins = pins;
    }

    int getID()      { return id; }
    int getAngle()   { return int( FLOAT(val-minVal)*180.0/FLOAT(maxVal-minVal) ); }
    int getLastVal() { return val; }
    int getMinVal()  { return minVal; }
    int getMaxVal()  { return maxVal; }
    
    void update() { val = analogRead( pins.n[0]); }
};

#endif // POT_H
