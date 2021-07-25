#include "lights.h"

Lights::Lights( CommonData* common) {
    this->common = common;
    id = -1;
    isAllFine = true;
  
    leds = new Led* [common->ledsN];
    for( int i = 0; i < common->ledsN; i++) {
        leds[i] = new Led;
        (*leds[i]) = Led();
    }
}

Lights::~Lights() {
    for( int i = 0; i < common->ledsN; i++)
        delete leds[i];
    delete [] leds;
}

void Lights::init( int id) {
    this->id = id;
    taskToOther.init( common, this->id);
    taskToOther.complete = true;
    Err.init( common, this->id);

    for( int i = 0; i < common->ledsN; i++)
        (*leds[i]).init( common, i, common->ledsPins[i]);
}

void Lights::doTask( Task* task) {
    int r = 0, g = 0, b = 0;
    for( int i = 0; i < 3; i++) {
        r = r*10 + int(task->val[i])-48;
        g = g*10 + int(task->val[3+i])-48;
        b = b*10 + int(task->val[6+i])-48;
    }
    setLedColour( task->id_unit, r, g, b);

    task->complete = true;
}

bool Lights::setLedColour( int id_led, int r, int g, int b) { leds[id_led]->setColour( r, g, b); }
