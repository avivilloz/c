#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    char *pingpong_fifo = "/tmp/pingpong_fifo";
    char buffer[7];
    int fd = 0;

    mkfifo(pingpong_fifo, 777);

    while (1)
    {
        fd = open(pingpong_fifo, O_WRONLY);
        write(fd, "ping->", 7);
        close(fd);
        fd = open(pingpong_fifo, O_RDONLY);
        read(fd, buffer, 7);
        printf("%s\n", buffer); 
        close(fd);
    }
    return 0;
}
