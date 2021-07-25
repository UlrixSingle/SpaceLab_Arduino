#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <Arduino.h>

#define FLOAT double

#define NONE -1
#define YES   1
#define NO    0

struct Pins {
    // 0 - for all
    // 1 - nema, rgb led
    // 2 - nema, rgb led
    // 3 - only needed on the nema with potentiometer or with encoder
    // 4, 5, 6, 7, 8, 9 - for everything
    static const int size = 10;
    int n[size];
};

struct UnitData {
    long  maxAngularySpeed;
    FLOAT gearRatio;
    bool  haveInverseMove;
    FLOAT minAngle;
    FLOAT maxAngle;
    FLOAT beginAngle;
};

class CommonData {
public:
    // Hardware information
    const long long freq = 115200; // frequency of Serial port

    // Host and others
    const int ns_id_owner = 2;  // first 2 symbols in command - id of module that need to complete task
    const int ns_id_unit = 2;   // next 2 symbols in command  - id of his unit
    const int ns_val = 9;       // next 8 symbols in command  - sign of value and value
    const int ns_command = 2;   // next 9 symbols in command  - extra comment
    const int ns_message = ns_id_owner + ns_id_unit + ns_val + ns_command; // = 15

    // Manipulator
    const int unitsN = 4; // num of manipulator's units
    const int decimalPlaces = 2; // the number of digits preceding the dot in val

    // Units
    const FLOAT precision = 1.0; // precision of angle's changing

    // Lights
    const int ledsN = 1; // num of lights' leds

    UnitData* unitsData;
    Pins* unitsPins;
    Pins* ledsPins;

    CommonData() {
        unitsData = new UnitData[unitsN];
        // maxSpeed, gearRatio, haveInverseMove, minAngle, maxAngle, beginAngle
        unitsData[0] = { 720*6, 46.0,  YES,    0, 7200, 3600};
        unitsData[1] = { 120*6,  2.0,  YES,   10,   90,   85};
        unitsData[2] = {   600,  1.0,  YES,   60,  180,   60};
        unitsData[3] = {   600,  1.0,  YES,   10,  170,   90};

        unitsPins = new Pins[unitsN];
        // for Nema -     dir, step,   en, sensor( potentiometer or encoder)
        unitsPins[0] = {   34,   36,   30, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
        unitsPins[1] = {   28,   26,   24,    0,    0,  800, NONE, NONE, NONE, NONE};
        // for Servo -    pin... It's all..
        unitsPins[2] = {   11, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
        unitsPins[3] = {    6, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

        /*
        ledsPins = new Pins[ledsN];
        ledsPins[0] =  {    4,    5,    6, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
        */
    }

    ~CommonData() {
        delete [] unitsData;
        delete [] unitsPins;
        //delete [] ledsPins;
    }

    long valtol( char* val) {
        long sign, res;
        if( val[0] == '-') sign = -1;
        else sign = 1;

        res = 0;
        for( int i = 1; i < ns_val-decimalPlaces; i++)
            res = res*10 + int(val[i])-48;
        return sign*res;
    }

    void ltoval( long l, char* val) {
        if( l < 0) { 
            val[0] = '-';
            l *= -1;
        } else val[0] = '+';

        for( int i = ns_val-1 - decimalPlaces; i >= 1; i--) {
            val[i] = l%10 + 48;
            l /= 10;
        }

        for( int i = 1; i <= decimalPlaces; i++)
            val[ns_val-i] = '0';
    }

    FLOAT valtof( char* val) {
        long sign, res;
        if( val[0] == '-') sign = -1;
        else sign = 1;

        res = 0;
        for( int i = 1; i < ns_val; i++)
            res = res*10 + int(val[i])-48;
        //cout << res << "\n";
        for( int i = 0; i < decimalPlaces; i++) res /= 10.0;
        return FLOAT(sign)*FLOAT(res);
    }

    void ftoval( FLOAT f, char* val) {
        if( f < 0.0) val[0] = '-';
        else val[0] = '+';
        for( int i = 0; i < decimalPlaces; i++) f *= 10.0;
        unsigned long tmp = f;

        for( int i = ns_val-1; i >= 1; i--) {
            val[i] = tmp%10 + 48;
            tmp /= 10;
        }
    }

    void chararrcopy( char* s1, int n1, const char* s2, int n2, int x) {
        if( n1 != n2) return;
        if( x > n1 || x > n2) return;

        for( int i = 0; i < x; i++)
            s1[i] = s2[i];
    }

    bool equals( char* s1, int n1, const char* s2, int n2, int x) {
        if( n1 != n2) return false;
        if( x > n1 || x > n2) return false;

        for( int i = 0; i < x; i++)
            if( s1[i] != s2[i])
                return false;
        return true;
    }

    FLOAT ABS( FLOAT val) { if( val < 0.0) return -val; return val; }
    
    FLOAT FMOD( FLOAT val, FLOAT mod) {
        if( mod < 0) return -1.0;
        return val-mod*FLOAT(int(val/mod));
    }
};

class Task {
    CommonData *common;

public:
    int  id_owner;  // module that must execute this command
    int  id_unit;   // unit of the receiver
    char *val;      // ! need end symb
    char *command;  // ! need end symb

    int  id_sender; // module that added this command to the buffer
    bool complete;  // flag about completing the comand

    void init( CommonData *common, int id_owner = 0, int id_unit = 0, int id_sender = 0) {
        this->common = common;

        this->id_owner = id_owner;
        this->id_unit = id_unit;

        this->val = new char [common->ns_val+1];
        this->val[common->ns_val] = '\0';

        this->command = new char [common->ns_command+1];
        this->command[common->ns_command] = '\0';

        this->id_sender = id_sender;
        this->complete = false;
    }

    ~Task() {
        if( val != nullptr) delete [] val;
        if( command != nullptr) delete [] command;
    }

    Task& operator= ( const Task& another) {
        id_owner = another.id_owner;
        id_unit = another.id_unit;

        for( int i = 0; i < common->ns_val+1; i++)
            val[i] = another.val[i];

        for( int i = 0; i < common->ns_command+1; i++)
            command[i] = another.command[i];

        id_sender = another.id_sender;
        complete = another.complete;

        return *this;
    }
};

#endif // COMMONDATA_H
