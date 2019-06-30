import io
import time
import picamera
from PIL import Image
import pyzbar.pyzbar as pyzbar
import requests
#import lcddriver
import time
import serial

#lcd = lcddriver.lcd()
#lcd.lcd_display_string("Welcome!", 1)
#lcd.lcd_display_string("Please show your QR code", 2)
port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=0.5)

while(True):
    ## take a photo and decode
    stream = io.BytesIO()
    with picamera.PiCamera() as camera:
        camera.start_preview()
        time.sleep(2)
        camera.capture(stream, format='jpeg')
        camera.close()
        del(camera)
    stream.seek(0)
    pil = Image.open(stream)
    texts = pyzbar.decode(pil)

    ## determine authority
    if len(texts) == 0: ## NO QR CODE
        print('NO QRcode!')
    elif len(texts) == 1: ## ONE QR CODE
        tt = texts[0].data.decode("utf-8")
        print(tt)
        r = requests.get('http://' + tt)
        print('status = ', r.status_code)
        #lcd.lcd_display_string("QRcode recognized!", 3)
        if r.status_code == requests.codes.ok:
            print("connect OK!")
        else:
            print('failed to send request!')
        print(r.text)
        port.write('r')
        print('send char to arduino')
        #lcd.lcd_display_string("Hello" + r.texts[0], 4)
    else: ## MORE THAN ONE QR CODE
        print('more than one QR code!')
        #lcd.lcd_display_string("One person at a time", 4)

    # clean up
    del(pil)


