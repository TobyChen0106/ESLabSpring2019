import serial
import time

ser = serial.Serial('/dev/ttyACM0',9600)

ser.write('r')
while True:
    ser.write('1')
    time.sleep(2)