#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <stdlib.h>

#define NUM_OF_CONSUMERS 3

struct msgbuff
{
   long mtype;
   char mtext[100];
};

int main(void)
{
   key_t key;
   int msgid;
   char *msg = "p1 to p2 p3 and p4";  
   struct msgbuff msg_buff;
   size_t i = 0;

   if (NULL == fopen("/tmp/msg_queue", "a+"))
   {
      perror("fopen");
      return 1;
   }

   key = ftok("/tmp/msg_queue", 'a');
   if (-1 == key)
   {
      perror("ftok");
      return 1;
   }

   msgid = msgget(key, 0777 | IPC_CREAT);
   if (-1 == msgid)
   {
      perror("msgget");
      return 1;
   }

   msg_buff.mtype = 1;
   memcpy(msg_buff.mtext, msg, strlen(msg) + 1); 

   /* adding 3 msgs to queue */
   for (; i < NUM_OF_CONSUMERS; ++i)
   {
      if (-1 == msgsnd(msgid, &msg_buff, sizeof(msg_buff), 0))
      {
         perror("msgsnd");
         return 1;
      }
   }

   return 0;
}
