#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 

int x;

int main() {
    printf("Enter the number: ");
    scanf("%d", &x);

    int f1 = fork();
    if (f1 == 0) { 
        printf("I am a child C1: %d\n", getpid());
        printf("My parent is P: %d\n", getppid());

        int fact = 1;
        for (int i = 1; i <= x; i++) {
            fact *= i;
        }
        printf("Factorial of %d is: %d\n", x, fact);

        int f4 = fork();
        if (f4 == 0) { 
            printf("I am a child C4: %d\n", getpid());
            printf("My parent is C1: %d\n", getppid());

            
            int a = 0, b = 1, c;
            printf("Fibonacci Series:\n");
            for (int i = 0; i < x; i++) { 
                printf("%d ", a);
                c = a + b;
                a = b;
                b = c;
            }
            printf("\n");
        }
    } 
    else {
        int f2 = fork();
        if (f2 == 0) { // Child C2
            printf("I am a child C2: %d\n", getpid());
            printf("My parent is P: %d\n", getppid());

            
            int base = 2, result = 1;
            for (int i = 0; i < x; i++) {
                result *= base;
            }
            printf("2 to the power of %d is: %d\n", x, result);
        } 
        else {
            int f3 = fork();
            if (f3 == 0) { 
                printf("I am a child C3: %d\n", getpid());
                printf("My parent is P: %d\n", getppid());

                
                int square = x * x;
                printf("Square of %d is: %d\n", x, square);
            } 
            else {
                printf("I am parent P: %d\n", getpid());
                wait(NULL);
                wait(NULL);
                wait(NULL);
            }
        }
    }

    return 0;
}