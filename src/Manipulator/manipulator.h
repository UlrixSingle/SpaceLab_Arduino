#ifndef MANIPULATOR_H
#define MANIPULATOR_H
#include "../Module/module.h"
#include "unit.h"
#include "unitnema.h"
#include "unitnemapot.h"
#include "unitservo.h"

class Manipulator : public Module {
    Unit** units; // array of manipulator's units

public:
    Manipulator( CommonData*);
    virtual ~Manipulator();

    void init( int id);
    void doTask( Task*);

private:
    bool setBeginPos();
    bool setUnitAngle( int, FLOAT);
};

#endif // MANIPULATOR_H
