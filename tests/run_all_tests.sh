#!/bin/bash

#incure the file path of the script
cd "$(dirname "$0")"

#define the color
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "=== Starting Testing ==="
echo "=== Case1: test_create_canvas ==="
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
echo "=== Case2: test_create_circle ==="
gcc -g -I.. test_create_circle.c ../animate.o -o test_create_circle

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_create_circle failed to compile!${NC}"
    exit 1
fi


echo "=== Case3: check for the pixel data of the circle ==="
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



echo "=== Case4: check for the pixel data of the rectangle ==="

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




echo "=== Case5: check for the pixel data of the rectangle ==="

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





echo "=== Case6: check for the pixel data of the layer ==="

# The sixth case
gcc -g -I.. test_layer.c ../animate.o -o test_layer

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_layer failed to compile!${NC}"
    exit 1
fi


./test_layer && xxd -g4 test_layer.dat > layer_actual.hex

# check if the expected file exist
if [ ! -f "layer_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file layer_actual.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "layer_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file layer_actual.hex"
    exit 1
fi

# compare to the two files
diff layer_actual.hex layer_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass layer test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines layer_actual.hex layer_expected.hex | head -n 10
fi


echo "=== Case7: check for the pixel data of the top layer function ==="


./test_layer && xxd -g4 test_layer_top.dat > layer_top_actual.hex

# check if the expected file exist
if [ ! -f "layer_top_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file layer_top_actual.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "layer_top_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file layer_actual.hex"
    exit 1
fi

# compare to the two files
diff layer_top_actual.hex layer_top_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass top layer test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines layer_top_actual.hex layer_top_expected.hex | head -n 10
fi



echo "=== Case8: check for the pixel data of the down layer function ==="


./test_layer && xxd -g4 test_layer_down.dat > layer_down_actual.hex

# check if the expected file exist
if [ ! -f "layer_down_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file layer_down_actual.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "layer_down_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file layer_actual.hex"
    exit 1
fi

# compare to the two files
diff layer_down_actual.hex layer_down_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass down layer test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines layer_down_actual.hex layer_down_expected.hex | head -n 10
fi



echo "=== Case9: check for the pixel data of the up layer function ==="


./test_layer && xxd -g4 test_layer_up.dat > layer_up_actual.hex

# check if the expected file exist
if [ ! -f "layer_up_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file layer_up_actual.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "layer_up_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file layer_up_actual.hex"
    exit 1
fi

# compare to the two files
diff layer_up_actual.hex layer_up_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass up layer test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines layer_up_actual.hex layer_up_expected.hex | head -n 10
fi



echo "=== Case10: check for the pixel data of the up layer function ==="


./test_layer && xxd -g4 test_layer_bottom.dat > layer_bottom_actual.hex

# check if the expected file exist
if [ ! -f "layer_bottom_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file layer_bottom_actual.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "layer_bottom_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file layer_bottom_actual.hex"
    exit 1
fi

# compare to the two files
diff layer_bottom_actual.hex layer_bottom_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass bottom layer test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines layer_bottom_actual.hex layer_bottom_expected.hex | head -n 10
fi


# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_layer > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_layer (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_layer
fi



# Clean up the executable
rm -f test_layer
rm -f test_layer.dat
rm -f layer_actual.hex
rm -f test_layer_top.dat
rm -f layer_top_actual.hex
rm -f test_layer_down.dat
rm -f layer_down_actual.hex
rm -f test_layer_up.dat
rm -f layer_up_actual.hex
rm -f test_layer_bottom.dat
rm -f layer_bottom_actual.hex



echo "=== Case11: check for the move of sprite ==="



# The forth case
gcc -g -I.. test_animate.c ../animate.o -o test_animate

if [ $? -ne 0 ]; then
    echo -e "${RED}Test - test_animate failed to compile!${NC}"
    exit 1
fi


./test_animate && xxd -g4 test_animate_t0.dat > test_animate_t0_actual.hex

# check if the expected file exist
if [ ! -f "test_animate_t0_expected.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file test_animate_t0_expected.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "test_animate_t0_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file test_animate_t0_actual.hex"
    exit 1
fi

# compare to the two files
diff test_animate_t0_actual.hex test_animate_t0_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass animate_place_sprite test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines test_animate_t0_actual.hex test_animate_t0_expected.hex | head -n 10
fi



./test_animate && xxd -g4 test_animate_t1.dat > test_animate_t1_actual.hex

# check if the expected file exist
if [ ! -f "test_animate_t1_expected.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No such file test_animate_t1_expected.hex"
    exit 1
fi

# check if the output exist
if [ ! -f "test_animate_t1_actual.hex" ]; then
    echo -e "${RED}[FAIL]${NC} No output file test_animate_t1_actual.hex"
    exit 1
fi

# compare to the two files
diff test_animate_t1_actual.hex test_animate_t1_expected.hex > /dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} Pass animate_place_sprite test"
else
    echo -e "${RED}[FAIL]${NC} Pixel content mismatch"
    diff -y --suppress-common-lines test_animate_t1_actual.hex test_animate_t1_expected.hex | head -n 10
fi



# 2. Using Valgrind to check for memory leaks and errors
echo "Checking for memory leaks and errors..."
valgrind --leak-check=full --error-exitcode=1 ./test_animate > /dev/null 2>&1


if [ $? -eq 0 ]; then
    echo -e "${GREEN}[PASS]${NC} test_animate (Function and memory are both normal)"
else
    echo -e "${RED}[FAIL]${NC} Memory leak or execution error detected!"
    # If failed, run again to display detailed errors
    valgrind --leak-check=full ./test_animate
fi


# Clean up the executable
rm -f test_animate
rm -f test_animate_t0.dat
rm -f test_animate_t0_actual.hex
rm -f test_animate_t1.dat
rm -f test_animate_t1_actual.hex