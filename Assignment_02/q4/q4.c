/*
    Question 4:
    Bakery Festival Sales Management System

    This program:
    1. Inputs and validates festival duration.
    2. Inputs daily customer orders.
    3. Calculates daily total sales.
    4. Calculates average order amount.
    5. Finds the highest order amount for each day.
    6. Calculates total festival sales.
    7. Finds the day with the highest total sales.
    8. Displays a daily sales bar chart.

    Required user-defined functions:
    - getValidDays()
    - calculateDailySales()
    - findHighestSalesDay()
    - displayBarChart()
*/

#include <stdio.h>  // Provides printf() and scanf()


// ==================================================
// FUNCTION 1: getValidDays()
// ==================================================

int getValidDays()
{
    int numberOfDays;  // Stores festival duration

    // Ask the user to enter the number of days

    printf("Enter number of festival days (1-7): ");
    scanf("%d", &numberOfDays);

    // Validate festival duration

    while (numberOfDays < 1 || numberOfDays > 7)
    {
        printf("Invalid input! Enter days between 1 and 7: ");
        scanf("%d", &numberOfDays);
    }

    // Return the valid number of days

    return numberOfDays;
}


// ==================================================
// FUNCTION 2: calculateDailySales()
// ==================================================

float calculateDailySales(int dayNumber)
{
    int orderCount;        // Number of orders for current day
    int order;             // Loop counter
    float amount;          // Current order amount
    float totalSales = 0;  // Total sales of current day
    float averageOrder;    // Average order amount
    float highestOrder = 0; // Highest order amount

    // ----------------------------------------------
    // INPUT NUMBER OF ORDERS
    // ----------------------------------------------

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orderCount);

    // Number of orders must be at least one

    while (orderCount < 1)
    {
        printf("Invalid! Enter at least one order: ");
        scanf("%d", &orderCount);
    }

    // ----------------------------------------------
    // INPUT ORDER AMOUNTS
    // ----------------------------------------------

    for (order = 1; order <= orderCount; order++)
    {
        // Ask for the current order amount

        printf("Enter amount for order %d: ", order);
        scanf("%f", &amount);

        // Validate the amount.
        // Amount must be greater than zero.

        while (amount <= 0)
        {
            printf("Invalid amount! Enter a value greater than 0: ");
            scanf("%f", &amount);
        }

        // Add the valid amount to total sales

        totalSales = totalSales + amount;

        // Check whether this is the highest order amount

        if (amount > highestOrder)
        {
            highestOrder = amount;
        }
    }

    // ----------------------------------------------
    // CALCULATE AVERAGE ORDER AMOUNT
    // ----------------------------------------------

    averageOrder = totalSales / orderCount;

    // ----------------------------------------------
    // DISPLAY DAILY SALES SUMMARY
    // ----------------------------------------------

    printf("\n----- DAY %d SALES SUMMARY -----\n", dayNumber);

    printf("Total sales: Rs. %.2f\n", totalSales);

    printf("Average order: Rs. %.2f\n", averageOrder);

    printf("Highest order: Rs. %.2f\n", highestOrder);

    // Return the total sales of this day

    return totalSales;
}


// ==================================================
// FUNCTION 3: findHighestSalesDay()
// ==================================================

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i;               // Loop counter
    int highestDay = 1;  // Day number with highest sales

    // Assume the first day has the highest sales

    float highestSales = dailySales[0];

    // Compare remaining days with the first day

    for (i = 1; i < numberOfDays; i++)
    {
        // Update only if sales are strictly greater.
        // This preserves the earliest day in case of a tie.

        if (dailySales[i] > highestSales)
        {
            highestSales = dailySales[i];

            // Array index starts at 0,
            // but day numbering starts at 1.

            highestDay = i + 1;
        }
    }

    // Return the day number with highest sales

    return highestDay;
}


// ==================================================
// FUNCTION 4: displayBarChart()
// ==================================================

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i;       // Loop counter for days
    int stars;   // Number of asterisks
    int j;       // Loop counter for asterisks

    // Display heading

    printf("\n===== DAILY SALES BAR CHART =====\n");

    // Process every festival day

    for (i = 0; i < numberOfDays; i++)
    {
        // One star represents every complete Rs. 100.
        // Remaining amount below Rs. 100 is ignored.

        stars = (int)(dailySales[i] / 100);

        // Display the day number

        printf("Day %d: ", i + 1);

        // Print the required number of asterisks

        for (j = 1; j <= stars; j++)
        {
            printf("*");
        }

        // Display the daily sales amount

        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}


// ==================================================
// MAIN FUNCTION
// ==================================================

int main()
{
    int numberOfDays;  // Festival duration
    int dayNumber;     // Current festival day
    int highestDay;    // Day with highest daily sales
    int i;             // Loop counter

    float dailySales[7];  // Array to store daily sales
    float festivalTotal = 0;  // Total festival sales

    // ----------------------------------------------
    // STEP 1: INPUT FESTIVAL DURATION
    // ----------------------------------------------

    numberOfDays = getValidDays();

    // ----------------------------------------------
    // STEP 2: PROCESS DAILY SALES
    // ----------------------------------------------

    for (dayNumber = 1; dayNumber <= numberOfDays; dayNumber++)
    {
        // Calculate sales for the current day.
        // Store returned total in the array.

        dailySales[dayNumber - 1] =
            calculateDailySales(dayNumber);
    }

    // ----------------------------------------------
    // STEP 3: CALCULATE TOTAL FESTIVAL SALES
    // ----------------------------------------------

    for (i = 0; i < numberOfDays; i++)
    {
        festivalTotal = festivalTotal + dailySales[i];
    }

    // Display total festival sales

    printf("\n===== FESTIVAL SUMMARY =====\n");

    printf("Total festival sales: Rs. %.2f\n", festivalTotal);

    // ----------------------------------------------
    // STEP 4: FIND HIGHEST SALES DAY
    // ----------------------------------------------

    highestDay = findHighestSalesDay(dailySales, numberOfDays);

    // Display highest sales day and amount

    printf("Day with highest sales: Day %d\n", highestDay);

    printf("Highest daily sales: Rs. %.2f\n",
           dailySales[highestDay - 1]);

    // ----------------------------------------------
    // STEP 5: DISPLAY DAILY SALES BAR CHART
    // ----------------------------------------------

    displayBarChart(dailySales, numberOfDays);

    // ----------------------------------------------
    // END PROGRAM
    // ----------------------------------------------

    return 0;
}