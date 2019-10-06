#include "mbed.h"

Serial pc(USBTX, USBRX);
Ticker tock;
int i = 0;

void printnow() {
    pc.printf("%d\r\n", i++);
}

int main() {
    tock.attach_us(&printnow, 10000);
    while (1) {
        ;
    }
    return 0;
}
