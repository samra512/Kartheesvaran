/*
🔍 What is a Pipe?
A pipe is a unidirectional communication channel:
One process can write data to the pipe.
Another process can read that data from the pipe.

This program:
Creates a pipe.
Writes 3 different messages to the pipe.
Reads the messages from the pipe and prints them.

Important Notes:
The program is using only one process — reading and writing happen in sequence.
Usually, pipes are used between two processes (like parent-child), but here it's just demonstrating how data flows through the pipe.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MSGSIZE 16   //Sets the size of each message to be 16 bytes (characters).

//Defines 3 message strings.
char* msg1 = "Hello, world #1";
char* msg2 = "Hello, world #2";
char* msg3 = "Hello, world #3";

int main(){
    char inbuf[MSGSIZE];  //inbuf[]: buffer for reading messages from the pipe
    int p[2], i;    //p[2]: file descriptor array. After pipe(p), p[0] is the read-end, and p[1] is the write-end.

    if (pipe(p) < 0)   //Creates the pipe.  ,If pipe() fails, it exits the program.
        exit(1);

    //write a pipe ,through p[1] (write end).

    write(p[1], msg1, MSGSIZE); // write(fields, message, messagesize)
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);

    for(i = 0; i < 3; i++){
        /* read pipe */
        read(p[0], inbuf, MSGSIZE);
        printf("%s\n", inbuf);
    }
    return 0;
}

/*
output:
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc pipe1.c -o pipe1
shifak_ahamed@LAPTOP-TQKP6C7B:~$ ./pipe1
Hello, world #1
Hello, world #2
Hello, world #3
*/

-----------------------------------------------------------------------

/* 01. get two input from user(parent process)
    name:
    reg_no:
    age:


   02. Print the output from the child
   name:
   reg_no:
   age:
*/

#include <stdio.h>      // Standard input/output functions (e.g., printf, scanf)
#include <stdlib.h>     // For exit() and general utilities
#include <unistd.h>     // For fork(), pipe(), read(), write()
#include <string.h>     // For string handling (though not directly used here)

#define MSGSIZE 100

int main() {
    char name[MSGSIZE], reg_no[MSGSIZE], age[MSGSIZE];
    char inbuf[MSGSIZE];    //inbuf: buffer used by the child process to read values from the pipe.

    int p[2];
    pid_t pid;

    if (pipe(p) < 0) {
        perror("Pipe failed");
        exit(1);
    }

    printf("Enter name: ");
    scanf(" %[^\n]", name);

    printf("Enter registration number: ");
    scanf(" %[^\n]", reg_no);

    printf("Enter age: ");
    scanf(" %[^\n]", age);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        close(p[0]);

        write(p[1], name, MSGSIZE);
        write(p[1], reg_no, MSGSIZE);
        write(p[1], age, MSGSIZE);
    } else {
        close(p[1]);

        read(p[0], inbuf, MSGSIZE);
        printf("\nChild Process Output:\n");
        printf("Name: %s\n", inbuf);

        read(p[0], inbuf, MSGSIZE);
        printf("Registration Number: %s\n", inbuf);

        read(p[0], inbuf, MSGSIZE);
        printf("Age: %s\n", inbuf);

        exit(0);
    }

    return 0;
}
/*

shifak_ahamed@LAPTOP-TQKP6C7B:~$ vi pipe2.c
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc pipe2.c -o pipe2
^[[Ashifak_ahamed@LAPTOP-TQKP6C7B:~$ ./pipe2
Enter name: samra
Enter registration number: 2021ict109
Enter age: 23

Child Process Output:
Name: samra
Registration Number: 2021ict109
Age: 23
*/

