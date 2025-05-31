#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

//structure for message queue
struct mesg_buffer {
long mesg_type;
char mesg_text[100];
} message;
int main()
{
key_t key;
int msgid;

//ftok to genatrate  unique key
key = ftok("progfile",65);
//msgget creates a mesage queue
//and return identifiers
msgid= msgget(key,0666 | IPC_CREAT);
message.mesg_type = 1;
printf("Write a data :");
fgets(message.mesg_text,MAX,stdin);
//msgsnd to send message
msgsnd(msgid,&message,sizeof(message.mesg_text),0);
//display the message
printf("Data send is : %s \n",message.mesg_text);

return 0;
}
------------------------------------------

//receive
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;
int main()
{
	key_t key;
	int msgid;
	//ftok to genararte unique key
	key= ftok("progfile",65);
	//msgget creates a mesage queue
//and return identifiers
msgid= msgget(key,0666 | IPC_CREAT);
//msgrcv to recieve message
msgrcv(msgid,&message , sizeof(message.mesg_text),1,0);
//display the message
printf("Data Receive is : %s \n",
message.mesg_text);
//to destroy the message queue
msgctl(msgid,IPC_RMID,NULL);

return 0;
}

--------------------------------
output:
shifak_ahamed@LAPTOP-TQKP6C7B :~ $ gcc msg.c -o msg
shifak_ahamed@LAPTOP-TQKP6C7B :~ $ gcc msgrec.c -o msgrec
shifak_ahamed@LAPTOP-TQKP6C7B :~ $ . /msg
Write a data :Hello sam
Data send is : Hello sam

shifak_ahamed@LAPTOP-TQKP6C7B :~ $ . /msgrec
Data Receive is : Hello sam

