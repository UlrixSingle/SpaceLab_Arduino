#include "manipulator.h"

Manipulator::Manipulator( CommonData* common) {
    this->common = common;
    id = -1;
    isAllFine = true;

    units = new Unit* [this->common->unitsN];
    units[0] = new UnitNema;
    units[1] = new UnitNemaPot;
    units[2] = new UnitServo;
    units[3] = new UnitServo;
    (*units[0]) = UnitNema();
    (*units[1]) = UnitNemaPot();
    (*units[2]) = UnitServo();
    (*units[3]) = UnitServo();
}

Manipulator::~Manipulator() {
    for( int i = 0; i < common->unitsN; i++)
        delete units[i];
    delete [] units;
}

void Manipulator::init( int id) {
    this->id = id;
    taskToOther.init(common, this->id);
    taskToOther.complete = true;
    Err.init(common, this->id);

    // int, const UnitData& {0,0,0,0,0,0}, Pins {0,0,0}
    (*units[0]).init( common, 1, &common->unitsData[0], &common->unitsPins[0]);
    (*units[1]).init( common, 2, &common->unitsData[1], &common->unitsPins[1]);
    
    for( int i = 2; i < 4; i++)
        (*units[i]).init( common, i +1, &common->unitsData[i], &common->unitsPins[i]);
}

void Manipulator::doTask( Task* task) {
    // "01" - move a unit on angle that equals 'val'
    // "02" - get current angle of unit
    // "03" - estabilish unit in begin position
    
    if( task->command[0] == '0' && task->command[1] == '1') {
        long value = common->valtol( task->val);
        if(  (*units[ task->id_unit-1 ]).getHaveInverseMove() ) value *= -1; 
        isAllFine = setUnitAngle( task->id_unit -1, units[task->id_unit -1]->getAngle()+value);
    } else if( task->command[0] == '0' && task->command[1] == '2') {
        taskToOther = Err;
        taskToOther.id_owner = task->id_sender;
        taskToOther.id_sender = id;
        common->ltoval( units[task->id_unit -1]->getAngle(), taskToOther.val);
        taskToOther.command[0] = '0';
        taskToOther.command[1] = '0';
    } else if( task->command[0] == '0' && task->command[1] == '3') { 
        isAllFine = setBeginPos(); 
    } 

    isAllFine = true;
    task->complete = true;
}

bool Manipulator::setBeginPos() {
    bool mode = true;

    for( int i = 0; i < common->unitsN && mode; i++) {
        mode &= (*units[i]).setAngle( (*units[i]).getBeginAngle());
        delay( 1000);
    }
    return mode;
}

bool Manipulator::setUnitAngle( int unit_id, FLOAT new_ang) {
    if( unit_id < 0 || unit_id >= common->unitsN)
        return false;
    return (*units[unit_id]).setAngle( new_ang);
}
