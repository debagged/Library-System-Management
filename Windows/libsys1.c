#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // used for usleep function
#include <time.h>

//BOLD WHITE {
#define BOLD "\033[1m" 
#define RESET "\033[0m"

//BOLD GREEN {
#define GREEN "\x1b[1;32m"
#define FORMAT "\x1b[0m"
// }

#define MAX_LINES 1500
#define MAX_LENGTH 400


//Void Funtion Declarations {
void loadingAnimation();
void addBooks();
void viewBooks();
void borrowBooks();
void borrowedList();
void editFile(const char *filename);
void editBooks(const char *filename);
void editBorrowed(const char *filename);

//typedef struct 
struct Books {
    int ID;
    char bookName[50];
    char authorName[50];
    char date[11];
} B;

struct Students{
    long int ID;
    int bookID;
    char studentName[50];
    char program[50];
    char bookName[50];
    char authorName[50];
    char status[10];
} S;



FILE *fp, *file; //Allowing for file creation 
int choice;

int main() 
{
    int choices;

    do {
        printf("\e[1;1H\e[2J"); // clear screen
    
        printf("\n\n");
        printf(BOLD "\t   |[=======================================================]|\n" RESET);
        printf(BOLD "\t   ||              "GREEN"WELCOME TO BOOKLY RECORDS"FORMAT"                 ||\n" RESET);
        printf(BOLD "\t   |[=======================================================]|\n\n" RESET);


        printf(BOLD"\t      MAIN MENU \n" RESET);
        printf("\t      |[===============================================]|\n");
        printf("\t      ||  %sOPTION%s        |      %sDESCRIPTION%s             ||\n",GREEN,RESET,GREEN,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s1%s           |      %sADD BOOKS%s               ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s2%s           |      %sVIEW BOOKS LIST%s         ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s3%s           |      %sBORROW BOOKS%s            ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s4%s           |      %sBORROWED BOOKS LIST%s     ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s5%s           |      %sEDIT LIST%s               ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s0%s           |      %sEXIT PROGRAM%s            ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      |[===============================================]|\n");
    

        printf("\n\n\n\t\tEnter your choice here >> ");
        scanf(" %d", &choices);
    
        getchar();// Consume the newline character in the buffer
    
        switch (choices) {
            case 0:
                printf("\e[1;1H\e[2J"); // clear screen
                loadingAnimation();
    
                printf("\e[1;1H\e[2J"); // clear screen
                printf("\n");
                printf(BOLD "\t    ================================================\n" RESET);
                printf(BOLD "\t    ||    %sTHANK YOU FOR USING BOOKLY RECORDS!%s     ||\n" RESET,GREEN, RESET);
                printf(BOLD "\t    ================================================\n\n" RESET);                
                break;
    
            case 1:
                addBooks();
                break;
    
            case 2:
                viewBooks();
                break;
    
            case 3:
                borrowBooks();
                break;
    
            case 4:
                borrowedList();
                break;

            case 5: 
                 //printf("Enter the File Name to Edit:");
                int editNum;
                    printf("Select a File to Edit \n [1. books.txt] \n [2.borrow.txt]\n");
                    scanf("%d", &editNum);
                
                    getchar();

                if (editNum == 1) {
                    editFile("books.txt");
                }
                else{
                    editFile("borrow.txt");
                }

                break;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }  
    
        if (choices != 0) {
            printf("\n\n\tPress Enter to Continue...");
            getchar(); // Wait for the user to press Enter
        }
        
    } while(choices != 0);
    
    return 0;
}




// VOID FUNCTIONS {

void loadingAnimation() {
    printf(" "); // Use puts for simple string output
    printf(BOLD "\n\t  =====================================\n" RESET);
    printf("\t\tExiting the Program... ");
        for (int i = 0; i < 30; ++i) {
            printf("\b|");
            fflush(stdout);
            usleep(100000);

            printf("\b/");
            fflush(stdout);
            usleep(100000);

            printf("\b-");
            fflush(stdout);
            usleep(100000);

            printf("\b\\");
            fflush(stdout);
            usleep(100000);
        }
    printf(BOLD "\n\t  =====================================\n" RESET);



}


void addBooks() {
    fp = fopen("books.txt", "a"); // "a" for appending to a file named books

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Check if the file is empty, if yes, write the header
    fseek(fp, 0, SEEK_END); // Move to the end of the file
        if (ftell(fp) == 0) {  // Check the position, if it's 0, the file is empty, then proceeds to printing 
            fprintf(fp, "\t%-15s%-60s%-40s%-15s\n", "Book ID", "Book Name", "Author Name", "Date Added");
        }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file


    printf(GREEN "\n\n\t\t===================[ ADD BOOKS ]===================\n" FORMAT);

    B.ID++;         

    printf(BOLD "\n\t\t  Enter Book Name: " RESET);
    fgets(B.bookName, 50, stdin);
    B.bookName[strcspn(B.bookName, "\n")] = '\0';

    printf(BOLD "\n\t\t  Enter Author Name: " RESET);
    fgets(B.authorName, 50, stdin);
    B.authorName[strcspn(B.authorName, "\n")] = '\0';

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);

    fprintf(fp, "\t%-15d%-60s%-40s%-15s\n", B.ID, B.bookName, B.authorName, B.date);

    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\t\t\t     BOOK ADDED SUCESSFULLY!! \n" FORMAT);
    printf("\t\t   ============================================== \n");

    fclose(fp); // Closes the file
}

void viewBooks() {
    char line[300]; // Assuming a maximum of 300 characters per line

    fp = fopen("books.txt", "r"); // "r" for reading

    if (fp == NULL) 
    {
        printf("\e[1;1H\e[2J"); // clear screen
        printf("\n   ----------------------------------------------------------------------------------------------------------------------------------------------\n\n");    
        printf(BOLD "\tERROR OPENING THE FILE!\n" RESET);
        printf("\n   ----------------------------------------------------------------------------------------------------------------------------------------------\n");
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Check if the file is empty, if yes, print a message
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {               
        printf("   ----------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        printf(BOLD "\n\t\t No books available.\n" RESET);
        printf("\n   ----------------------------------------------------------------------------------------------------------------------------------------------\n");
    } 
    else 
    {
        // Move the file pointer to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        printf(GREEN "\n[VIEW BOOKS LIST]\n" FORMAT);
        // Print a separator line
                 
        printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\n");

        // Read and print each line until the end of the file
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf(BOLD "%s" RESET, line);
        }

        printf("\n ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    }
    fclose(fp); // Close the file
}

void borrowBooks() {
    FILE *fp;

    printf("\e[1;1H\e[2J"); // clear screen

    fp = fopen("borrow.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fseek(fp, 0, SEEK_END); // Move to the end of the file
    if (ftell(fp) == 0) {
        // Check the position, if it's 0, the file is empty
        fprintf(fp, "\t %-20s%-35s%-35s%-10s%-35s%-13s%-15s%-10s\n", "Student ID[06-]", "Student Name", "Program", "Book ID", "Book Name", "Date Lent","Return Date", "Status");
    }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);

    printf(GREEN "\n\n\t\t===========================[ BOOK LENDING ]===========================\n" FORMAT);

    printf("\n\t\t Fatima Student ID (06-): ");
    scanf("%ld", &S.ID);
    getchar();

    printf("\n\t\t Enter Student Name: ");
    fgets(S.studentName, 50, stdin);
    S.studentName[strcspn(S.studentName, "\n")] = '\0';

    printf("\n\t\t Enter Program (e.g.; BS Computer Science): ");
    fgets(S.program, 50, stdin);
    S.program[strcspn(S.program, "\n")] = '\0';

    printf("\e[1;1H\e[2J"); // clear screen
    viewBooks();

    printf("\n\t\t Enter Book ID: ");
    scanf("%d", &S.bookID);
    getchar(); // Consume the newline character

    printf("\n\t\t Enter Book Name: ");
    fgets(S.bookName, 50, stdin);
    S.bookName[strcspn(S.bookName, "\n")] = '\0';

    strcpy(S.status, "Borrowed"); // Use strcpy to assign the string "Borrowed" to S.status
    printf("\n\t\tStatus: %s", S.status);

    // Assuming the return date is one week from the borrow date
    struct tm returnDate;
    returnDate = *now;
    returnDate.tm_mday += 7;
    mktime(&returnDate);
    char returnDateString[11];
    strftime(returnDateString, sizeof(returnDateString), "%m-%d-%Y", &returnDate);

    fprintf(fp, "\t %-20ld%-35s%-35s%-10d%-35s%-13s%-15s%-10s\n", S.ID, S.studentName , S.program, S.bookID, S.bookName, B.date ,returnDateString, S.status);

    sleep(2);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION ADDED SUCESSFULLY!! \n" FORMAT);
    printf("\n\t\t  =============================================== ");


    fclose(fp); // Closes the file
}

void borrowedList(){ 
    char line[300]; // Assuming a maximum of 300 characters per line

    fp = fopen("borrow.txt", "r"); // "r" for reading

    if (fp == NULL) 
    {
        printf("\e[1;1H\e[2J"); // clear screen
        printf("\n\t\tERROR OPENING THE FILE!\n");
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Check if the file is empty, if yes, print a message
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        printf("\n\t\t No data available.\n");
    } 
    else 
    {
        // Move the file pointer to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        printf(GREEN "\n[LENDING INFORMATION]\n" FORMAT);


        // Print a separator line
        printf("   -----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
 
        // Read and print each line until the end of the file
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        }

        printf("\n   -----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    fclose(fp); // Close the file
}

void editFile(const char *filename)
{
    char lines[MAX_LINES][MAX_LENGTH];
    int lineCount = 0;

    FILE *file;
    // Open file for reading
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read file content into memory
    while (fgets(lines[lineCount], MAX_LENGTH, file) != NULL) {
        lineCount++;
    }
    fclose(file);

    // Display file content with line numbers
    printf("\nContents of %s:\n", filename);
    for (int i = 0; i < lineCount; i++) {
        printf("[%d] %s", i, lines[i]);
    }

    // Ask user for line to edit
    printf("\nEnter the line number to edit (0 to cancel): ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    if (choice == 0 || choice > lineCount) {
        printf("Invalid choice or line number.\n");
        return;
    }

    if (filename == "books.txt"){
        editBooks("books.txt");
    }

    if (filename == "borrow.txt") {
        editBorrowed("borrow.txt");
    }
    
    fclose(file);

    printf("File %s updated successfully.\n", filename);
}

void editBooks(const char *filename)
{
    char line[MAX_LINES];
    char lineNumber = 0;
    long position;

    file = fopen(filename, "rw+");

    printf("\n\t\tEnter bookID: ");
    scanf("%d", &B.ID);
    getchar();

    printf(BOLD "\n\t\t  Enter Book Name: " RESET);
    fgets(B.bookName, 50, stdin);
    B.bookName[strcspn(B.bookName, "\n")] = '\0';

    printf(BOLD "\t\t  Enter Author Name: " RESET);
    fgets(B.authorName, 50, stdin);
    B.authorName[strcspn(B.authorName, "\n")] = '\0';

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);

    while (fgets(line, sizeof(line), file)) {
        if (choice == lineNumber) {
            position = ftell(file); // Save the current offset
            // Edit the line (replace "author me" with "new author")
            fseek(file, position - strlen(line), SEEK_SET); // <-- Moving file pointer to beginning of line
            fprintf(file, "\t%-15d%-60s%-40s%-15s\n", B.ID, B.bookName, B.authorName, B.date);
        }
        lineNumber++;
    }
    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION MODIFIED SUCESSFULLY!! \n" FORMAT);
    printf("\n\t\t  =============================================== ");


}

void editBorrowed(const char *filename){

    char line[MAX_LINES];
    char lineNumber = 0;
    long position;
    
    FILE *file;
    file = fopen(filename, "rw+");

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);

    printf("\n\t\t Fatima Student ID (06-): ");
    scanf("%ld", &S.ID);
    getchar();

    printf("\n\t\t Enter Student Name: ");
    fgets(S.studentName, 50, stdin);
    S.studentName[strcspn(S.studentName, "\n")] = '\0';

    printf("\n\t\t Enter Program (e.g.; BS Computer Science): ");
    fgets(S.program, 50, stdin);
    S.program[strcspn(S.program, "\n")] = '\0';

    printf("\n\t\t Enter Book ID: ");
    scanf("%d", &S.bookID);
    getchar(); // Consume the newline character

    printf("\n\t\t Enter Book Name: ");
    fgets(S.bookName, 50, stdin);
    S.bookName[strcspn(S.bookName, "\n")] = '\0';

    printf("\n\n\nStatus: ");
    scanf("%s", S.status);

    // Assuming the return date is one week from the borrow date
    struct tm returnDate;
    returnDate = *now;
    returnDate.tm_mday += 7;
    mktime(&returnDate);
    char returnDateString[11];
    strftime(returnDateString, sizeof(returnDateString), "%m-%d-%Y", &returnDate);


     while (fgets(line, sizeof(line), file)) {
        if (choice == lineNumber) {
            position = ftell(file); // Save the current offset
            // Edit the line (replace "author me" with "new author")
            fseek(file, position - strlen(line), SEEK_SET); // <-- Moving file pointer to beginning of line
            fprintf(file, "\t %-20ld%-35s%-35s%-10d%-35s%-13s%-15s%-10s\n", S.ID, S.studentName , S.program, S.bookID, S.bookName, B.date ,returnDateString, S.status);
        }
        lineNumber++;
    }
    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION MODIFIED SUCESSFULLY!! \n" FORMAT);
    printf("\n\t\t  =============================================== ");


}
