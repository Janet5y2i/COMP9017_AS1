#!/bin/bash

# to ensure the script can be run from any location
cd "$(dirname "$0")"

# complile the test program
gcc -g -I.. test_create_canvas.c ../animate.o -o test_create_canvas

# run the test program and check the result
./test_create_canvas
if [ $? -eq 0 ]; then
    echo "Test Create Canvas: PASS"
else
    echo "Test Create Canvas: FAIL"
fi