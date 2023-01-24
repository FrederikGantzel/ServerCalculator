#include "header.h"

/************************************************************************
 * MAIN
 ************************************************************************/


int main() {
    char input[100];                    // buffer for user input
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    double received_result;
    char *char_ptr;
    char operation;
    int successful_send = 0;

    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);

    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    } else {
      printf("\nConnected to server.\n\n");
      print_requirements();
      printf("Ready to take requests.\n\n");
    }

    //server loop
    while (1) {
        printf("Input: ");
        // read string
        fgets(input, sizeof(input), stdin);

        int in_length = 0;
        while (*(input + in_length)) {
            in_length++;
        }

        //check for END command. If we get END, we just shut down connection
        if (strncmp(input, "END", 3) == 0) {
          operation = 'e';
          write(client_socket, &operation, sizeof(char));
          close(client_socket);
          printf("\nEnding connection to server\n");
          exit(EXIT_SUCCESS);
        }

        //Chech for square root. If we get square root we only need to check for
        //one more number
        if (strncmp(input, "sqrt ", 5) == 0) {
          operation = 's';
          double first_number;

          if (get_last_number(in_length, 5, input, &first_number, char_ptr) == 0) {
            if (first_number < 0) {
              printf("\nCannot take the square root of a negative number. See request requirements:\n\n");
              print_requirements();
            } else {
              successful_send = 1;
              write(client_socket, &operation, sizeof(char));
              write(client_socket, &first_number, sizeof(double));
            }
          }
        //If the input is neither END nor sqrt, we know the first part of the
        //input should be a number, and thus we take the first part of the input
        //(until a space is encounteres), and try to turn it into a number with
        //the strtod function
        } else {
          //we figure out how many characters the first number is, so we can declare a proper char array for it
          int first_number_length = 0;
          while (*(input + first_number_length)) {
            if (input[first_number_length] == ' ') {
              break;
            }
            first_number_length++;
          }

          //we make a char array of the first number, and turn it into a double with strtod
          char first_str_number[first_number_length];

          for(int i=0; i<first_number_length; i++) {
              first_str_number[i] = input[i];
          }
          double first_number = strtod(first_str_number, &char_ptr);

          //strtod returns 0 if it could not translate the string into a double,
          //so if first_number is 0, we need to check if it is because strtod
          //failed to turn it into a number, or if it is because the input number
          //is actually 0
          if (first_number == 0 && !(first_str_number[0] == '0') ) {
            printf ("\nInvalid input. See request requirements:\n\n");
            print_requirements();
          } else {
            //if the first number is inputted correctly, we move on to the operator.
            //we know the operator should be one character, with a space on each side,
            //so we check the three next characters in the input
            char str_operation[first_number_length];
            for (int i=0; i<3; i++) {
              str_operation[i] = input[first_number_length+i];
            }

            //we check each of the operators. If the input is none of these,
            //we will throw an error.
            if (strcmp(str_operation, " + ") == 0) {
              operation = '+';
              double second_number;

              if (get_last_number(in_length, first_number_length+3, input, &second_number, char_ptr) == 0) {
                successful_send = 1;
                write(client_socket, &operation, sizeof(char));
                write(client_socket, &first_number, sizeof(double));
                write(client_socket, &second_number, sizeof(double));
              }
            } else if (strcmp(str_operation, " - ") == 0) {
              operation = '-';
              double second_number;

              if (get_last_number(in_length, first_number_length+3, input, &second_number, char_ptr) == 0) {
                successful_send = 1;
                write(client_socket, &operation, sizeof(char));
                write(client_socket, &first_number, sizeof(double));
                write(client_socket, &second_number, sizeof(double));
              }
            } else if (strcmp(str_operation, " * ") == 0) {
              operation = '*';
              double second_number;

              if (get_last_number(in_length, first_number_length+3, input, &second_number, char_ptr) == 0) {
                successful_send = 1;
                write(client_socket, &operation, sizeof(char));
                write(client_socket, &first_number, sizeof(double));
                write(client_socket, &second_number, sizeof(double));
              }
            } else if (strcmp(str_operation, " / ") == 0) {
              operation = '/';
              double second_number;

              if (get_last_number(in_length, first_number_length+3, input, &second_number, char_ptr) == 0) {
                if (second_number == 0) {
                  printf("\nCannot divide a number by zero. See request requirements:\n\n");
                  print_requirements();
                } else {
                  successful_send = 1;
                  write(client_socket, &operation, sizeof(char));
                  write(client_socket, &first_number, sizeof(double));
                  write(client_socket, &second_number, sizeof(double));
                }
              }
            } else if (strcmp(str_operation, " ^ ") == 0) {
              operation = '^';
              double second_number;

              if (get_last_number(in_length, first_number_length+3, input, &second_number, char_ptr) == 0) {
                successful_send = 1;
                write(client_socket, &operation, sizeof(char));
                write(client_socket, &first_number, sizeof(double));
                write(client_socket, &second_number, sizeof(double));
              }
            } else {
              printf ("\nInvalid input. See request requirements:\n\n");
              print_requirements();
            }

          }
        }

        //reads only if something was sent to the server
        if (successful_send == 1) {
          read(client_socket, &received_result, sizeof(double));
          printf("Result: %f\n\n", received_result);
          successful_send = 0;
        }

    }

    return EXIT_SUCCESS;
}

//This function just prints the instructions, in case the input is wrong
void print_requirements() {
  printf("REQUEST REQUIREMENTS:\n\n");
  printf("Six types of operations can be requested:\n");
  printf("Addition (+), subtraction (-), multiplication (*), division (/),\nraising to a number power (^), and taking the square root (sqrt)\n\n");
  printf("Requests must follow the following structure:\n");
  printf("[first number] [requested operation] [second number]\n");
  printf("or in the case of taking the square root:\n");
  printf("sqrt [number]\n");
  printf("(notice the spacebars between numbers and operators)\n\n");
  printf("Some examples:\n");
  printf("46 + 23.7\n");
  printf("29.1 - 29.9\n");
  printf("5 ^ 3\n");
  printf("sqrt 49\n\n");
  printf("Only one operation between two numbers may be inputted at a time,\nor in the case of taking the square root, only one operation and one number\n");
  printf("Numbers must be real.\n");
  printf("In the case of division, the number input after the division operator must not be zero.\n");
  printf("In the case of taking the square root, the number must not be negative.\n\n");
  printf("To terminate connection to the server, enter the command \"END\" (in all capital letters)\n\n");
}

//this gets the last number (provided that the last number was entered correctly).
int get_last_number(int in_length, int chars_before_length, char * input, double * result_nr, char * char_ptr) {
  char str_number[in_length-chars_before_length];
  int i = chars_before_length;
  while (*(input + i)) {
      str_number[i-chars_before_length] = input[i];
      i++;
  }
  (*result_nr) = strtod(str_number, &char_ptr);

  if ((*result_nr) == 0 && !(str_number[0] == '0') ) {
    printf ("\nInvalid input. See request requirements:\n\n");
    print_requirements();
    return 1;
  } else {
    return 0;
  }
}
