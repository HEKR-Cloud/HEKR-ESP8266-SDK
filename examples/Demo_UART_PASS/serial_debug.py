#!/usr/bin/env python
# coding=utf-8

import sys
import serial
import readline
import time
import thread


def SerialRead():
    while 1:
        reply = ser1.read()
        print "\b%s" % reply,


if __name__ == '__main__':
    baud = 9600
if len(sys.argv) == 2:
    baud = sys.argv[1]
print baud
ser1 = serial.Serial("/dev/ttyUSB0", baud, timeout=5)
ser1.setDTR(False)
ser1.setRTS(False)
thread.start_new_thread(SerialRead, ())
while 1:
    message = raw_input()
    # hex=int(raw_input(),16)
    # print hex
    ser1.write(message)
    time.sleep(0.5)
ser1.close()

