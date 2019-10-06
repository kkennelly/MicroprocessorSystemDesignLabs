#include "mbed.h"

Serial pc(USBTX, USBRX);
Timer rolling;

int main() {
    int i = 0;
    rolling.start();
    while(1) {
        pc.printf("%d\r\n", i++);
        while (rolling.read_us() < 10000){
            ;
        }
        rolling.reset();
    }
    return 0;
}
