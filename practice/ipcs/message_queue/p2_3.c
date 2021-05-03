#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>

struct msgbuff
{
   long mtype;
   char mtext[100];
};

int main(void)
{
   key_t key;
   int msgid;
   struct msgbuff msg_buff;

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

   if (-1 == msgrcv(msgid, &msg_buff, sizeof(msg_buff), 1, 0))
   {
      perror("msgrcv");
      return 1;
   }

   printf("%s\n", msg_buff.mtext);

   return 0;
}
