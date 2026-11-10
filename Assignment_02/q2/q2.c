/*
    Program Name: Amicable Pairs
    Course: Programming Fundamentals
    Question: 2 - Part A

    Description:
    This program finds all amicable pairs
    up to a user-entered limit n.

    An amicable pair (a, b) satisfies:
        Sum of proper divisors of a = b
        Sum of proper divisors of b = a

    Each pair is displayed only once.
    The smaller number is displayed first.

    A user-defined function is used to calculate
    the sum of proper divisors.
*/

#include <stdio.h>  // Provides printf() and scanf()

// ------------------------------------------------
// FUNCTION: sumProperDivisors()
// PURPOSE: Calculate the sum of proper divisors
//          of a given positive integer.
// ------------------------------------------------

int sumProperDivisors(int num)
{
    int divisor;    // Variable to test possible divisors
    int sum = 0;    // Stores the running sum

    // Proper divisors cannot be greater than num / 2.
    // Therefore, we only check from 1 to num / 2.

    for (divisor = 1; divisor <= num / 2; divisor++)
    {
        // Check whether divisor divides num completely

        if (num % divisor == 0)
        {
            // Add the divisor to the running sum

            sum = sum + divisor;
        }
    }

    // Return the calculated sum to the calling function

    return sum;
}

// ------------------------------------------------
// MAIN FUNCTION
// ------------------------------------------------

int main()
{
    int n;          // Upper limit entered by the user
    int i;          // First number of a possible pair
    int j;          // Second number of a possible pair
    int sum1;       // Sum of proper divisors of i
    int sum2;       // Sum of proper divisors of j
    int pairCount = 0;  // Counts amicable pairs

    // --------------------------------------------
    // STEP 1: INPUT THE UPPER LIMIT
    // --------------------------------------------

    printf("Enter the upper limit n: ");
    scanf("%d", &n);

    // Validate the input

    while (n <= 0)
    {
        printf("Enter a positive integer: ");
        scanf("%d", &n);
    }

    // --------------------------------------------
    // STEP 2: DISPLAY THE HEADING
    // --------------------------------------------

    printf("\nAmicable pairs up to %d:\n", n);

    // --------------------------------------------
    // STEP 3: SEARCH FOR AMICABLE PAIRS
    // --------------------------------------------

    // Check each number from 2 to n

    for (i = 2; i <= n; i++)
    {
        // Calculate the sum of proper divisors of i

        sum1 = sumProperDivisors(i);

        // The sum of proper divisors of i
        // becomes the possible second number j

        j = sum1;

        // Ensure that:
        // 1. j is greater than i.
        // 2. j is within the upper limit n.

        if (j > i && j <= n)
        {
            // Calculate the sum of proper divisors of j

            sum2 = sumProperDivisors(j);

            // Check whether the sum of proper divisors
            // of j equals the original number i

            if (sum2 == i)
            {
                // Display the amicable pair

                printf("(%d, %d)\n", i, j);

                // Increase the number of pairs found

                pairCount++;
            }
        }
    }

    // --------------------------------------------
    // STEP 4: DISPLAY THE TOTAL NUMBER OF PAIRS
    // --------------------------------------------

    if (pairCount == 0)
    {
        printf("No amicable pairs found.\n");
    }
    else
    {
        printf("Total pairs: %d\n", pairCount);
    }

    // --------------------------------------------
    // END OF PROGRAM
    // --------------------------------------------

    return 0;
}