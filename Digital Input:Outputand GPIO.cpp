#include "mbed.h"

DigitalIn  mypin(USER_BUTTON); //set button pin name and mode
DigitalOut myled(LED1); //set LED pin name and mode

int main()
{
    // check mypin object is initialized and connected to a pin
    if(mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }

    mypin.mode(PullUp); //set button mode

    // press the button and see the console / led change
    while(1) {
myled = !mypin; // toggle led based on value of button
      wait(0.01);
    }
}