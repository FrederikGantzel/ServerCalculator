# ServerCalculator
Program for CS560 "Computer Networking" Assignment 6, NAU, Fall Semester 2021

## Installation
Download the "ServerCalculator" folder and put it wherever you want.
Some external C libraries are required in order to run the server and client pair:

stdio.h

stdlib.h

stdbool.h

signal.h

pthread.h

string.h

math.h

inet.h

socket.h

in.h

uio.h

types.h

unistd.h

I got the packages installed and run the program on a Linux virtual machine using Ubuntu:
https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-11-with-gui-support#1-overview

## Usage
Provides a server and client pair, where the client takes in a single mathematical operation, and sends it to the server, and the server then sends back the result.
To run the program, run the command "make" in the command line (make sure the command line path is set to the ServerCalculator folder you downloaded. Also make sure that you have C installed). Then run the server by typing "./server" in the command line window. In a seperate command line window, set the same path and type "./client" to run the client. Multiple clients can be connected to the server at the same time.

## Example Program:
![image](https://user-images.githubusercontent.com/91853323/215630661-0f07c0b5-80ff-46a7-b25b-08d3c045ad26.png)

