#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){

    char userName[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%s", userName);

    printf("Enter Password: ");
    scanf("%s", password);


    if (strcmp(userName, "admin") == 0 && strcmp(password, "pass1234") == 0 )
    {
        printf("Login Successfully");
        system("./libsys");
    }
    else
    {
        printf("Invalid Info\n");
    }

    return 0;
}