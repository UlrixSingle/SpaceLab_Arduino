#include "host.h"

Host::Host( CommonData* common) {
    this->common = common;
    id = -1;
    isAllFine = true;
}

void Host::init( int id) {
    this->id = id;
    taskToOther.init( common, this->id);
    taskToOther.complete = true;
    Err.init( common, this->id);

    Serial.begin( common->freq);
    Serial.println( "Host init complete");
}

void Host::doTask( Task* task) {
    // everything that get Host it will be sent
    // but not that he already sent
    drawMessage = new char [common->ns_message+1];
    
    assembly( drawMessage, task);
    send( drawMessage);
    task->complete = true;
    
    delete [] drawMessage;
}

void Host::updateHardware() {
    if( messageAvailable()) {
        drawMessage = new char [common->ns_message+1];
        receive( drawMessage);
        parsing( &taskToOther, drawMessage);
        delete [] drawMessage;
    }
}

void Host::receive( char* message) {
    Serial.readBytes( message, common->ns_message);
    while( Serial.available()) { Serial.read(); }
    message[common->ns_message] = '\0';
}

void Host::send( char* message) {
    Serial.availableForWrite();
    Serial.write( message, common->ns_message+1);
    Serial.write( byte('\n'));
}

bool Host::messageAvailable() { return Serial.available(); }

void Host::parsing( Task* task, char* message) {
    task->id_owner = 0;
    task->id_unit = 0;
    
    for( int i = 0; i < common->ns_message; i++) {
        if( i < common->ns_id_owner)
            task->id_owner = task->id_owner*10 + (int(message[i])-48);
        
        else if( i < common->ns_id_owner + common->ns_id_unit)
            task->id_unit = task->id_unit*10 + (int(message[i])-48);

        else if( i < common->ns_message - common->ns_command)
            task->val[i - common->ns_id_owner - common->ns_id_unit] = message[i];

        else
            task->command[i + common->ns_command - common->ns_message] = message[i];
    }

    task->id_sender = id;
    task->complete = false;
}

void Host::assembly( char* message, Task* task) {
    message[common->ns_message] = '\0';
    int tmp;

    tmp = task->id_sender;
    for( int i = common->ns_id_owner-1; i >= 0; i--) {
        message[i] = char(tmp%10 + 48);
        tmp /= 10;
    }

    for( int i = common->ns_id_owner; i < common->ns_id_owner + common->ns_id_unit; i++)
        message[i] = '0';

    for( int i = common->ns_id_owner + common->ns_id_unit; i < common->ns_message - common->ns_command; i++)
        message[i] = task->val[i - common->ns_id_owner - common->ns_id_unit];

    for( int i = common->ns_message - common->ns_command; i < common->ns_message; i++)
        message[i] = task->command[i + common->ns_command - common->ns_message];
}
