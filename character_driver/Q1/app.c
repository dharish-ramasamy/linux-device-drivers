/******************************************************************************

Q1). Build simple Character Diver in which device is the memory block and using
     static major number assignment?

*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int fd;
    char Ubuff[100];
    char msg[] = "Hello from kernel..!!";
   
    memset(Ubuff, 0, sizeof(Ubuff));
    
    fd = open("/dev/static_driver", O_RDWR, 0666);

    if(fd < 0)
    {
        printf("Error in opening the file\n");
        return -1;
    }

    write(fd,msg, sizeof(msg));

    read(fd, (char *)&Ubuff, sizeof(Ubuff));

    printf("\nData from the Kernel space : %s\n\n",Ubuff);

    close(fd);
    return 0;
}
