/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Encoder.h"
Serial pc(USBTX, USBRX);

/*InterruptIn pin7(p7);
InterruptIn pin8(p8);
*/
Encoder encoder(p7, p8);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

int counter = 0;

int main()
{
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    
    while (1) {
        
        counter = encoder.getCounter();
        
        // set the led values
        led1 = counter & 0x8;
        led2 = counter & 0x4;
        led3 = counter & 0x2;
        led4 = counter & 0x1;
        
        pc.printf("Counter: %i\r\n", counter);
        wait(0.1);
    }
}