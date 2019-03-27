# 107-2 嵌入式實驗 LAB 1
- 組名：請問柏志要喝奶茶還是按摩呢？
- 組員：B06901004劉穎立、B05901170陳柏志、B05901179詹欣玥
## 0. Develop Environment
- We use MBED as our develop environment.
![](https://i.imgur.com/WcRwGFU.png)

## 1. Digital Input/Outputand GPIO

程式碼：
```cpp
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
```

#### DigitalIn的mode
- PULLDOWN: Input becomes HIGH when pressed down.
- PULLUP: Input becomes LOW when pressed down
- USER_BUTTON will remain as PULLUP no matter what mode you define it as.

## 2. Interrupt and Low Power Features

程式碼：
```cpp
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
```

#### Interrupt
What we know about interrupt:
- Interrupt transfers control to the interrupt service routine generally, through the interrupt vector, which contains the addresses of all the service routines.
- Interrupt architecture must save the address of the interrupted instruction.
- Incoming interrupts are disabled while another interrupt is being processed to prevent a lost interrupt.
- An operating system is interrupt driven.

## 3. DEMO Video
    ![](https://imgur.com/7vTb07L)
## 4. 心得
　　我們遇到的第一個問題是在做Square Root Approximation的時候不知道要怎麼用電腦輸入數字，跟如何接收板子算完的結果再顯示在電腦上，後來安裝了ST Link Driver後就可以用serial的scanf跟printf。
