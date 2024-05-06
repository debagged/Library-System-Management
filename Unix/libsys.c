#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // used for usleep function
#include <time.h>

//BOLD WHITE {
#define BOLD "\033[1m" 
#define RESET "\033[0m"
//}
/*
#include <stdio.h>

#define BOLD "\033[1m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

int main() {
  printf("%s%sThis is bold green text!%s\n", BOLD, GREEN, RESET);
  return 0;
}

*/
//BOLD GREEN {
#define GREEN "\x1b[1;32m"
#define FORMAT "\x1b[0m"
// }

//Void Funtion Declarations {
void loadingAnimation();
void addBooks();
void viewBooks();
void borrowBooks();
void borrowedList();

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
} S;


FILE *fp; //Allowing for file creation to occur 
int book_id_counter = 1; // Declare as a global variable


int main() 
{
    int choices;

    do {
        printf("\e[1;1H\e[2J"); // clear screen
    
        printf("\n\n");
        printf(BOLD "\t   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n" RESET);
        printf(BOLD "\t   ┃              "GREEN"WELCOME TO BOOKLY RECORDS"FORMAT"                 ┃\n" RESET);
        printf(BOLD "\t   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n" RESET);


        printf(BOLD"\t      MAIN MENU \n" RESET);
        printf("\t     ┏━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        printf("\t     ┃  Option      │      Description                   ┃\n");
        printf("\t     ┠──────────────┼────────────────────────────────────┨\n");
        printf("\t     ┃  1           │      Add Books                     ┃\n");
        printf("\t     ┠──────────────┼────────────────────────────────────┨\n");
        printf("\t     ┃  2           │      View Books                    ┃\n");
        printf("\t     ┠──────────────┼────────────────────────────────────┨\n");
        printf("\t     ┃  3           │      Borrow Books                  ┃\n");
        printf("\t     ┠──────────────┼────────────────────────────────────┨\n");
        printf("\t     ┃  4           │      Borrowed Book List            ┃\n");
        printf("\t     ┠──────────────┼────────────────────────────────────┨\n");
        printf("\t     ┃  0           │      Exit                          ┃\n");
        printf("\t     ┗━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");


        printf("\n\n\n\t\tEnter your choice here >> ");
        scanf(" %d", &choices);
    
        getchar();// Consume the newline character in the buffer
    
        switch (choices) {
            case 0:
                printf("\e[1;1H\e[2J"); // clear screen
                printf(BOLD "\n\t  ************************************************\n" RESET);
                printf("\n\t\tExiting the Program... ");
                loadingAnimation();

                printf("\e[1;1H\e[2J"); // clear screen
                printf("\n");
                printf(BOLD "\t    ************************************************\n" RESET);
                printf(BOLD "\t    **    "GREEN"THANK YOU FOR USING BOOKLY RECORDS!"FORMAT"     **\n" RESET);
                printf(BOLD "\t    ************************************************\n\n" RESET);                
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
        if (ftell(fp) == 0) {  // Check the position, if it's 0, the file is empty
            fprintf(fp, "\t%-15s%-60s%-40s%-15s\n\n", "Book ID", "Book Name", "Author Name", "Date Added");
        }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file


    printf(GREEN "\n\n\t\t===================[ ADD BOOKS ]===================\n" FORMAT);
    
    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);

    B.ID = book_id_counter++;
 
    printf(BOLD "\n\t\t  Enter Book Name: " RESET);
    fgets(B.bookName, 50, stdin);
    B.bookName[strcspn(B.bookName, "\n")] = '\0';

    printf(BOLD "\n\t\t  Enter Author Name: " RESET);
    fgets(B.authorName, 50, stdin);
    B.authorName[strcspn(B.authorName, "\n")] = '\0';

    fprintf(fp, "\t%-15d%-60s%-40s%-15s\n", B.ID, B.bookName, B.authorName, B.date);

    sleep(2);

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
        fprintf(fp, "\t %-20s%-35s%-35s%-10s%-35s%-13s%-15s\n", "Student ID[06-]", "Student Name", "Program", "Book ID", "Book Name", "Date Lent","Return Date");
    }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file

    printf("\e[1;1H\e[2J"); // clear screen

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

    printf("\n\t\t Enter Book ID: ");
    scanf("%d", &S.bookID);
    getchar(); // Consume the newline character

    printf("\n\t\t Enter Book Name: ");
    fgets(S.bookName, 50, stdin);
    S.bookName[strcspn(S.bookName, "\n")] = '\0';

    // Assuming the return date is one week from the borrow date
    struct tm returnDate;
    returnDate = *now;
    returnDate.tm_mday += 7;
    mktime(&returnDate);
    char returnDateString[11];
    strftime(returnDateString, sizeof(returnDateString), "%m-%d-%Y", &returnDate);

    fprintf(fp, "\t %-20ld%-35s%-35s%-10d%-35s%-13s%-15s\n", S.ID, S.studentName , S.program, S.bookID, S.bookName, B.date ,returnDateString);

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

