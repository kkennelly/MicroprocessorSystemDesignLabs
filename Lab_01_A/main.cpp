#include "mbed.h"

Serial pc(USBTX, USBRX);

int main() {
    int i = 0;
    while(1) {
        pc.printf("%d\r\n",i++);
        wait(0.01);
    }
    return 0;
}
