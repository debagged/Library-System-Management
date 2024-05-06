#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
    #define SYS_COMMAND "libsys1.exe" // On Windows, specify the executable file extension
#else
    #define SYS_COMMAND "./libsys1"   // On Unix-like systems, use the file path directly
#endif


int main(){

    char userName[100];
    char password[100];
    
    char tab[] = {"\t\t\t"};
    printf("\e[1;1H\e[2J"); // clear screen

    printf("%sEnter Username: ", tab);
    scanf("%s", userName);

    printf("%sEnter Password: ", tab);
    scanf("%s", password);


    if (strcmp(userName, "admin") == 0 && strcmp(password, "pass1234") == 0 )
    {
        printf("\aLogin Successfully");
            fflush(stdout); // Flush the output buffer to ensure the message is displayed immediately
        sleep(1);
        system(SYS_COMMAND); // Use the defined command for system call
    }
    else
    {
        printf("Invalid Info\n");
    }

    return 0;
}