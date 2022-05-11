#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>

int main(void)
{
    int fds_ping[2];
    int fds_pong[2];
    int id = 0;

    if (-1 == pipe(fds_ping))
    {
        perror("error");
        return 1;
    }

    if (-1 == pipe(fds_pong))
    {
        perror("error");
        return 1;
    }

    id = fork();

    if (0 == id)
    {
        char ping_buff[7];
        if (-1 == read(fds_ping[0], ping_buff, 7))
        {
            perror("read");
            return 1;
        }
        printf("%s\n", ping_buff); 
        if (-1 == write(fds_pong[1], "<-pong", 7))
        {
            perror("write");
            return 1;
        }
    }
    else
    {
        char pong_buff[7];
        if (-1 == write(fds_ping[1], "ping->", 7))
        {
            perror("write");
            return 1;
        }
        if (-1 == read(fds_pong[0], pong_buff, 7))
        {
            perror("read");
            return 1;
        }
        printf("%s\n", pong_buff); 
    }

    close(fds_ping[0]);
    close(fds_ping[1]);
    close(fds_pong[0]);
    close(fds_pong[1]);

    return 0;
}
