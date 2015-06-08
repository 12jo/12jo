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

void error_handling(char* msg);
void * send_msg(void *arg);
void * recv_msg(void *arg);


char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];


int main(int argc,char* argv[])
{
 int sock;
 struct sockaddr_in serv_addr;
 pthread_t snd_thread, rcv_thread;
 void* thread_return;
 char id[10];
 char pw[10];
 char login[10];
 if(argc!=4)
 {
  printf("Useage: %s <IP> <PORT> <NAME>\n",argv[0]);
  exit(1);
 }
 sprintf(name, "[%s]",argv[3]);
 sock=socket(PF_INET,SOCK_STREAM,0);
 
 memset(&serv_addr, 0, sizeof(serv_addr));
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
 serv_addr.sin_port=htons(atoi(argv[2]));
 
 if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
  error_handling("connect() error");

 printf("아이디 입력하시오");
fgets(id, 10, stdin);
 write(sock,id,sizeof(id));
printf("비밀번호 입력하시오");
fgets(pw, 10, stdin);
 write(sock,pw,strlen(pw));

 fflush(stdin);
 read(sock,login,strlen(login));
  if(login[0]=='1')
 {
  printf("login success\n");
  pthread_create(&snd_thread, NULL, send_msg,(void*)&sock);
  pthread_create(&rcv_thread, NULL,recv_msg,(void*)&sock);
  pthread_join(snd_thread,&thread_return);
  pthread_join(rcv_thread,&thread_return);
  close(sock);
  return 0;
 }
 else
 {
   printf("login fail\n");
   exit(1);
 }
}
void* send_msg(void* arg)
{
 int sock=*((int*)arg);
 char name_msg[NAME_SIZE+BUF_SIZE];
 while(1)
 {
  fgets(msg, BUF_SIZE, stdin);
  sprintf(name_msg,"%s %s",name,msg);
  write(sock,name_msg,strlen(name_msg));
 }
 return NULL;
}
void* recv_msg(void* arg)
{
 int sock=*((int*)arg);
 char name_msg[NAME_SIZE+BUF_SIZE];
 int str_len;
 while(1)
 {
  str_len=read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
  if(str_len==-1)
   return (void*) -1;
 name_msg[str_len]=0;
 fputs(name_msg, stdout);
 }
 return NULL;
}
void error_handling(char* msg)
{
 fputs(msg, stderr);
 fputc('\n', stderr);
 exit(1);
}
