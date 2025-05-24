/*
The fork() function in C is used to create a new child process from the existing parent process. 
It's one of the fundamental concepts in operating systems and process management. 

 What is fork()?
- fork() is a system call in Unix-based operating systems (like Linux) that creates a duplicate process.
- When a program executes fork(), it creates a new process (child process) that runs independently but starts as a copy of the parent.
How does it work?
- When fork() is called, the operating system creates a new process that has the same code and memory as the parent.

*/


#include<stdio.h>  // Standard I/O functions
#include<unistd.h>  // For process-related functions
int main(){

printf("\nHello world");
int f=fork();  // Creates a new child process
int p=getpid();  //// Gets the process ID of the current process
printf("\n the pid is %d",p);
printf("\n the pid is %d",f);


return 0;
}

[2021ict109@fedora ~]$ vi fork.c
[2021ict109@fedora ~]$ gcc fork.c -o fork
[2021ict109@fedora ~]$ ./fork

Hello world
 the pid is 11107
 the pid is 11108
 Hello world
 the pid is 11108
 the pid is 0[2021ict109@fedora ~]$ cat fork.c

 /*
 - The parent process starts execution.
- The fork() function creates a child process, which is an exact copy of the parent at the moment of creation.
- Both parent and child continue execution independently.
- The return value of fork():
- In the child process: fork() returns 0.
- In the parent process: fork() returns the Process ID (PID) of the child.

. Step-by-Step Execution
- Parent starts execution: Prints "Hello world".
- Fork creates a child: The code is now running in two separate processes.
- Each process prints its PID:
- The parent prints its PID and the child's PID.
- The child prints its own PID and a fork() return value of 0.

Hello world
 the pid is 11107   <-- Parent's PID
 the pid is 11108   <-- Parent sees child's PID

Hello world
 the pid is 11108   <-- Child's PID
 the pid is 0       <-- Child sees "fork" return value as 0
 */
-----------------------------------------------------------------
#include<stdio.h>
#include<unistd.h>
int main(){

int f=fork();
int p=getpid();
printf("\nHello world");

if(f==0){
printf("\nThis is child%d,",f);
}
else{
printf("\nThis is a parent%d,",p);
}

return 0;
}

[2021ict109@fedora ~]$ vi fork.c
[2021ict109@fedora ~]$ gcc fork.c -o fork
[2021ict109@fedora ~]$ ./fork

Hello world
This is a parent16649,
Hello world
This is child0,

/*
Hello world
This is a parent16649,  <-- Parent prints child’s PID
Hello world
This is child0,  <-- Child process prints "child 0"
*/
--------------------------------------------------------------------

#include<stdio.h>
#include<unistd.h>
int main(){

int B=fork();
int C=fork();


if(B==0){
printf("\nThis is child");
}
else if(C==0){
	printf("\nThis is sibiling");
}
else{
printf("\nThis is a parent");
}

return 0;
}

This is child: 0This is child: 0[2021ict109@fedora ~]$ vi fork.c
[2021ict109@fedora ~]$ gcc fork.c -o fork
[2021ict109@fedora ~]$ ./fork



This is a parent
This is child

This is childThis is child


/*
      (Initial Parent Process)
               ├── B = fork() → Creates Child
               │       ├── C = fork() → Creates Another Child
               │
               └── C = fork() → Creates Another Child

 What Happens During Execution?
Each fork() creates a new process.
- The first fork() (variable B) creates one new child process.
- The second fork() (variable C) runs for both parent and child, generating additional processes.


 Before fork() execution → Only one parent process exists.
- First fork() (B = fork()) → Now two processes exist.
- Second fork() (C = fork()) → Each of the existing processes runs fork() again, creating four total processes.

*/

------------------------------------------------------


#include<stdio.h>
#include<unistd.h>
int main(){

int f=fork();
if(f==0){
	printf("\nThis is child");
    printf("\n parent pid:%d",getppid());
}
else{
	int f1=fork();
	if(f1==0){
	printf("\nThis is sibiling");
    printf("\n parent pid:%d",getppid());
	}
	else{
			printf("\nThis is parent");
         printf("\n My pid:%d",getppid());
	    printf("\n My parent pid:%d",getppid());


	}
} 
return 0;
}


This is parent
 My pid:8228
 My parent pid:8228
This is child
 parent pid:26946
This is sibiling
 parent pid:26946

 /*
 #include<stdio.h>
#include<unistd.h>

int main(){
    int f = fork();
    int p = getpid();  // Get process ID

    printf("\nHello world");  // Both processes print this

    if(f == 0){
        printf("\nThis is the child process.");
        printf("\nChild PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else {
        printf("\nThis is the parent process.");
        printf("\nParent PID: %d, Child PID: %d\n", getpid(), f);
    }

    return 0;
}
Hello world
This is the parent process.
Parent PID: 12345, Child PID: 12346

Hello world
This is the child process.
Child PID: 12346, Parent PID: 12345

 */