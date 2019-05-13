# 107-2 嵌入式實驗 LAB 2
- 組名：請問柏志要喝奶茶還是按摩呢？
- 組員：B06901004劉穎立、B05901170陳柏志、B05901179詹欣玥

## 11.1 Sensor Shields
- file `SeneorShield.cpp`
- X-NUCLEO-IKS01A1 expansion board
    - three-axis accelerometer (ST LSM6Ds0)
    - three-axis gyroscope sensor, three-axis magnetometer (LIS3MDL)
    - humidity sensor (HTS221)
    - temperature sensor, and pressure sensor (LPS25H).
    ![](https://i.imgur.com/kv1pqYt.jpg)
    - All sensors can be accessed from the MCU using I2C serial communication.
### code:
- A helper function to print floats and doubles
```C++
static char *print_double(char* str, double v, int decimalDigits=2)
```
- main function
```C++
int main(){
    /* first, enable all sensors */
    while(1){
        /* 
        periodically retrieve data from each sensor 
        use printf to print on terminal 
        */
    }
}
```
### <b>RESULT</b>
- We tried to print it in a clear and readable way on the terminal.
![](https://imgur.com/P2eFqps.jpg)
![](https://imgur.com/X4cJzx9.jpg)
![](https://imgur.com/X43o840.jpg)
- We shaked or spinned the sensor to assure it works properly 👍

## 11.2 First BLE Program
- file `FirstBLEProgram.cpp`
- Bluetooth low energy expansion board (X-NUCLEO-IDB04A1)
### code:
- `int main`
```C++
int main()
{
    // initiate a period callback function that blinks while waiting for BLE events.
    //then initiate BLE in by using
    bleInitComplete()
}
```
- `void bleInitComplete`
```C++
void bleInitComplete (BLE::InitializationCompleteCallbackContext *params){
        // setup BLE
        // enable sensors
        while(1)
        {
            if()
            {
                // triggered in period callback
                // transits hrmCounter as dummy data of heart rate
            }
            else
            {
                // low power
                // waiting for events
            }
        }
```
### <b>RESULT</b>
- Successfully connected! 👍
    ![](https://imgur.com/NvXRoRN.jpg)
    ![](https://imgur.com/hWWklCE.jpg)
    ![](https://imgur.com/QZgemvD.jpg)
## 12 Weather Station
### An attempt with MBED
- file `WeatherStation_1.cpp`
- We first tried to modify the code from 11.2, the Heart rate program, into a weather station program.
- However, <b>it appears that the ST BLE Profiles App keeps on reconizing our program as a `Continuous Glucose Measurement Device` </b>.
![](https://imgur.com/lXZ7AYJ.jpg)
![](https://imgur.com/CDe3SRu.jpg)
    tap into one of those three
![](https://imgur.com/tSESd3i.jpg)
- We already ensured we connected to the right device, and searched for the keyword 
`Continuous Glucose Measurement Device` but couldn't find any.

- So we temporarily gave up on using this library, and turned to HC-05 as our bluetooth device.

### Using HC-05 to implement weather station