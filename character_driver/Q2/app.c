/******************************************************************************

Q2). Build simple Character Diver in which device is the memory block and using
     dynamic major number assignment?

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
    char msg[] = "Hello from kernel..!";

    memset(Ubuff, 0, sizeof(Ubuff));
    fd = open("/dev/dynamic_driver", O_RDWR, 0666);

    if(fd < 0)
    {
        printf("Error in opening file\n");
        return -1;
    }
    
    write(fd, msg, sizeof(msg));
    
    read(fd, &Ubuff, sizeof(Ubuff));

    printf("\nData from kernel : %s\n\n", Ubuff);

    close(fd);
    return 0;
}
