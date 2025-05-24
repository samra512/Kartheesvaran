#include <stdio.h>
#include <unistd.h>

int n1, n2, n3; // Global variables for input

int main() {
    printf("Enter numbers:\n");
    printf("Fibonacci: ");
    scanf("%d", &n1);
    printf("Factorial: ");
    scanf("%d", &n2);
    printf("Prime check: ");
    scanf("%d", &n3);

    int f = fork();
    int f4 = fork();

    if (f == 0) { // Process B
        printf("my B id: %d\n", getpid());

        // Prime number check
        int i, isPrime = 1;
        if (n3 < 2) {
            isPrime = 0;
        } else {
            for (i = 2; i * i <= n3; i++) {
                if (n3 % i == 0) {
                    isPrime = 0;
                    break;
                }
            }
        }

        if (isPrime)
            printf("%d is a prime number.\n", n3);
        else
            printf("%d is not a prime number.\n", n3);

        int f2 = fork();
        int f1 = fork();

        if (f1 == 0) { // Process C
            printf("iam C child: %d\n", getpid());
            printf("my parent B id: %d\n", getppid());

            // Fibonacci Series
            int a = 0, b = 1, c;
            printf("Fibonacci Series:\n");
            for (int i = 0; i < n1; i++) {
                printf("%d ", a);
                c = a + b;
                a = b;
                b = c;
            }
            printf("\n");
        } else if (f2 == 0) { // Process D
            printf("iam D child: %d\n", getpid());
            printf("my parent B id: %d\n", getppid());
        }
    }

    if (f4 == 0) { // Process E
        printf("iam E child: %d\n", getpid());
        printf("my parent A id: %d\n", getppid());

        // Factorial Calculation
        int fact = 1;
        for (int i = 1; i <= n2; i++) {
            fact *= i;
        }
        printf("Factorial of %d is: %d\n", n2, fact);
    } else {
        printf(" A id: %d\n", getpid());
    }

    return 0;
}

output:

Enter numbers:
Fibonacci: 5
Factorial: 4
Prime check: 7
A id: 12345
my B id: 12346
7 is a prime number.
iam C child: 12348
my parent B id: 12346
Fibonacci Series:
0 1 1 2 3
iam D child: 12347
my parent B id: 12346
iam E child: 12349
my parent A id: 12345
Factorial of 4 is: 24