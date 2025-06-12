/* Shared memory

What is this chapter about?
This program demonstrates shared memory IPC (Inter-Process Communication) in C on Unix/Linux systems. 
Shared memory allows multiple processes to access the same memory segment.
 It is a fast way to exchange data between processes because they read/write directly in a shared memory area.




*/
//writer

#include <stdio.h>
#include <stdlib.h>   //exit()
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>  //Shared memory operations

#define SHM_SIZE 1024   //size of shared segment

int main(){
    key_t key=ftok("2021ict109",109);   //Genarate unique key  .It takes a filename and a project ID number.

    //create shared memory segment
    int shmid= shmget(key,SHM_SIZE ,IPC_CREAT | 0666); 

    if (shmid== -1){
        perror("shmget");
        exit(1);
    }
    
    //Attach to shared memory
    char *shmaddr = (char*) shmat(shmid,NULL,0);

    if(shmaddr == (char*)-1){
        perror("shmat");
        exit(1);
    } 

    printf("Write a data:");
    fgets(shmaddr,SHM_SIZE,stdin);   //write the data shared memory

    printf("Data writen in memory: %s\n",shmaddr);

    shmdt(shmaddr); //Detact from shared memory
    
    return 0;

}
 


//Reader

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024   //size of shared segment

int main(){
    key_t key=ftok("2021ict109",109);

    int shmid= shmget(key,SHM_SIZE , 0666); 

    if (shmid== -1){
        perror("shmget");
        exit(1);
    }

//Attach to shared memory
char *shmaddr = (char*) shmat(shmid,NULL,0);

if(shmaddr == (char*)-1){
    perror("shmat");
    exit(1);
} 

printf("Data read from memory: %s\n",shmaddr);

shmdt(shmaddr); //Detact from shared memory

shmctl(shmid,IPC_RMID,NULL);  //Remove shared memory seqment
return 0;

}

/*
shifak_ahamed@LAPTOP-TQKP6C7B:~$ touch 2021ict109
shifak_ahamed@LAPTOP-TQKP6C7B:~$ vi shwriter.c
shifak_ahamed@LAPTOP-TQKP6C7B:~$ vi shreader.c
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc shwriter.c -o shwriter
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc shreader.c -o shreader
shifak_ahamed@LAPTOP-TQKP6C7B:~$ ./shwriter
Write a data:hi sam
Data writen in memory: hi sam

shifak_ahamed@LAPTOP-TQKP6C7B:~$ ./shreader
Data read from memory: hi sam

*/
--------------------------------------------------------------------------------
//02.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    size_t size = 4096;
    char *shared_mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        sprintf(shared_mem, "Hello from child!");
        printf("Child wrote: %s\n", shared_mem);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent read: %s\n", shared_mem);
        munmap(shared_mem, size);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

/*

shifak_ahamed@LAPTOP-TQKP6C7B:~$ vi sharedmemory.c
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc sharedmemory.c -o sharedmemory
shifak_ahamed@LAPTOP-TQKP6C7B:~$ ./sharedmemory
Child wrote: Hello from child!
Parent read: Hello from child!


*/

-------------------------------------------------------------------


/*
Q03.
Write a C program using shared memory (mmap) and fork() to compute combinations (nCr) and permutations (nPr) using the formula:
nCr = n! / (r! * (n - r)!)
nPr = n! / (n - r)!

The parent process should:
Take user input for n and r.

The child process should:
Calculate the factorials of n, r, and n - r.

Store the results in shared memory.
Print the computed factorials.
The parent process should:
Wait for the child to finish.
Read the factorials from shared memory.
Compute and display the values of nCr and nPr.
Use mmap() for inter-process communication instead of System V shared memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    // Allocate shared memory for 3 integers: fact_n, fact_r, fact_n_r
    int *shared = mmap(NULL, 3 * sizeof(int), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    int n, r;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter r: ");
    scanf("%d", &r);

    if (r > n || n < 0 || r < 0) {
        printf("Invalid input. Ensure 0 ≤ r ≤ n\n");
        munmap(shared, 3 * sizeof(int));
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child: calculate factorials and write to shared memory
        shared[0] = factorial(n);       // fact_n
        shared[1] = factorial(r);       // fact_r
        shared[2] = factorial(n - r);   // fact_n_r

        // Output from child
        printf("Child Process:\n");
        printf("Factorial of n (%d): %d\n", n, shared[0]);
        printf("Factorial of r (%d): %d\n", r, shared[1]);
        printf("Factorial of (n - r) (%d): %d\n", n - r, shared[2]);

        exit(0);
    } else if (pid > 0) {
        // Parent
        wait(NULL); // Wait for child

        int fact_n = shared[0];
        int fact_r = shared[1];
        int fact_n_r = shared[2];

        int nCr = fact_n / (fact_r * fact_n_r);
        int nPr = fact_n / fact_n_r;

        printf("\nParent Process:\n");
        printf("nCr = %d\n", nCr);
        printf("nPr = %d\n", nPr);

        // Cleanup
        munmap(shared, 3 * sizeof(int));
    } else {
        perror("fork");
        munmap(shared, 3 * sizeof(int));
        exit(1);
    }

    return 0;
}


/*
output:

shifak_ahamed@LAPTOP-TQKP6C7B:~$ vi shparentchild.c
shifak_ahamed@LAPTOP-TQKP6C7B:~$ gcc shparentchild.c -o shparentchild
shifak_ahamed@LAPTOP-TQKP6C7B:~$ ./shparentchild
Enter n: 5
Enter r: 2
Child Process:
Factorial of n (5): 120
Factorial of r (2): 2
Factorial of (n - r) (3): 6

Parent Process:
nCr = 10
nPr = 20
shifak_ahamed@LAPTOP-TQKP6C7B:~$

*/