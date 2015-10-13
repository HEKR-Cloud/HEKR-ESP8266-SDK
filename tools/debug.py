#!/usr/bin/env python
import os
import sys
import time
import thread

cleanoldbin = 'rm -rf ../bin/upgrade/*.bin'

downloadbin = '../tools/flashtool.py --port /dev/ttyUSB0 -b 921600  write_flash --flash_size 16m  0x01000 ../bin/upgrade/user1.bin'

downloadbin_all = '../tools/flashtool.py --port /dev/ttyUSB0 --baud 921600  write_flash --flash_size 16m 0x00000 ../bin/boot_v1.2.bin 0x01000 ../bin/upgrade/user1.bin 0x100000 ../bin/SfsPart.bin 0x1FE000 ../bin/blank.bin 0x1FC000 ../bin/esp_init_data_default.bin'

OpenUartDebug = "../tools/serial_debug.py 9600"

make_one_bin = 'make APP=1'

make_two_bin = 'make clean&&make APP=1&&make clean&&make APP=2&&make clean'

class ESP:
    def __init__(self):
        pass

    def make(self, arg):
        if arg == '--all':
            print arg
            downloadbin = downloadbin_all
        elif arg == '--onebin':
            make = make_one_bin
        elif arg == '--twobin':
            make = make_two_bin

if __name__ == '__main__':
    if len(sys.argv) >= 1:
        make = make_one_bin
        if len(sys.argv) >= 2:
            if sys.argv[1] == '--all':
                print sys.argv[1]
                downloadbin = downloadbin_all
            elif sys.argv[1] == '--onebin':
                make = make_one_bin
            elif sys.argv[1] == '--twobin':
                make = make_two_bin

    command = [
        cleanoldbin,
        make,
        downloadbin,
        OpenUartDebug
    ]
    print cleanoldbin

    for i in range(len(command)):
        try:
	    print command[i]
            if os.system(command[i]) !=0:
                raise Exception('[error]:%s' % command[i])
        except type, reason:
            print reson
            break
