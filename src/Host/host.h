#ifndef HOST_H
#define HOST_H
#include "../Module/module.h"

class Host : public Module{
    char *drawMessage;

public:
    Host( CommonData*);
    //~Host();

    void init( int);
    void doTask( Task*);
    void updateHardware();

private:
    void receive( char*);
    void send( char*);
    bool messageAvailable();
    void parsing( Task*, char*);
    void assembly( char*, Task*);
};

#endif // HOST_H
