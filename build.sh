#!/bin/bash
gcc jchcar.c -Wall -c -fPIC
gcc -shared jchcar.o -lwiringPiPca9685 -lwiringPi -lm -o libjchcar.so
