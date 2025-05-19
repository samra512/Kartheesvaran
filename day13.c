1. Enter a your age and varify your aligible or not for election voting

code:
#include <stdio.h>
int main(){
	
	int age;
	printf("Enter your age:%d",age);
	scanf("%d",&age)
	
	if(age>=18){
		printf("You are aligible for vote");
	}
	else{
	   printf("You are not aligible for vote");
	}
	return 0;
}

output:
[2021ict109@fedora ~]$ gcc day_2.c -o day_2
[2021ict109@fedora ~]$ ./day_2
Enter your age:022
You are aligible for vote[2021ict109@fedora ~]$ ./day_2
Enter your age:011
You are not aligible for vote[2021ict109@fedora ~]$

--------------------------------------------------------------------
2. if condition Ternary operator
syntax:
test condition ? expresion1 :expresion2;

code:
#include <stdio.h>
int main(){
	
	int age;
	printf("Enter your age:%d",age);
	scanf("%d",&age);
	
	 (age>18) ? printf("You are aligible") : printf("You are not aligible");
	 
	return 0;
}
output:
[2021ict109@fedora ~]$ vi day_2.c
[2021ict109@fedora ~]$ gcc day_2.c -o day_2
[2021ict109@fedora ~]$ ./day_2
Enter your age:025
You are aligible[2021ict109@fedora ~]$ ./day_2
Enter your age:012
You are not aligible[2021ict109@fedora ~]$


3. Enter the value between 1 to 7 and create a program 

Enter the number between 1 to 7:1
Today is Monday!

#include <stdio.h>
int main(){
	
	int day;
	printf("Enter your number between 1 to 7");
	scanf("%d",&day);
	
	switch (day) {
  case 1:
     printf("Today is Monday");
    break;
  case 2:
    printf("Today is Tuesday");
    break;
  case 3:
    printf("Today is Wendesday");
    break;
 case 4:
    printf("Today is Thursday");
    break;
	case 5:
    printf("Today is Friday");
    break;
	case 6:
    printf("Today is Saturday");
    break;
	case 7:
    printf("Today is Sunday");
    break;
  default:
    printf("Invalid number");
}
	
	
	return 0;
}

output:
[2021ict109@fedora ~]$ ./day_2
Enter your number between 1 to 74
Today is Thursday[2021ict109@fedora ~]$

---------------------------------------------

04. Write a code for small astrology based on your life path number for that get date of from user 
    than calculate life path number .(use switch case)
	
	Date :23
	calculation Life path number
	     a=date%10;
		 b=date/10;
		 c=a+b;
		 
		 if life path number:
		   1.Lucky
		   2.Careful do your work
		   3.Storger
		   4.Happy
		   5.Can get help
		   6.Doubt
		   7.Sad
		   8.Like
		   9.Courage
		   
code:

#include <stdio.h>
int main(){
	
	int date;
	printf("Enter your date:");
	scanf("%d",&date);
	
	    int a=date%10;
		int  b=date/10;
		 int c=a+b;
	
	switch (c){
		case 1:
     printf("Lucky");
    break;
  case 2:
    printf("Careful do your work");
    break;
  case 3:
    printf("Storger");
    break;
 case 4:
    printf("Happy");
    break;
	case 5:
    printf("Can get help");
    break;
	case 6:
    printf("Doubt");
    break;
	case 7:
    printf("Sad");
    break;
	case 8:
    printf("Like");
    break;
	case 9:
    printf("Courage");
    break;
  default:
    printf("Invalid number");
	}
	
	return 0;
	
}		   

output:
[2021ict109@fedora ~]$ ./day_2
Enter your date:12
Storger[2021ict109@fedora ~]$

-------------------------------------------

05.  Give list number then calculate the summation and multiplication using for loop
Example:
 1 2 3 4 5 
 summation=15
 Multiplication=120
 
 #include <stdio.h>

int main() {
    int n, i;
    int sum = 0, mul = 1; 

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];

    printf("Enter %d numbers: ", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]); 
        sum =sum+ arr[i]; 
        mul =mul* arr[i]; 
    }

    printf("Summation = %d\n", sum);
    printf("Multiplication = %d\n", mul);

    return 0;
}

output:
[2021ict109@fedora ~]$ ./day_2
Enter the number of elements: 5
Enter 5 numbers: 1
2
3
4
5
Summation = 15
Multiplication = 120

-------------------------------------------

06. Print the integer from 1 to 10 using while loop

#include <stdio.h>
int main(){
	
	int i=1;
	while(i<=10){
		printf("%d",i);
		i++;
	}
	return 0;
}

output:
[2021ict109@fedora ~]$ vi day_2.c
[2021ict109@fedora ~]$ gcc day_2.c -o day_2
[2021ict109@fedora ~]$ ./day_2
12345678910[2021ict109@fedora ~]$

---------------------------------------------------------

07. Fibonanci series up to specific number of terms

code:
#include <stdio.h>
int main(){
	
	int num;
	printf("Enter a number:");
	scanf("%d",&num);
	
	int a=0;
	int b=1;
	int c;
	
	for(int i=0;i<=num;i++){
		printf("%d",a);
		 c=a+b;
		a=b;
		b=c;
		
	}
	
	return 0;
}

output:
[2021ict109@fedora ~]$ ./day_2
Enter a number:10
011235813213455[2021ict109@fedora ~]$

--------------------------------------------------------
08. Calculate a factorial of a given non negative integer


#include <stdio.h>
int main(){
	
	int fact=1;
	int num;
	printf("Enter a number:");
	scanf("%d",&num);
	
	for(i=1;i<=num;i++){
		fact=fact*i;
	}
	
		printf("factorial:%d",fact);

	return 0;
}


output:
[2021ict109@fedora ~]$ ./day_2
Enter a number:5
factorial:120[2021ict109@fedora ~]$

------------------------------------------------------------

09. Accepts 2 string from the user
Concanates the 2 string Display the concanated result

#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];

    printf("Enter the first string: ");
    scanf("%s", str1);

    printf("Enter the second string: ");
    scanf("%s", str2);

    strcat(str1, str2); 

    printf("Concatenated String: %s\n", str1);

    return 0;
}

output:
[2021ict109@fedora ~]$ vi day_2.c
[2021ict109@fedora ~]$ gcc day_2.c -o day_2
[2021ict109@fedora ~]$ ./day_2
Enter the first string: hello
Enter the second string: sam
Concatenated String: hellosam


--------------------------------------------------
10. Take a binary number(as an integer) as input and coverts its decimal equivalent

code:
    #include <stdio.h>

int main() {
    int binary, decimal = 0, base = 1, remainder;

    printf("Enter a binary number: ");
    scanf("%d", &binary);

    while (binary > 0) {
        remainder = binary % 10;
        decimal += remainder * base;
        binary /= 10;
        base *= 2;
    }

    printf("Decimal equivalent: %d\n", decimal);

    return 0;
}

output:
{ ~ }  » vi progran.c                                                                  ~ 1
{ ~ }  » gcc progran.c -o progran                                                        ~
{ ~ }  » ./progran                                                                       ~
Enter a binary number:110
Decimal equvalent:6
{ ~ }  » ./progran                                                                       ~
Enter a binary number:111
Decimal equvalent:7
{ ~ }  » ./progran                                                                       
Enter a binary number:1011011
Decimal equvalent:91
------------------------------------------------------------   

11. Accept an array of integer from the user
 Find and display the maximum and minimum value in the array
 
 #include <stdio.h>
 int main(){
    int n,i;
        printf("Enter a 5 numbers:%d");
        scanf("%d",&n);

    int arr[n];

    for( i=0;i<n;i++){
        scanf("%d",arr[i]);
    }

      int max=arr[0];
    int min=arr[0];
    for(i=0;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
        }

        if(arr[i]<min){
            min=arr[i];
        }
    }
    
    printf("max:%d",max);
    printf("\nmin:%d",min);

    return 0;
 }

 output:
 { ~ }  » ./progran                                                                       ~
Enter a numbers:5
2
4
7
9
1
max:9
min:1     
---------------------------------------------------------
 
 12. create  Pascals Triangle
 no od rows=5;
          1
        1   1
      1   2   1
    1   3   3   1
  1   4   6   4   1

 
  code:
  
  #include <stdio.h>
int main(){
   int row=6 ,coef=1;
   int i,j,space;

   for( i=0;i<row;i++){
           for(space=1;space<=row-i;space++) //making the output look triangular.
                   printf(" ");

           for( j=0;j<=i;j++){   //controlling each value in the row
                   if (j==0 || i==0)  //- Pascal’s Triangle starts with 1.
                           coef=1;
                   else
                           coef=coef*(i-j+1)/j;  //Calculating Pascal's Triangle Values
                   printf("%4d",coef); //- Prints each number with 4 spaces for proper alignment.
           }
           printf("\n"); //Moves to the next row after printing all values in the current row
   }

 return 0;
}

  output:
  { ~ }  » vi progran.c                                                                  ~ 1
{ ~ }  » gcc progran.c -o progran                                                        ~
{ ~ }  » ./progran                                                                       ~
         1
        1   1
       1   2   1
      1   3   3   1
     1   4   6   4   1
    1   5  10  10   5   1
                              