#include "header.h"

/************************************************************************
 * MAIN
 ************************************************************************/


pthread_mutex_t lock;

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    int client_socket;
    pthread_mutex_init(&lock, NULL);

    // sent when ,client disconnected
    signal(SIGPIPE, SIG_IGN);

    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on

    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    pthread_t new_thread;
    // server loop
    while (1) {

        pthread_mutex_lock(&lock);
        // accept connection to client
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
            perror("Error accepting client");
        } else {
            printf("\nAccepted client\n");

            //we create a now thread, so multiple clients can be connected to the server
            //at the same time
            if (pthread_create(&new_thread, NULL, handle_client, (void *)&client_socket) != 0) {
              printf("\nError while creating thread\n");
              exit(1);
            }

            if (pthread_detach(new_thread) != 0) {
              printf("\nError in detaching thread\n");
              exit(1);
            }

        }
    }
}


/************************************************************************
 * handle client
 ************************************************************************/

void *handle_client(void *arg) {
    char input_operation;
    double first_number;
    double second_number;
    double result;
    int keep_going = 1;
    int client_socket = *(int *)arg;

    pthread_mutex_unlock(&lock);

    //server loop
    while (keep_going) {

      // read operation from client
      if (read(client_socket, &input_operation, sizeof(char)) == 0) {
          perror("Error reading from network!\n");
      }

      //if operation = e, we end the server loop
      if (input_operation == 'e') {
        keep_going = 0;
      } else if (input_operation == 's') { //if the operation is the square root, we only need to receive one number
        if (read(client_socket, &first_number, sizeof(double)) == 0) {
            perror("Error reading from network!\n");
        }
        printf("Taking square root of %f\n", first_number);

        result = sqrt(first_number);
      } else { //if any operation other than the square root or END, we need to receive two numbers
        if (read(client_socket, &first_number, sizeof(double)) == 0) {
            perror("Error reading from network!\n");
        }
        if (read(client_socket, &second_number, sizeof(double)) == 0) {
            perror("Error reading from network!\n");
        }

        if (input_operation == '+') {
          printf("Adding together %f and %f\n", first_number, second_number);
          result = first_number + second_number;
        } else if (input_operation == '-') {
          printf("Subtracting %f from %f\n", second_number, first_number);
          result = first_number - second_number;
        } else if (input_operation == '*') {
          printf("Multiplying %f by %f\n", first_number, second_number);
          result = first_number * second_number;
        } else if (input_operation == '/') {
          printf("Dividing %f by %f\n", first_number, second_number);
          result = first_number / second_number;
        } else {
          printf("Raising %f to the power of %f\n", first_number, second_number);
          result = pow(first_number, second_number);
        }
      }

      //we send the result back (if the server loop was not ended)
      if (input_operation != 'e') {
        printf("Result: %f\n\n", result);
        write(client_socket, &result, sizeof(double));
      }

    }

    // cleanup
    if (close(client_socket) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    } else {
        printf("\nClosed socket to client, exit");
    }
    return NULL;
}
