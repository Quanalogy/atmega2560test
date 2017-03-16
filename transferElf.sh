#!/bin/bash
avrdude -C avrdude.conf -P/dev/ttyACM0 -cwiring -patmega2560 -b115200 -v -v -v -v -D -Uflash:w:atmega2560test