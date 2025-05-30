#include <stdio.h>   // For input/output functions like printf
#include <unistd.h>  //for sleep
#include <stdlib.h>  //for exit

int main(){

printf("Program started\n");

printf("Sleeping for 3 seconds\n");
sleep(3);   // Pause the program for 3 seconds


printf("Exit the program\n");
exit(0);    // Exit the program with status 0 (indicating successful completion)
return 0;

}
---------------------------------------------------
output:
[2021ict109@fedora ~]$ vi wait.c
[2021ict109@fedora ~]$ gcc wait.c -o wait
[2021ict109@fedora ~]$ ./wait
Program started
Sleeping for 3 seconds
Exit the program
[2021ict109@fedora ~]$

Explanation:
sleep(3): The program pauses for 3 seconds, 
which means that the next line of code wont execute until that 3-second period is over.

exit(0): The program exits with a status code of 0,
 which indicates successful termination. Once the exit() function is called, the program terminates, and no further code after it (like return 0) is executed.
 
 ========================================================
 
#include <stdio.h>   // For input/output functions like printf
#include <unistd.h>  //for sleep
#include <stdlib.h>  //for exit
#include <sys/wait.h>  //for wait

int main(){
 
 pid_t pid;  // pid_t is a data type used in C programming (especially in Unix/Linux systems) to store process IDs.
 
printf("parent process started. PID:%d\n",getpid());

 pid=fork();

if (pid<0){
	perror("fork failed");
	exit(1);
}

	if(pid==0){
		//child process
		printf("Child process. PID:%d , sleeping for 2 second..\n",getpid());
		sleep(2);
		printf("Child process exit\n");
		exit(0);
	}
	else{
		//parent process
		int status;
		printf("parent waiting for Child finished..\n");
        wait(&status);
		if(WIFEXITED(status)){
			printf("child exited with status:%d\n",WEXITSTATUS(status));
		}
		else{
			printf("Child did not exit normally.\n");
		}
		printf("Parent process ending..\n");
	}

return 0;

}
--------------------------------------
output:
[2021ict109@fedora ~]$ vi wait.c
[2021ict109@fedora ~]$ gcc wait.c -o wait
[2021ict109@fedora ~]$ ./wait
parent process started. PID:10730
parent waiting for Child finished..
Child process. PID:10731 , sleeping for 2 second..
Child process exit
child exited with status:0
Parent process ending..
[2021ict109@fedora ~]$


===================================
/*
Exercise

First Child:Slept for 1 second
Seconf Child:Slept for 3 second
Parent: Both children have finished

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    printf("parent process started. PID:%d\n", getpid());
    printf("parent waiting for both Child finished..\n");

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for first child");
        exit(1);
    }

    if (pid1 == 0) {
        // First child
        printf("Child process. PID:%d , sleeping for 1 second..\n", getpid());
        sleep(1);
        printf("1st Child process exit\n");
        exit(0);
    } else {
        // Parent creates second child after first child
        waitpid(pid1, &status, 0); // Wait for first child to finish

        pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed for second child");
            exit(1);
        }

        if (pid2 == 0) {
            // Second child
            printf("Child process. PID:%d , sleeping for 3 second..\n", getpid());
            sleep(3);
            printf("2nd Child process exit\n");
            exit(0);
        } else {
            waitpid(pid2, &status, 0); // Wait for second child
            printf("Parent process ending..\n");
        }
    }

    return 0;
}


----------------------------------------
output:
[2021ict109@fedora ~]$ vi wait.c
[2021ict109@fedora ~]$ gcc wait.c -o wait
[2021ict109@fedora ~]$ ./wait
parent process started. PID:20124
parent waiting for both Child finished..
Child process. PID:10972 , sleeping for 1 second..
1st Child process exit
Child process. PID:19656 , sleeping for 3 second..
2nd Child process exit
Parent process ending..



=============================================================

/*
Exercise 02

First Child:Slept for 2 second ,exit with status 2
Seconf Child:Slept for 1 second ,exit with status 1
Parent: waits twice, and prints which child by (by PID or exit code)
Finished first and second

*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    printf("Parent process started. PID: %d\n", getpid());

    // First child
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    if (pid1 == 0)
    {
        // First child process
        printf("First child process. PID: %d, sleeping for 2 seconds...\n", getpid());
        sleep(2);
        printf("First child exiting with status 2.\n");
        exit(2);
    }
    else
    {
        // Parent creates second child
        pid2 = fork();
        if (pid2 < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        if (pid2 == 0)
        {
            // Second child process
            printf("Second child process. PID: %d, sleeping for 1 second...\n", getpid());
            sleep(1);
            printf("Second child exiting with status 1.\n");
            exit(1);
        }
        else
        {
            // Parent process waits for both children separately
            int status;
            pid_t finished_pid;

            for (int i = 0; i < 2; i++)
            {
                finished_pid = wait(&status);
                if (finished_pid == -1)
                {
                    perror("wait failed");
                    exit(1);
                }

                if (WIFEXITED(status))
                {
                    printf("Child with PID %d exited with status: %d\n", finished_pid, WEXITSTATUS(status));
                }
                else
                {
                    printf("Child with PID %d did not exit normally.\n", finished_pid);
                }
            }
            printf("Parent: Both children have finished.\n");
        }
    }

    return 0;
}


{ ~ }  » vi fork.c                                                                            ~ 1
{ ~ }  » gcc fork.c -o fork  
   Parent process started. PID: 10880
First child process. PID: 20776, sleeping for 2 seconds...
Second child process. PID: 10180, sleeping for 1 second...
Second child exiting with status 1.
Child with PID 10180 exited with status: 1
First child exiting with status 2.
Child with PID 20776 exited with status: 2
Parent: Both children have finished.
{ ~ }  »                                             
===============================================

/*
Exercise 03
The parent creates a child process
The child creates a grandchild process
The grandchild sleep 2 second and exits with status 2
The child waits for the grandchild , print its exit status
then exits with status 55 

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;
    int status;

    printf("Parent process started. PID: %d\n", getpid());

    child_pid = fork();

    if (child_pid < 0) {
        perror("Failed to fork child");
        exit(1);
    }

    if (child_pid == 0) {
        // Inside child process
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Failed to fork grandchild");
            exit(1);
        }

        if (grandchild_pid == 0) {
            // Inside grandchild process
            printf("Grandchild process started. PID: %d\n", getpid());
            sleep(2);
            printf("Grandchild exiting with status 2\n");
            exit(2);
        } else {
            // Child waits for grandchild
            waitpid(grandchild_pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("Child: Grandchild exited with status %d\n", WEXITSTATUS(status));
            }
            printf("Child exiting with status 55\n");
            exit(55);
        }
    } else {
        // Parent waits for child
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        }
        printf("Parent process ending.\n");
    }

    return 0;
}

--------------------------
output:
{ ~ }  » vi fork.c                                                                            ~ 1
{ ~ }  » gcc fork.c -o fork                                                                     ~
{ ~ }  » ./fork                                                                                 ~
Parent process started. PID: 13780
Grandchild process started. PID: 1796
Grandchild exiting with status 2
Child: Grandchild exited with status 2
Child exiting with status 55
Parent: Child exited with status 55
Parent process ending.