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

\> make

gcc -o client client.c -lm

gcc -o server server.c -lm -pthread

\> ./server

\> ./client (In a seperate window)

_______SERVER_______

Accepted Client

_______CLIENT_______

Connected to server.

REQUEST REQUIREMENTS:

Six types of operations can be requested:

Addition (+), subtraction (-), multiplication (*), division (/),

raising to a number power (^), and taking the square root (sqrt)

Requests must follow the following structure:

[first number] [requested operation] [second number]

or in the case of taking the square root:

sqrt [number]

(notice the spacebars between numbers and operators)

Some examples:

46 + 23.7

29.1 - 29.9

5 ^ 3

sqrt 49

Only one operation between two numbers may be inputted at a time,

or in the case of taking the square root, only one operation and one number

Numbers must be real.

In the case of division, the number input after the division operator must not be zero.

In the case of taking the square root, the number must not be negative.

To terminate connection to the server, enter the command "END" (in all capital letters)

Ready to take requests.

Input:

\> 25 + 4

_______SERVER_______

Adding together 25.000000 and 4.000000

Result: 29.000000

_______CLIENT_______

Result: 29.000000

Input:

\> 300 / 7

_______SERVER_______

Dividing 300.000000 by 7.000000

Result: 42.857143

_______CLIENT_______

Result: 42.857143

Input:

\> END

Ending connection to server
