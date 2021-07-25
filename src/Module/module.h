#ifndef MODULE_H
#define MODULE_H
#include "../Module/commondata.h"
#include "buffer.h"

class Module {
public:
    CommonData* common;
    Task taskToOther;
    Task Err;

    int id;
    bool isAllFine;

    /*
    Module( CommonData* common) {
        this->common = common;
        id = -1;
        isAllFine = true;
    }
    */

    virtual void init( int id) {
        this->id = id;
        taskToOther.init(common, this->id);
        taskToOther.complete = true;
        Err.init(common, this->id);
    }

    bool taskAvailable( Task* task) {
        if( task->id_owner == id) {
            return !(task->complete);
        }   return false;
    }

    virtual void doTask( Task* task) { return; }

    void update( LoopBuffer* buffer) {
        updateHardware();
        
        if( !isAllFine) taskToOther = Err;
        if( !taskToOther.complete) {
            buffer->add( taskToOther);
            taskToOther.complete = true;
        }   isAllFine = true;
    }

    int getID() { return id; }

    virtual void updateHardware() { return; }
};

#endif // MODULE_H
