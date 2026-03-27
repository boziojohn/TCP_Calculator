#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 200
#define BUFFER_SIZE MAX_INPUT_LENGTH * sizeof(char)

void read_input(char input_buffer[], int size, int remove_newline_flag);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments!");
        return 1;
    }

    char message_buffer[MAX_INPUT_LENGTH] = {'\0'};

    // socket initialization
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_address.sin_addr);

    // connecting
    int connection_status = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    printf("Please give an equation: ");
    read_input(message_buffer, BUFFER_SIZE, 1);

    send(client_socket, message_buffer, BUFFER_SIZE, 0); // Send the equation

    recv(client_socket, message_buffer, BUFFER_SIZE, 0); // Receive the answer  
    printf("Server response: %s\n", message_buffer);

    close(client_socket);
    return 0;
}

void read_input(char input_buffer[], int size, int remove_newline_flag) // Inspired by Mr. Tselikas book
{
    int length;

    if(fgets(input_buffer, size, stdin) == NULL)
    {
        puts("\nError reading input");
        exit(EXIT_FAILURE);
    }

    length = strlen(input_buffer);

    if(length > 0)
    {
        if(remove_newline_flag && input_buffer[length - 1] == '\n')
        {
            input_buffer[length - 1] = '\0';
        }
        else
        {
            puts("\nError: too few characters");
            exit(EXIT_FAILURE);
        }
    }
}
