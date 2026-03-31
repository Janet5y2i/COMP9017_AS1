#!/bin/bash

#incure the file path of the script
cd "$(dirname "$0")"

#define the color
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "=== Starting Testing ==="

# step1: complie the case
# -I.. : animate.o is on the last path
gcc -g -I.. test_create_canvas.c ../animate.o -o test_create_canvas

if [ $? -ne 0 ]; then
    echo -e "${RED}Test failed to compile!${NC}"
    exit 1
fi

# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_create_canvas > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_create_canvas (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_create_canvas
fi

# Clean up the executable
rm -f test_create_canvas


gcc -g -I.. test_canvas_size.c ../animate.o -o test_canvas_size

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_canvas_size failed to compile!${NC}"
    exit 1
fi

# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_canvas_size > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_canvas_size (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_canvas_size
fi

# Clean up the executable
rm -f test_canvas_size