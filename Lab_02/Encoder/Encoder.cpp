#include "Encoder.h"
#include "mbed.h"

Encoder::Encoder(PinName pinNameA, PinName pinNameB) : pinA(pinNameA), pinB(pinNameB) {
    // initialize all values
    
    // set pin modes to pull up
    pinA.mode(PullUp);                  // why couldn't we do pin7 = 1 to default the output to high?
    pinB.mode(PullUp);
    
    // assign interrupt handler for falling edges
    pinA.fall(callback(this, &Encoder::interrupt));
    pinB.fall(callback(this, &Encoder::interrupt));
    
    // assign interrupt handler for rising edges
    pinA.rise(callback(this, &Encoder::interrupt));
    pinB.rise(callback(this, &Encoder::interrupt));
    
    counter = 0;
    currentState = 0b11;
    previousState = 0b11;
}

// pattern for clockwise is:
//        11 01 00 10
// pattern for counter clockwise is:
//        11 10 00 01
 
void Encoder::interrupt() {
    
    // set current state to previous state
    previousState = currentState;
    int pinAread = pinA.read();
    int pinBread = pinB.read();
    
    currentState = (pinAread << 1) | pinBread;
    
    
    // if we xor the previous state last bit with the current state first bit
    if((previousState & 1 ^ (currentState >> 1) & 1) == 0) {
        // the bits are the same so we are going counter clockwise
        counter--;
    }
    else {
        // the bits are chaning so we are going clockwise
        counter++;
    }
    
   /* // if we xor previous state and current state and the answer is 
    // if previous state is 11 and the current state is 01
    if (previousState == 0b11 && currentState == 0b01) {  
        // then clockwise, increment counter
        counter++;
    }
    // else if previous state is 11 and the current state is 10
    else if (previousState == 0b11 && currentState == 0b10) {   
        // then counter clockwise, decrement counter
        counter--;
    }
    // if the state is any different, we dont need to worry about the counter*/
}

int Encoder::getCounter() {
    return counter >> 2;
}