
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

static struct sembuf g_decrement;

struct msgbuff
{
   long mtype;
   char mtext[100];
};

static int SemaphoreOpen(const char *key_file)
{
   int semid;
   key_t key = 0;

   key = ftok(key_file, 'a');
   if (-1 == key)
   {
      perror("ftok");
      exit(1);
   }

   semid = semget(key, 1, 0);
   if (-1 == semid)
   {
      perror("semget");
      exit(1);
   }

   return semid;
}

static void InitSemBuffers(void)
{
	g_decrement.sem_flg = IPC_NOWAIT;
	g_decrement.sem_num = 0;
	g_decrement.sem_op = -1;
}

int main(void)
{
   key_t key;
   int shmid;
   char *shm_buff = NULL;
   int semid = SemaphoreOpen("/tmp/semid");

   InitSemBuffers();
   
   if (-1 == semop(semid, &g_decrement, 1))
   {
      perror("semop");
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

   printf("%s\n", shm_buff);

   if (-1 == shmdt(shm_buff))
   {
      perror("shmdt");
      return 1;
   }

   if (-1 == shmctl(shmid, IPC_RMID, NULL))
   {
      perror("shmctl");
      return 1;
   }

   return 0;
}
