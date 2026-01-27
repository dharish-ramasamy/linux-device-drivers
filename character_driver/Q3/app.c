/******************************************************************************

Q3). Build Character Driver in which user application will send ‘a’ or ‘A’ character
     and driver will send back character ‘b’ or ‘B’?

*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd;
    char Ubuff[100];
    char msg;

    printf("Enter user input (either \"a\" or \"A\"): ");
    scanf("%s", &msg);

    fd = open("/dev/msg_driver", O_RDWR, 0666);

    if(fd < 0)
    {
        printf("Error in opening file\n");
        return -1;
    }

    write(fd, &msg, sizeof(msg));

    read(fd, &Ubuff, sizeof(Ubuff));

    printf("Data from kernel : %s\n", Ubuff);

    close(fd);
    return 0;
}
