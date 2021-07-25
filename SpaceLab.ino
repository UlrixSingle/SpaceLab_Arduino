#include "spacelab_lib.h"


CommonData global;
LoopBuffer buffer( &global);
Host host( &global);


// ++ Default
void setup() {
    host.init(1);
}

void loop() {
    if( host.taskAvailable( buffer.end()) )
        host.doTask( buffer.end());
    
    host.update( &buffer);
}
// -- Default


// ++ Lights
/*
Lights light( &global);

void setup() {
    host.init(1);
    light.init(2);
}

void loop() {
    if( host.taskAvailable( buffer.end()) )
        host.doTask( buffer.end());
    else if( light.taskAvailable( buffer.end()) )
        light.doTask( buffer.end());
    
    host.update( &buffer);
    light.update( &buffer);
}
*/
// -- Lights


// ++ Manipulator
/*
Manipulator rudolf( &global);

void setup() {
    host.init(1);
    rudolf.init(3);
    Serial.println( "Init complete");
}

void loop() {
    if( host.taskAvailable( buffer.end()) )
        host.doTask( buffer.end());
    else if( rudolf.taskAvailable( buffer.end()) )
        rudolf.doTask( buffer.end());
    
    host.update( &buffer);
    rudolf.update( &buffer);
}
*/
// -- Manipulator
