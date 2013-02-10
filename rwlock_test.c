#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/file.h>
#include <errno.h>
#include <string.h> 
#include <time.h>
#include <fcntl.h>
#include "rwlock.h"

int main()
{
    char buf[128];
    time_t ltime;
    int fd = open("./tmp.txt",O_RDWR|O_APPEND);
    if(fd < 0)
    {
        fprintf(stderr,"open failed %s\n",strerror(errno));
        return -1;
    }

    int ret = write_lock(fd,0,SEEK_SET,0);
    if(ret)
    {
        fprintf(stderr,"fcntl  failed for father\n");
        return -2;
    }
    else
    {
        time(&ltime);
        fprintf(stderr,"%s    I got the lock\n",ctime_r(&ltime,buf));
    }

    ret = fork();
    if(ret == 0)
    {
        time(&ltime);  
        fprintf(stdout,"%s  I am the son process,pid is %d,ppid = %d\n",ctime_r(&ltime,buf),getpid(),getppid());
        write(fd,"write by son\n",32);
        sleep(100);
        time(&ltime);
        fprintf(stdout,"%s    son exit\n",ctime_r(&ltime,buf));
    }
    else if(ret > 0)
    {
        time(&ltime);
        fprintf(stdout,"%s    I am the father process,pid is %d\n",ctime_r(&ltime,buf),getpid());
        write(fd,"write by father\n",32);
        sleep(50);
        close(fd);
        time(&ltime);
        fprintf(stdout, "%s    father exit\n",ctime_r(&ltime,buf));
        return 0;
    }
    else
    {
        fprintf(stderr, "error happened in fork\n");
        return -3;
    }

}
