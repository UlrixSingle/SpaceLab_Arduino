#ifndef BUFFER_H
#define BUFFER_H
#include "commondata.h"

class LoopBuffer{
    Task Err;

    const int n = 11;
    Task *arr;
    int endPos;

public:
    LoopBuffer( CommonData* common) {
        Err.init( common);

        arr = new Task[n];
        for( int i = 0; i < n; i++)
            arr[i].init( common);

        endPos = 0;
    }

    ~LoopBuffer() { delete [] arr; }

    void add( const Task& task) {
        arr[endPos] = task;
        endPos = (endPos+1)%n;

        /*
        Serial.println( "id_owner  id_unit  val");
        for( int i = 0; i < n; i++) {
            Serial.print( arr[i].id_owner);
            Serial.print( "        ");
            Serial.print( arr[i].id_unit);
            Serial.print( "       ");
            Serial.print( arr[i].val);
            //Serial.print( " ");
            //Serial.print( arr[i].command);
            if( i == endPos) Serial.print( " <-");
            Serial.println();
        }   Serial.println(); */
    }

    Task* end() { return &(arr[endPos-1]); }

    Task* get( int ind) {
        if( ind < 0 || ind >= n) return &Err;
        return &( arr[((endPos-ind)%n+n)%n] );
    }
};

#endif // BUFFER_H
