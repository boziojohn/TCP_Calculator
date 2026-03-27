#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_PENDING_CONNECTIONS 13
#define MAX_INPUT_LENGTH 100
#define BUFFER_SIZE MAX_INPUT_LENGTH * sizeof(char)

typedef enum operators
{
    PLUS = 0,
    MINUS,
    MULT,
    DIV,
} Operator;

typedef int Value;

Value calculate_solution(Operator op, Value operand1, Value operand2);
Operator identify_operator(char *expression, Value *operand1, Value *operand2);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Wrong number of arguments!");
        return 1;
    }

    Operator op;
    Value result, operand1, operand2;
    char buffer[MAX_INPUT_LENGTH] = {'\0'};

    // socket initialization
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // binding
    struct sockaddr_in server_address;
    socklen_t address_length;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_status = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listening
    listen(server_socket, MAX_PENDING_CONNECTIONS);

    // accepting
    int client_socket = accept(server_socket, NULL, NULL);

    recv(client_socket, buffer, BUFFER_SIZE, 0);

    op = identify_operator(buffer, &operand1, &operand2);
    result = calculate_solution(op, operand1, operand2);

    if (op == -1 || result == INT_MAX)
    {
        strcpy(buffer, "Wrong input, Please ensure you give a valid equation");
    }
    else
    {
        sprintf(buffer, "%d", result);
    }

    send(client_socket, buffer, BUFFER_SIZE, 0);

    close(server_socket);
    return 0;
}

Value calculate_solution(Operator op, Value operand1, Value operand2)
{
    switch (op)
    {
        case PLUS:
            return operand1 + operand2;

        case MINUS:
            return operand1 - operand2;

        case MULT:
            return operand1 * operand2;

        case DIV:
            if (operand2 == 0)
            {
                return INT_MAX;
            }
            else
            {
                return operand1 / operand2;
            }

        default:
            return INT_MAX;
    }
}

Operator identify_operator(char *expression, Value *operand1, Value *operand2)
{
    char *operator_position = NULL;
    Operator op = -1;

    if ((operator_position = strchr(expression, '+')) != NULL)
    {
        op = PLUS;
    }
    else if ((operator_position = strchr(expression, '-')) != NULL)
    {
        op = MINUS;
    }
    else if ((operator_position = strchr(expression, '*')) != NULL)
    {
        op = MULT;
    }
    else if ((operator_position = strchr(expression, '/')) != NULL)
    {
        op = DIV;
    }

    if (op != -1)
    {
        *operand1 = atoi(expression);
        *operand2 = atoi(operator_position + 1);
    }

    return op;
}
