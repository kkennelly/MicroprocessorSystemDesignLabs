#ifndef MBED_ENCODER_H
#define MBED_ENCODER_H
 
#include "mbed.h"
 
class Encoder {
public:

    // our previous initialize function
    Encoder(PinName pinNameA, PinName pinNameB);
    
    // will handle the interrupt and change the count if necessary
    void interrupt();
    
    int getCounter();
  
private:
    int counter;
    unsigned int currentState;
    unsigned int previousState;
    
    InterruptIn pinA;
    InterruptIn pinB;
    
};
 
#endif