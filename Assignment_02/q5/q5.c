/*
    QUESTION 5
    UNIVERSITY LIBRARY MANAGEMENT SYSTEM

    This program manages:
    1. Member registration
    2. Available books
    3. Borrowing books
    4. Returning books
    5. Late return fines
    6. Membership fine waiver
    7. Member record
    8. Exit

    User-defined functions:
    displayMenu()
    registerMember()
    displayBooks()
    borrowBook()
    returnBook()
    displayMemberRecord()
*/


#include <stdio.h>    // printf(), scanf(), getchar()
#include <string.h>   // strlen(), strcmp(), strcpy(), fgets()


// ==================================================
// CONSTANTS
// ==================================================

#define MAX_BOOKS 4

#define MAX_BORROWED 3

#define NAME_SIZE 100

#define TITLE_SIZE 50


// ==================================================
// FUNCTION 1: displayMenu()
// ==================================================

void displayMenu()
{
    // Display all menu options

    printf("\n========================================\n");

    printf(" UNIVERSITY LIBRARY MANAGEMENT SYSTEM\n");

    printf("========================================\n");

    printf("1. Register Member\n");

    printf("2. Display Available Books\n");

    printf("3. Borrow a Book\n");

    printf("4. Return a Book\n");

    printf("5. Display Member Record\n");

    printf("6. Exit\n");

    printf("========================================\n");

    printf("Enter your choice: ");
}


// ==================================================
// FUNCTION 2: registerMember()
// ==================================================

void registerMember(char name[],
                    int *studentID,
                    int *memberType)
{
    int type;

    // ----------------------------------------------
    // INPUT MEMBER NAME
    // ----------------------------------------------

    // Read the complete name including spaces

    printf("\nEnter member name: ");

    getchar();  // Remove leftover newline from previous input

    fgets(name, NAME_SIZE, stdin);

    // Remove newline character from the name

    name[strcspn(name, "\n")] = '\0';


    // ----------------------------------------------
    // INPUT STUDENT ID
    // ----------------------------------------------

    printf("Enter student ID: ");

    scanf("%d", studentID);


    // ----------------------------------------------
    // INPUT MEMBERSHIP TYPE
    // ----------------------------------------------

    printf("\nMembership Type:\n");

    printf("1. Student\n");

    printf("2. Faculty\n");

    printf("Enter membership type: ");

    scanf("%d", &type);


    // Validate membership type

    while (type != 1 && type != 2)
    {
        printf("Invalid membership type!\n");

        printf("Enter 1 for Student or 2 for Faculty: ");

        scanf("%d", &type);
    }


    // Store membership type through pointer

    *memberType = type;


    // ----------------------------------------------
    // DISPLAY REGISTRATION CONFIRMATION
    // ----------------------------------------------

    printf("\nMember Registered Successfully!\n");

    printf("Name: %s\n", name);

    printf("Student ID: %d\n", *studentID);

    if (*memberType == 1)
    {
        printf("Membership Type: Student\n");

        printf("Permitted Days: 14\n");
    }
    else
    {
        printf("Membership Type: Faculty\n");

        printf("Permitted Days: 30\n");
    }
}


// ==================================================
// FUNCTION 3: displayBooks()
// ==================================================

void displayBooks(int bookIDs[],
                  char bookTitles[][TITLE_SIZE],
                  int availableCopies[],
                  int totalBooks)
{
    int i;

    // Display table heading

    printf("\n============================================\n");

    printf("             AVAILABLE BOOKS\n");

    printf("============================================\n");

    printf("%-10s %-25s %-10s\n",
           "Book ID", "Title", "Copies");

    printf("--------------------------------------------\n");


    // Display each book

    for (i = 0; i < totalBooks; i++)
    {
        printf("%-10d %-25s %-10d\n",
               bookIDs[i],
               bookTitles[i],
               availableCopies[i]);
    }

    printf("============================================\n");
}


// ==================================================
// FUNCTION 4: borrowBook()
// ==================================================

void borrowBook(int bookIDs[],
                char bookTitles[][TITLE_SIZE],
                int availableCopies[],
                int totalBooks,
                int borrowedBookIDs[],
                int *borrowedCount,
                int memberType)
{
    int bookID;

    int days;

    int i;

    int bookIndex = -1;


    // ----------------------------------------------
    // INPUT BOOK ID
    // ----------------------------------------------

    printf("\nEnter Book ID to borrow: ");

    scanf("%d", &bookID);


    // ----------------------------------------------
    // INPUT INTENDED BORROWING DAYS
    // ----------------------------------------------

    printf("Enter number of days you intend to keep the book: ");

    scanf("%d", &days);


    // Validate positive days

    while (days <= 0)
    {
        printf("Days must be positive!\n");

        printf("Enter number of days again: ");

        scanf("%d", &days);
    }


    // ----------------------------------------------
    // SEARCH FOR BOOK ID
    // ----------------------------------------------

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == bookID)
        {
            bookIndex = i;

            break;
        }
    }


    // ----------------------------------------------
    // CHECK INVALID BOOK ID
    // ----------------------------------------------

    if (bookIndex == -1)
    {
        printf("\nInvalid Book ID!\n");

        return;
    }


    // ----------------------------------------------
    // CHECK BOOK AVAILABILITY
    // ----------------------------------------------

    if (availableCopies[bookIndex] <= 0)
    {
        printf("\nNo copies of this book are available!\n");

        return;
    }


    // ----------------------------------------------
    // CHECK BORROWING LIMIT
    // ----------------------------------------------

    if (*borrowedCount >= MAX_BORROWED)
    {
        printf("\nBorrowing limit reached!\n");

        printf("A member can borrow maximum 3 books.\n");

        return;
    }


    // ----------------------------------------------
    // RECORD SUCCESSFUL BORROWING
    // ----------------------------------------------

    borrowedBookIDs[*borrowedCount] = bookID;

    // Increase borrowing count

    (*borrowedCount)++;


    // Decrease available copies

    availableCopies[bookIndex]--;


    // ----------------------------------------------
    // DISPLAY SUCCESS MESSAGE
    // ----------------------------------------------

    printf("\nBook Borrowed Successfully!\n");

    printf("Book ID: %d\n", bookID);

    printf("Book Title: %s\n", bookTitles[bookIndex]);

    printf("Intended Days: %d\n", days);

    if (memberType == 1)
    {
        printf("Student permitted period: 14 days\n");
    }
    else
    {
        printf("Faculty permitted period: 30 days\n");
    }
}


// ==================================================
// FUNCTION 5: returnBook()
// ==================================================

float returnBook(int bookIDs[],
                 int availableCopies[],
                 int totalBooks,
                 int borrowedBookIDs[],
                 int *borrowedCount,
                 int memberType,
                 float *totalFine)
{
    int bookID;

    int actualDays;

    int permittedDays;

    int lateDays;

    int i;

    int bookIndex = -1;

    int borrowedIndex = -1;

    float fine = 0.0;

    float finePayable = 0.0;

    char membershipCode[20];


    // ----------------------------------------------
    // INPUT BOOK ID
    // ----------------------------------------------

    printf("\nEnter Book ID to return: ");

    scanf("%d", &bookID);


    // ----------------------------------------------
    // INPUT ACTUAL DAYS
    // ----------------------------------------------

    printf("Enter actual number of days book was kept: ");

    scanf("%d", &actualDays);


    // Validate positive actual days

    while (actualDays <= 0)
    {
        printf("Days must be positive!\n");

        printf("Enter actual days again: ");

        scanf("%d", &actualDays);
    }


    // ----------------------------------------------
    // SEARCH BOOK IN INVENTORY
    // ----------------------------------------------

    for (i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == bookID)
        {
            bookIndex = i;

            break;
        }
    }


    // ----------------------------------------------
    // SEARCH BOOK IN BORROWING RECORD
    // ----------------------------------------------

    for (i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == bookID)
        {
            borrowedIndex = i;

            break;
        }
    }


    // ----------------------------------------------
    // VALIDATE BORROWED BOOK
    // ----------------------------------------------

    if (bookIndex == -1 || borrowedIndex == -1)
    {
        printf("\nThis book was not borrowed by the member!\n");

        return 0.0;
    }


    // ----------------------------------------------
    // DETERMINE PERMITTED BORROWING PERIOD
    // ----------------------------------------------

    if (memberType == 1)
    {
        // Student can keep books for 14 days

        permittedDays = 14;
    }
    else
    {
        // Faculty can keep books for 30 days

        permittedDays = 30;
    }


    // ----------------------------------------------
    // CALCULATE EXTRA DAYS
    // ----------------------------------------------

    if (actualDays > permittedDays)
    {
        lateDays = actualDays - permittedDays;
    }
    else
    {
        lateDays = 0;
    }


    // ----------------------------------------------
    // CALCULATE LATE FINE
    // ----------------------------------------------

    if (memberType == 1)
    {
        // Student fine = Rs. 20 per extra day

        fine = lateDays * 20.0;
    }
    else
    {
        // Faculty fine = Rs. 10 per extra day

        fine = lateDays * 10.0;
    }


    // ----------------------------------------------
    // DISPLAY FINE BEFORE WAIVER
    // ----------------------------------------------

    printf("\nPermitted Days: %d\n", permittedDays);

    printf("Actual Days: %d\n", actualDays);

    printf("Extra Days: %d\n", lateDays);

    printf("Fine Before Waiver: Rs. %.2f\n", fine);


    // ----------------------------------------------
    // INPUT MEMBERSHIP CODE
    // ----------------------------------------------

    if (fine > 0)
    {
        printf("\nEnter membership code for 50%% waiver: ");

        scanf("%19s", membershipCode);


        // ------------------------------------------
        // CHECK MEMBERSHIP CODE
        // ------------------------------------------

        if (strcmp(membershipCode, "LIB2026") == 0)
        {
            // Apply 50% waiver

            finePayable = fine * 0.50;

            printf("Correct Code! 50%% waiver applied.\n");
        }
        else
        {
            // No waiver applied

            finePayable = fine;

            printf("Incorrect Code! No waiver applied.\n");
        }
    }
    else
    {
        // No late fine

        finePayable = 0.0;
    }


    // ----------------------------------------------
    // UPDATE CUMULATIVE FINE
    // ----------------------------------------------

    // Store fine before waiver

    *totalFine = *totalFine + fine;


    // ----------------------------------------------
    // UPDATE AVAILABLE COPIES
    // ----------------------------------------------

    availableCopies[bookIndex]++;


    // ----------------------------------------------
    // REMOVE BOOK FROM BORROWING LIST
    // ----------------------------------------------

    // Shift remaining elements one position to the left

    for (i = borrowedIndex; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }


    // Decrease borrowing count

    (*borrowedCount)--;


    // ----------------------------------------------
    // DISPLAY RETURN CONFIRMATION
    // ----------------------------------------------

    printf("\nBook Returned Successfully!\n");

    printf("Fine Payable After Waiver: Rs. %.2f\n",
           finePayable);


    // Return current return's payable fine

    return finePayable;
}


// ==================================================
// FUNCTION 6: displayMemberRecord()
// ==================================================

void displayMemberRecord(char name[],
                        int studentID,
                        int memberType,
                        int borrowedBookIDs[],
                        int borrowedCount,
                        float totalFine,
                        float fineAfterWaiver)
{
    int i;


    // ----------------------------------------------
    // DISPLAY MEMBER DETAILS
    // ----------------------------------------------

    printf("\n============================================\n");

    printf("             MEMBER RECORD\n");

    printf("============================================\n");


    printf("Member Name: %s\n", name);

    printf("Student ID: %d\n", studentID);


    // Display membership type

    if (memberType == 1)
    {
        printf("Membership Type: Student\n");
    }
    else if (memberType == 2)
    {
        printf("Membership Type: Faculty\n");
    }
    else
    {
        printf("Membership Type: Not Registered\n");
    }


    // ----------------------------------------------
    // DISPLAY CURRENTLY BORROWED BOOKS
    // ----------------------------------------------

    printf("\nCurrently Borrowed Books:\n");


    if (borrowedCount == 0)
    {
        printf("No books are currently borrowed.\n");
    }
    else
    {
        for (i = 0; i < borrowedCount; i++)
        {
            printf("Book ID: %d\n", borrowedBookIDs[i]);
        }
    }


    // ----------------------------------------------
    // DISPLAY FINE RECORD
    // ----------------------------------------------

    printf("\nTotal Fine Before Waiver: Rs. %.2f\n",
           totalFine);

    printf("Final Fine Payable After Waiver: Rs. %.2f\n",
           fineAfterWaiver);


    printf("============================================\n");
}


// ==================================================
// MAIN FUNCTION
// ==================================================

int main()
{
    // ----------------------------------------------
    // INITIALIZE BOOK INVENTORY
    // ----------------------------------------------

    int bookIDs[MAX_BOOKS] =
    {
        101, 102, 103, 104
    };


    char bookTitles[MAX_BOOKS][TITLE_SIZE] =
    {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };


    int availableCopies[MAX_BOOKS] =
    {
        5, 3, 0, 4
    };


    // ----------------------------------------------
    // MEMBER RECORD VARIABLES
    // ----------------------------------------------

    char name[NAME_SIZE] = "";

    int studentID = 0;

    int memberType = 0;


    // ----------------------------------------------
    // BORROWING RECORD VARIABLES
    // ----------------------------------------------

    int borrowedBookIDs[MAX_BORROWED];

    int borrowedCount = 0;


    // ----------------------------------------------
    // FINE VARIABLES
    // ----------------------------------------------

    float totalFine = 0.0;

    float fineAfterWaiver = 0.0;

    float currentFinePayable;


    // ----------------------------------------------
    // MENU VARIABLE
    // ----------------------------------------------

    int choice;


    // ----------------------------------------------
    // MENU-DRIVEN PROGRAM
    // ----------------------------------------------

    do
    {
        // Display menu

        displayMenu();


        // Input menu choice

        scanf("%d", &choice);


        // ------------------------------------------
        // SWITCH STATEMENT
        // ------------------------------------------

        switch (choice)
        {
            case 1:

                // Register member

                registerMember(name,
                              &studentID,
                              &memberType);

                break;


            case 2:

                // Display all books

                displayBooks(bookIDs,
                             bookTitles,
                             availableCopies,
                             MAX_BOOKS);

                break;


            case 3:

                // Borrow a book

                if (memberType == 0)
                {
                    printf("\nPlease register a member first!\n");
                }
                else
                {
                    borrowBook(bookIDs,
                               bookTitles,
                               availableCopies,
                               MAX_BOOKS,
                               borrowedBookIDs,
                               &borrowedCount,
                               memberType);
                }

                break;


            case 4:

                // Return a book

                if (memberType == 0)
                {
                    printf("\nPlease register a member first!\n");
                }
                else
                {
                    currentFinePayable =
                        returnBook(bookIDs,
                                   availableCopies,
                                   MAX_BOOKS,
                                   borrowedBookIDs,
                                   &borrowedCount,
                                   memberType,
                                   &totalFine);


                    // Update cumulative fine payable after waivers

                    fineAfterWaiver =
                        fineAfterWaiver + currentFinePayable;
                }

                break;


            case 5:

                // Display member record

                if (memberType == 0)
                {
                    printf("\nNo member registered yet!\n");
                }
                else
                {
                    displayMemberRecord(name,
                                       studentID,
                                       memberType,
                                       borrowedBookIDs,
                                       borrowedCount,
                                       totalFine,
                                       fineAfterWaiver);
                }

                break;


            case 6:

                // Exit program

                printf("\nThank you for using the Library System!\n");

                break;


            default:

                // Invalid menu choice

                printf("\nInvalid menu choice!\n");

                printf("Please select a number between 1 and 6.\n");
        }

    }
    while (choice != 6);


    // ----------------------------------------------
    // END PROGRAM
    // ----------------------------------------------

    return 0;
}