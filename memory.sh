#!/bin/bash

clear                                   # clear the outputs
g++ *.cpp                               # compile the program
./a.out                                 # run the program
valgrind --leak-check=full -v ./a.out   # check for memory leak
g++ -g -Wall -std=c++11 *.cpp -o test   # display where the memory leak is