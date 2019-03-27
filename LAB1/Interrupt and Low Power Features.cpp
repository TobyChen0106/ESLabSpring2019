#include "mbed.h"

InterruptIn button(USER_BUTTON); //set button pin name and mode
DigitalOut led(LED1);//set LED pin name and mode

void light() { //if detect falling edge, turn on LED
    led = 1;
}
void off(){ //if detect rising edge, turn off LED
    led = 0;
}

int main() {
    // attach the address of the flip function to the falling edge
    button.fall(&light);
    // attach the address of the flip function to the rising edge
    button.rise(&off);
    while(1) {           
    // wait around, interrupts will interrupt this!
        wait(0.05);
    }
}