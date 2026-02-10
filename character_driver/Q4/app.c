#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    int fd;

    char path[100];
    char Ubuff[100];
    char msg[] = "Hello, from kernel device 1..!\n";

    if (argc < 2) 
    {
        printf("No arguement is passed from command line except \"%s\"\n", argv[0]);
        return 1;
    }

    int device_num = atoi(argv[1]);

    sprintf(path, "/dev/multi_device%d", device_num);

    fd = open(path, O_RDWR, 0666);
    
    if(fd < 0)
    {
        printf("Error in opening file\n");
        return -1;
    }

    if(write(fd, msg, sizeof(msg) < 0))
    {
        printf("Error in writing..\n");
        return -1;
    }

    lseek(fd, 0, SEEK_SET);  

    if(read(fd, Ubuff, sizeof(Ubuff)) < 0)
    {
        printf("Error while reading..\n");
        return -2;
    }
    printf("Data from kernel : %s\n", Ubuff);

    close(fd);
    return 0;
}
