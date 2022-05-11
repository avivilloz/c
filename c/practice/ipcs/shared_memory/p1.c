#include <stdio.h> 
#include <sys/ipc.h> 
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define NUM_OF_CONSUMERS 3

static struct sembuf g_increment;

union semun 
{
   int val;
};

struct msgbuff
{
   long mtype;
   char mtext[100];
};

static int SemaphoreCreate(const char *key_file)
{
   FILE *fp = NULL;
   key_t key = 0;
   int semid;
   union semun param;

   fp = fopen(key_file, "a+");
   if (NULL == fp)
   {
      perror("fopen");
      exit(1);
   }
   fclose(fp);

   key = ftok(key_file, 'a');
   if (-1 == key)
   {
      perror("ftok");
      exit(1);
   }

   semid = semget(key, 1, 0777 | IPC_CREAT);
   if (-1 == semid)
   {
      perror("semget");
      exit(1);
   }

   param.val = 0;
   if (-1 == semctl(semid, 0, SETVAL, param))
   {
      perror("semctl");
      exit(1);
   }

   return semid;
}

static void InitSemBuffers(void)
{
	g_increment.sem_flg = IPC_NOWAIT;
	g_increment.sem_num = 0;
	g_increment.sem_op = NUM_OF_CONSUMERS;
}

int main(void)
{
   key_t key;
   int shmid;
   char *msg = "p1 to p2 p3 and p4";  
   char *shm_buff = NULL;
   int semid = SemaphoreCreate("/tmp/semid");

   InitSemBuffers();

   if (NULL == fopen("/tmp/shared_memory", "a+"))
   {
      perror("fopen");
      return 1;
   }

   key = ftok("/tmp/shared_memory", 'a');
   if (-1 == key)
   {
      perror("ftok");
      return 1;
   }

   shmid = shmget(key, 1024, 0777 | IPC_CREAT);
   if (-1 == shmid)
   {
      perror("shmget");
      return 1;
   }

   shm_buff = (char *)shmat(shmid, NULL, 0);
   if (-1 == *shm_buff)
   {
      perror("shmat");
      return 1;
   }

   memcpy(shm_buff, msg, strlen(msg) + 1);

   if (-1 == shmdt(shm_buff))
   {
      perror("shmdt");
      return 1;
   }

   if (-1 == semop(semid, &g_increment, 1))
   {
      perror("semop");
      return 1;
   }

   return 0;
}
