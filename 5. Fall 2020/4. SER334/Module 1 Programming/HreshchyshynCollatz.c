/**
* Uses a function that performs Collatz Conjecture iterations.
* Calculates the number of iterations given a user input.
* Completion time: 3 hours across all 3 programs
*
* @author Jacob Hreshchyshyn, Professor Acuna
* @version 8/31/2020 at 8:30 AM
*/

////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int termination(int n);

int main(void)
{
    int input;
    int iteration;
    printf("Input a number to see how many Collatz iterations occur.\n");
    scanf("%d", &input);
    iteration = termination(input);
    printf("%d iterations occurred.\n", iteration);
    return 0;
}

int termination(int n)
{
    int num = n;
    int iteration = 0;
    while(num != 1)
    {
        if(num % 2 == 0)
        {
            num = num/2;
        }
        else
        {
            num = (3 * num) + 1;
        }
        iteration++;
    }
    return iteration;
}


