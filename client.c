#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#include<semaphore.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void error_handling(char* message)
void *send_msg(void *arg);
void *recv_msg(void *arg);


char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];


int main(int argc,char* argv[])
{
 int sock;
// int clnt_sock;
 int str_len,i;
 struct sockaddr_in serv_addr;
 pthread_t snd_thread, rcv_thread;
 void* thread_return;
 
 if(argc!=4)
 {
  printf("Useage: %s <IP> <PORT> <NAME>\n",argv[0]);
  exit(1);
 }

 if(argc!=2)
 {
  printf("useage:%s <port> ,argv[0]");
  exit(1);
 }

 serv_sock=socket(AF_INET,SOCK_STREAM,0);
 
 memset(&serv_addr, 0, sizeof(serv_addr));
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
 serv_addr.sin_port=htons(atoi(argv[2]));
 
 if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
  error_handling("connect(0 error")

 pthread_create(&snd_thread, NULL, send_msg,(void*)&sock);
 pthread_create(&rcv_thread, NULL,recv_msg,(void*)&sock);
 pthread_join(snd_thread,&thread_return);
 pthread_join(rcv_thread,&thread_return);
 close(sock);
 return 0;
}
void* send_msg(void* arg)
{
 int sock=*((int*)arg);
 char name_msg[NAME_SIZE+BUF_SIE];
 while(1)
 {
  fgets(msg, BUF_SIZE, stdin);
  sprintf(name_msg,"%s %s",name, msg);
  write(sock,name_msg,strlen(name_msg));
 }
 return NULL;
}
void error_handling(char* message)
{
 fputs(message, stderr);
 fputc('\n', stderr);
 exit(1);
}
