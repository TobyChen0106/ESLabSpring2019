# 107-2 嵌入式實驗 LAB 2
- 組名：請問柏志要喝奶茶還是按摩呢？
- 組員：B06901004劉穎立、B05901170陳柏志、B05901179詹欣玥

## 11.1 Sensor Shields
- X-NUCLEO-IKS01A1 expansion board
    - three-axis accelerometer (ST LSM6Ds0)
    - three-axis gyroscope sensor, three-axis magnetometer (LIS3MDL)
    - humidity sensor (HTS221)
    - temperature sensor, and pressure sensor (LPS25H).
    ![](https://i.imgur.com/kv1pqYt.jpg)
    - All sensors can be accessed from the MCU using I2C serial communication.
- code:
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
- <b>RESULT</b>
    - We tried to print it in a clear and readable way on the terminal.
    ![](https://imgur.com/P2eFqps.jpg)
    ![](https://imgur.com/X4cJzx9.jpg)
    ![](https://imgur.com/X43o840.jpg)
    - We shaked or spinned the sensor to assure it works properly 👍
## 11.2 First BLE Program
- Bluetooth low energy expansion board (X-NUCLEO-IDB04A1)
- 
## 12 Weather Station