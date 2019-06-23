import io
import time
import picamera
from PIL import Image
import pyzbar.pyzbar as pyzbar
import requests
import lcddriver
from time import *

lcd = lcddriver.lcd()

lcd.lcd_display_string("antisteo on YT", 1)
lcd.lcd_display_string("LCD runtime is", 2)
lcd.lcd_display_string("picorder", 3)
lcd.lcd_display_string("connect me via I2C", 4)

while(True):
    stream = io.BytesIO()
    lcd.lcd_display_string("Welcome!", 1)
    lcd.lcd_display_string("Please show your QR code", 2)
    with picamera.PiCamera() as camera:
        camera.start_preview()
        time.sleep(2)
        camera.capture(stream, format='jpeg')
    # "Rewind" the stream to the beginning so we can read its content
    stream.seek(0)
    pil = Image.open(stream)
    #
    #########################################
    #
    # create a reader
    texts = pyzbar.decode(pil)
    if len(texts) == 0:
        print('NO QRcode!')
    else:
        for text in texts:
            tt = text.data.decode("utf-8")
            print(tt)
            r = requests.get('http://' + tt)
            print('status = ', r.status_code)
            lcd.lcd_display_string("QRcode recognized!", 3)
            if r.status_code == requests.codes.ok:
                print("connect OK!")
            else:
                print('failed to send request!')
            print('text = ', r.text)
            lcd.lcd_display_string("Hello" + r.text, 4)

    # clean up
    del(pil)
    camera.close()
    del(camera)

