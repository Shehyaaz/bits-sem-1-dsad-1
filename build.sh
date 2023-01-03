#!/bin/sh
echo "Compiling ...."
# Create output directory if it doesn't exist
mkdir -p output
g++ src/*.cpp -std=c++11 -o output/main
echo "Done ..."