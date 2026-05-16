#include <stdint.h>
#include <stddef.h>
#include "fsm_supervisor.h"
extern "C" {
    #include <FreeRTOS.h>
    #include <task.h>
    #include "inc/tm4c123gh6pm.h"
}

#define RED_DELAY_TICKS_ON              1000
#define RED_DELAY_TICKS_OFF             3000
#define GREEN_DELAY_TICKS_ON            1000
#define GREEN_DELAY_TICKS_OFF           3000

// this function sets the hardware up to receive input and expect output on
// the proper GPIO pins to make the LED light flash
void setupGpio() {

    // enable port F run mode clock gating control by enabling bit 5 on
    // system control registers
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

    // perform delay read to let clock stabilize
    volatile uint32_t delay_read = SYSCTL_RCGCGPIO_R;
    (void)delay_read;

    // set PF1 and PF3 as output registers via GPIODIR direction bit
    GPIO_PORTF_DIR_R |= (1 << 1) | (1 << 3);

    // Enable PF1 and PF3 as digital I/0 enabled via GPIODEN digital
    // enable bit
    GPIO_PORTF_DEN_R |= (1 << 1) | (1 << 3);

}

void blinkRedTask( void * pvParameters ) {
    // read input which is pointer to fsm supervisor object
    FsmSupervisor* fsm_supervisor = static_cast<FsmSupervisor*>(pvParameters);

    // use an infinite loop, it is up to the scheduler to stop this task and
    // start another one
    for (;;) {
        // set light to be red by enabling second bit
        GPIO_PORTF_DATA_R |= (1 << 1);
        fsm_supervisor->transition_to_safe();
        vTaskDelay(pdMS_TO_TICKS(RED_DELAY_TICKS_ON));

        // set light to be off by disabling second bit
        GPIO_PORTF_DATA_R &= ~(1 << 1);
        vTaskDelay(pdMS_TO_TICKS(RED_DELAY_TICKS_OFF));
    }
}

void blinkGreenTask( void * pvParameters ) {
    // read input which is pointer to fsm supervisor object
    FsmSupervisor* fsm_supervisor = static_cast<FsmSupervisor*>(pvParameters);


    for (;;) {
        // set light to be red by enabling fourth bit
        GPIO_PORTF_DATA_R |= (1 << 3);
        fsm_supervisor->transition_to_nominal();
        vTaskDelay(pdMS_TO_TICKS(GREEN_DELAY_TICKS_ON));

        // set light to be off by disabling fourth bit
        GPIO_PORTF_DATA_R &= ~(1 << 3);
        vTaskDelay(pdMS_TO_TICKS(GREEN_DELAY_TICKS_OFF));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask,
                                   char *pcTaskName) {
    // we are not using the inputs right now so cast them so the compiler is
    // not angry with us
    (void)pxTask;
    (void)pcTaskName;

    // disable interrupts so if we hit this overflow we will hang out in
    // this function and loop forever so we can get stuck here in the debugger
    taskDISABLE_INTERRUPTS();
    for (;;);
}

int main() {

    setupGpio();

    static FsmSupervisor fsm_supervisor;

    xTaskCreate(blinkGreenTask,     // task name
                "blinkGreenTask",   // text name for the task
                200,                // stack depth in words
                &fsm_supervisor,    // pass fsm_supervisor
                1,                  // task priority of 1
                NULL);              // no task handle

    xTaskCreate(blinkRedTask,       // task name
                "blinkRedTask",     // text name for the task
                200,                // stack depth in words
                &fsm_supervisor,    // pass fsm_supervisor
                1,                  // task priority of 1
                NULL);              // no task handle

    vTaskStartScheduler();

    for (;;);
}
