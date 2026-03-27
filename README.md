# TCP_Calculator
A simple TCP-based calculator in C. The client sends a math equation to the server, which computes and returns the result. Supports +, -, *, and / operations

A simple client-server calculator implemented in C using TCP sockets.  
The client sends a mathematical equation to the server, which computes the result and sends it back. Supports addition (+), subtraction (-), multiplication (*), and division (/).

## Features
- Client-server communication over TCP
- Parses and evaluates simple math equations
- Handles invalid inputs gracefully
- Easy to compile and run on any system with C compiler

## Files
- `client.c` – Connects to the server and sends an equation
- `server.c` – Listens for client connections and calculates the result

## Usage

### Compile
```bash
gcc -o server server.c
gcc -o client client.c
