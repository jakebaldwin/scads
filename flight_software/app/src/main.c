#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void delay(uint32_t iterations) {
    // sleep for seconds seconds. This needs to be volatile or the optimizer
    // would ignore this loop entirely
    for (volatile uint32_t i = 0; i < iterations; ++i) { /* do nothing */ }
}

int main() {

    // enable port F run mode clock gating control by enabling bit 5 on
    // system control registers
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

    // perform delay read to let clock stabilize
    volatile uint32_t delay_read = SYSCTL_RCGCGPIO_R;
    (void)delay_read;

    // set PF1 as output register via GPIODIR direction bit
    GPIO_PORTF_DIR_R |= 0x02;

    // Enable PF1 as digital I/0 enabled via GPIODEN digital enable bit
    GPIO_PORTF_DEN_R |= 0x02;

    while(1) {
        // set PF1 light on
        GPIO_PORTF_DATA_R |= 0x02;
        delay(500000);
        // set PF1 light off
        GPIO_PORTF_DATA_R &= ~(0x02);
        delay(1000000);
    }

    return 0;
}
