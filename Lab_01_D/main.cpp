#include "mbed.h"
#include "ctype.h"

Serial pc(USBTX, USBRX);
void interrupt();
void copy_data();

// the number of bytes to fit in the buffer
const int BUFFER_SIZE = 8;
// the buffer
char buffer[BUFFER_SIZE];
// circular buffer pointers - volatile makes it non-interruptible
volatile int buffer_in = 0;
volatile int buffer_out = 0;


// the buffer that holds info ready for output
char output[BUFFER_SIZE];
// circular buffer pointers - volatile makes it non-interruptible
volatile int output_in = 0;
volatile int output_out = 0;
// indicator bool
// true to indicate the presence of a new packet
bool new_packet = false;
// indicator bool
// true to indicate the output of the packet was successful
bool packet_read = true;


int main() {
    
    // setup serial receive interrupt
    pc.attach(interrupt, Serial::RxIrq);
    
    while (1) {
           
        // if a new packet has to be read
        if (new_packet) {
            
            new_packet = false;
            
            // print the packet
            while (((output_out + 1) % BUFFER_SIZE) != output_in) {
                
                pc.printf("%c", output[output_out]);
                output_out = (output_out + 1) % BUFFER_SIZE;
            }
            
            // print the last character
            // making output_out the same as output_in
            pc.printf("%c", output[output_out]);
            output_out = (output_out + 1) % BUFFER_SIZE;
            
            // new line for ease of read
            //pc.printf("\n");
            
            // re-initialize the output buffer in order to be filled again
            output_in = 0;
            output_out = 0;
            
            // set this variable to notify completion
            packet_read = true;
        }           
    }
}


void interrupt() {
    
    char currentData;

    // while we can read the pc and the buffer isn't full
    while(pc.readable() && ((buffer_in + 1) % BUFFER_SIZE) != buffer_out) {
        currentData = pc.getc();
        
        // if it is the less than character
        if (currentData == '<') {
            buffer_in = 0;
            buffer_out = 0;
        }
        // if the data is valid
        else if ( isalnum(currentData) ) {
            buffer[buffer_in] = currentData;
            buffer_in = (buffer_in + 1) % BUFFER_SIZE;
        }
        // if the data isn't valid, just get the next char
    }   
    
    if (((buffer_in + 1) % BUFFER_SIZE) == buffer_out) {   
        copy_data();
    }
    
    return;
}


void copy_data() {
    
    // while packet_read is false, we cannot proceed
    while (!packet_read) {
        ;   
    }
        
    // while there is data to read and our output buffer isnt full
    while (buffer_out != buffer_in && ((output_in + 1) % BUFFER_SIZE) != output_out) {
        // store the next piece of data into the output buffer
        output[output_in] = buffer[buffer_out];
        
        buffer_out = (buffer_out + 1) % BUFFER_SIZE;
        output_in = (output_in + 1) % BUFFER_SIZE;
    }
    
    // if the output buffer is full, then we can say it is available to read
    if(((output_in +1) % BUFFER_SIZE) == output_out) {
        // re-initialize the buffer in and out
        buffer_in = 0;
        buffer_out = 0;
        
        new_packet = true;
        packet_read = false;
    }
}