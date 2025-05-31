/*
Exercise

IPC using Message Queue

read input from the parent process
Enter Name:Hi
Enter RegNo:2021ict109
Enter Age:23

Message send succesfully

Give the output from the child process

Received Name:Samra
Received RegNo:2021ict109
Received Age:23

*/
//include library
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//Define constant
#define MSGKEY 1111
#define MAX_NAME_LEN 100
#define MAX_REGNO_LEN 100

//Define the message structur
struct person {
    long mtype; // Message type
    int age;
    char name[MAX_NAME_LEN];
    char regno[MAX_REGNO_LEN];
};

//start the main function
int main() {
    int msqid;
    struct person p1, p2;
    int f = fork();

// Child process: Receiver
    if (f == 0) {

//Create a message queue
        msqid = msgget(MSGKEY, IPC_CREAT | 0666); 
        if (msqid == -1) {
            perror("msgget failed");
            exit(EXIT_FAILURE);
        }

//calculate the message type
        int msg_size = sizeof(struct person) - sizeof(long);

 //Receive message
        if (msgrcv(msqid, &p2, msg_size, 0, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        } else {
  //Display the receive data          
            printf("Received Name: %s\n", p2.name);
            printf("Received RegNo: %s\n", p2.regno);
            printf("Received Age: %d\n", p2.age);
        }

//Remove the message queue
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
 // Parent process: Sender
      
    } else {

 //create a message queue       
        msqid = msgget(MSGKEY, IPC_CREAT | 0666);
        if (msqid == -1) {
            perror("msgget failed");
            exit(EXIT_FAILURE);
        }

//set message type
        p1.mtype = 1;

 //Read input from user       
        printf("Enter Name: ");
        scanf("%s", p1.name);

        printf("Enter RegNo: ");
        scanf("%s", p1.regno);

        printf("Enter Age: ");
        scanf("%d", &p1.age);

//Calculate the message type
        int msg_size = sizeof(struct person) - sizeof(long);

 //send message       
        if (msgsnd(msqid, &p1, msg_size, IPC_NOWAIT) == -1) {
            perror("msgsnd failed");
        } else {
            printf("Message sent successfully.\n");
        }

//Exit parent
        exit(0);
    }

    return 0;
}
