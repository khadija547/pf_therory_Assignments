/*
    Program Name: Cinema Hall Seat Booking Management System
    Course: Programming Fundamentals (CS-1002)
    Question: 1

    Description:
    This program manages cinema hall seats.
    It displays available and booked seats,
    finds consecutive available seats for a group,
    and books seats according to the middle-row priority.

    Note:
    The complete program is implemented inside main().
    No user-defined functions are used.
*/

#include <stdio.h>      // Header file for printf() and scanf()

int main()
{
    // -----------------------------------------
    // STEP 1: DECLARE BASIC VARIABLES
    // -----------------------------------------

    int rows;
    int seatsPerRow;

    // Input number of rows
    printf("Enter number of rows: ");
    scanf("%d", &rows);

    // Validate rows
    while (rows <= 0)
    {
        printf("Rows must be greater than zero. Enter again: ");
        scanf("%d", &rows);
    }

    // Input number of seats in each row
    printf("Enter number of seats per row: ");
    scanf("%d", &seatsPerRow);

    // Validate seats per row
    while (seatsPerRow <= 0)
    {
        printf("Seats per row must be greater than zero. Enter again: ");
        scanf("%d", &seatsPerRow);
    }

    // -----------------------------------------
    // STEP 2: CREATE TWO-DIMENSIONAL ARRAY
    // -----------------------------------------

    // This array stores the status of every seat.
    // 0 = Available
    // 1 = Booked

    int seats[rows][seatsPerRow];

    // Declare loop variables
    int i, j;

    // -----------------------------------------
    // STEP 3: INPUT CURRENT SEATING STATUS
    // -----------------------------------------

    printf("\nEnter seating status:\n");
    printf("0 = Available, 1 = Booked\n\n");

    // Outer loop controls rows
    for (i = 0; i < rows; i++)
    {
        // Inner loop controls seats in each row
        for (j = 0; j < seatsPerRow; j++)
        {
            printf("Enter status of Row %d, Seat %d: ", i, j);

            scanf("%d", &seats[i][j]);

            // Only 0 and 1 are valid values
            while (seats[i][j] != 0 && seats[i][j] != 1)
            {
                printf("Invalid status! Enter 0 or 1: ");
                scanf("%d", &seats[i][j]);
            }
        }
    }

    // -----------------------------------------
    // STEP 4: DISPLAY SEATING ARRANGEMENT
    // -----------------------------------------

    printf("\n========== CINEMA SEATING PLAN ==========\n");

    // Display seat numbers as column headings
    printf("Row\t");

    for (j = 0; j < seatsPerRow; j++)
    {
        printf("%d\t", j);
    }

    printf("\n");

    // Display each row
    for (i = 0; i < rows; i++)
    {
        printf("%d\t", i);

        for (j = 0; j < seatsPerRow; j++)
        {
            if (seats[i][j] == 0)
            {
                printf("_\t");   // Available seat
            }
            else
            {
                printf("X\t");   // Booked seat
            }
        }

        printf("\n");
    }

    // -----------------------------------------
    // STEP 5: COUNT AVAILABLE SEATS
    // -----------------------------------------

    int totalAvailable = 0;
    int rowAvailable;

    printf("\n========== SEAT AVAILABILITY REPORT ==========\n");

    for (i = 0; i < rows; i++)
    {
        rowAvailable = 0;

        for (j = 0; j < seatsPerRow; j++)
        {
            if (seats[i][j] == 0)
            {
                rowAvailable++;
            }
        }

        // Add current row's available seats to total
        totalAvailable = totalAvailable + rowAvailable;

        printf("Available seats in Row %d: %d\n", i, rowAvailable);
    }

    printf("Total available seats in hall: %d\n", totalAvailable);

    // -----------------------------------------
    // STEP 6: INPUT AND VALIDATE GROUP SIZE
    // -----------------------------------------

    int k;

    printf("\nEnter number of customers who want to sit together: ");
    scanf("%d", &k);

    // Group size must be greater than zero
    // and must not exceed seats in one row

    while (k <= 0 || k > seatsPerRow)
    {
        printf("Invalid group size! Enter a number between 1 and %d: ",
               seatsPerRow);

        scanf("%d", &k);
    }

    // -----------------------------------------
    // STEP 7: PREPARE SEAT SEARCHING
    // -----------------------------------------

    int middleRow = rows / 2;

    int distance;
    int side;
    int candidateRow;

    int consecutive;
    int startSeat = -1;
    int allocatedRow = -1;

    int found = 0;

    // -----------------------------------------
    // STEP 8: SEARCH ROWS FROM THE MIDDLE
    // -----------------------------------------

    // Search rows in increasing distance from middle.
    // Lower row number is checked before higher row number.

    for (distance = 0; distance < rows && found == 0; distance++)
    {
        // side = 0 means lower row
        // side = 1 means higher row

        for (side = 0; side < 2 && found == 0; side++)
        {
            // Middle row should only be checked once
            if (distance == 0 && side == 1)
            {
                continue;
            }

            // Calculate the row to search
            if (side == 0)
            {
                candidateRow = middleRow - distance;
            }
            else
            {
                candidateRow = middleRow + distance;
            }

            // Ignore rows outside the array
            if (candidateRow < 0 || candidateRow >= rows)
            {
                continue;
            }

            // ---------------------------------
            // STEP 9: SEARCH CONSECUTIVE SEATS
            // ---------------------------------

            consecutive = 0;

            // Search seats from left to right
            for (j = 0; j < seatsPerRow; j++)
            {
                if (seats[candidateRow][j] == 0)
                {
                    // Increase count of consecutive free seats
                    consecutive++;

                    // Check if required group size is found
                    if (consecutive == k)
                    {
                        // Calculate first seat of the block
                        startSeat = j - k + 1;

                        // Save selected row
                        allocatedRow = candidateRow;

                        // Mark that suitable seats are found
                        found = 1;

                        // Stop searching this row
                        break;
                    }
                }
                else
                {
                    // A booked seat breaks the consecutive block
                    consecutive = 0;
                }
            }
        }
    }

    // -----------------------------------------
    // STEP 10: CONFIRM OR REJECT BOOKING
    // -----------------------------------------

    if (found == 1)
    {
        printf("\n========== BOOKING SUCCESSFUL ==========\n");

        printf("Allocated Row: %d\n", allocatedRow);

        printf("Allocated Seat Numbers: ");

        // Display allocated seats and update their status
        for (j = startSeat; j < startSeat + k; j++)
        {
            printf("%d ", j);

            // Change available seat (0) into booked seat (1)
            seats[allocatedRow][j] = 1;
        }

        printf("\n");

        // ---------------------------------
        // STEP 11: DISPLAY UPDATED PLAN
        // ---------------------------------

        printf("\n========== UPDATED SEATING PLAN ==========\n");

        printf("Row\t");

        for (j = 0; j < seatsPerRow; j++)
        {
            printf("%d\t", j);
        }

        printf("\n");

        for (i = 0; i < rows; i++)
        {
            printf("%d\t", i);

            for (j = 0; j < seatsPerRow; j++)
            {
                if (seats[i][j] == 0)
                {
                    printf("_\t");
                }
                else
                {
                    printf("X\t");
                }
            }

            printf("\n");
        }

        // ---------------------------------
        // STEP 12: COUNT REMAINING SEATS
        // ---------------------------------

        totalAvailable = 0;

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < seatsPerRow; j++)
            {
                if (seats[i][j] == 0)
                {
                    totalAvailable++;
                }
            }
        }

        printf("\nRemaining available seats: %d\n", totalAvailable);
    }
    else
    {
        // No suitable consecutive block was found
        printf("\nBooking unsuccessful!\n");
        printf("No row contains %d consecutive available seats.\n", k);

        printf("Seating plan remains unchanged.\n");

        // The original totalAvailable is still correct
        printf("Remaining available seats: %d\n", totalAvailable);
    }

    // -----------------------------------------
    // END OF PROGRAM
    // -----------------------------------------

    return 0;
}