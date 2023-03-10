/************************************************************************
 * libraries
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

// socket/bind/listen/accept
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// read/write/close
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>

/************************************************************************
 * function prototype declarations
 ************************************************************************/
void *handle_client(void *arg);
void print_requirements();
int get_last_number(int in_length, int chars_before_length, char * input, double * result_nr, char * char_ptr);

/************************************************************************
 * preprocessor directives
 ************************************************************************/
#define SERVER_ADDR "127.0.0.1" // ip address
#define PORT 23657              // port the server will listen on

// number of pending connections in the connection queue
#define NUM_CONNECTIONS 100
