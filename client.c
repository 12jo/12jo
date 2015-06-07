#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char* message)

int main(int argc,char* argv[])
{
 int sock;
 char message[BUF_SIZE];
 int str_len,rev_len, rev_cnt;
 struct sockaddr_in serv_addr;
 pid_t pid;
 if(argc!=3)
 {
  printf("Useage : %s <IP> <port> \n",argv[0]);
  exit(1);
 }

 sock=socket(PF_INET,SOCK_STREAM,0);
 if(sock==-1)
 {
  error_handling("socket() error");
  exit(1);
 }
 
 memset(&serv_adr,0,sizeof(serv_adr));
 serv_adr.sin_family=AF_INET;
 serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
 serv_adr.sin_port=htons(atoi(argv[2]));
  
 if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
  error_handling("connect error");
 else
  puts("connected............");

 pid=fork();
 if(pid==0)
 {
  }
else
 {
 }

}

void read(int sock,char *buf)
{

}
