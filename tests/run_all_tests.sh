#!/bin/bash

#incure the file path of the script
cd "$(dirname "$0")"

#define the color
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "=== Starting Testing ==="
echo "=== First Test: test_create_canvas ==="
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



# The second case
echo "=== Second Test: test_create_circle ==="
gcc -g -I.. test_create_circle.c ../animate.o -o test_create_circle

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_create_circle failed to compile!${NC}"
    exit 1
fi


echo "=== Third Test: check for the pixel data of the circle ==="
./test_create_circle && xxd -g4 test_create_circle.dat > circle_actual.hex

# check if the expected file exist
if [ ! -f "circle_expected.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file circle_expected.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "circle_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file circle_actual.hex"
    exit 1
fi

# compare to the two files
diff circle_actual.hex circle_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass animate_place_sprite test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines circle_actual.hex circle_expected.hex | head -n 10
fi

# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_create_circle > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_create_circle (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_create_circle
fi

# Clean up the executable
rm -f test_create_circle
rm -f test_create_circle.dat
rm -f circle_actual.hex



echo "=== Forth Test: check for the pixel data of the rectangle ==="

# The forth case
gcc -g -I.. test_create_rectangle_filled.c ../animate.o -o test_create_rectangle_filled

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_create_rectangle_filled failed to compile!${NC}"
    exit 1
fi


./test_create_rectangle_filled && xxd -g4 test_create_rectangle_filled.dat > rectangle_filled_actual.hex

# check if the expected file exist
if [ ! -f "rectangle_filled_expected.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file rectangle_filled_expected.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "rectangle_filled_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file rectangle_filled_actual.hex"
    exit 1
fi

# compare to the two files
diff rectangle_filled_actual.hex rectangle_filled_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass animate_place_sprite test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines rectangle_filled_actual.hex rectangle_filled_expected.hex | head -n 10
fi

# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_create_rectangle_filled > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_create_rectangle_filled (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_create_rectangle_filled
fi



# Clean up the executable
rm -f test_create_rectangle_filled
rm -f test_create_rectangle_filled.dat
rm -f rectangle_filled_actual.hex




echo "=== Fifth Test: check for the pixel data of the rectangle ==="

# The fifth case
gcc -g -I.. test_create_rectangle_empty.c ../animate.o -o test_create_rectangle_empty

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_create_rectangle_empty failed to compile!${NC}"
    exit 1
fi


./test_create_rectangle_empty && xxd -g4 test_create_rectangle_empty.dat > rectangle_empty_actual.hex

# check if the expected file exist
if [ ! -f "rectangle_empty_expected.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file rectangle_empty_expected.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "rectangle_empty_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file rectangle_empty_actual.hex"
    exit 1
fi

# compare to the two files
diff rectangle_empty_actual.hex rectangle_empty_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass animate_place_sprite test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines rectangle_empty_actual.hex rectangle_empty_expected.hex | head -n 10
fi

# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_create_rectangle_empty > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_create_rectangle_empty (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_create_rectangle_empty
fi



# Clean up the executable
rm -f test_create_rectangle_empty
rm -f test_create_rectangle_empty.dat
rm -f rectangle_empty_actual.hex