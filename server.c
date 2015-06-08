#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<semaphore.h>

#define BUF_SIZE 100
#define MAX_CLNT 256
void * handle_clnt(void* arg);
void send_msg(char* msg,int len);
void error_handling(char* msg);


char id_in[15];
char pw_in[15];
   
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc,char* argv[])
{
  int serv_sock, clnt_sock;
  struct sockaddr_in serv_adr, clnt_adr;
  int clnt_adr_sz;
  pthread_t t_id;
 if(argc!=2)
 {
  printf("useage : %s <port>\n",argv[0]);
  exit(1);
 }
 
 pthread_mutex_init(&mutx, NULL);
 serv_sock=socket(PF_INET,SOCK_STREAM,0);

 memset(&serv_adr,0,sizeof(serv_adr));
 serv_adr.sin_family=AF_INET;
 serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
 serv_adr.sin_port=htons(atoi(argv[1]));
 
 if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
   error_handling("bind() error");

 if(listen(serv_sock,5)==-1)
  error_handling("listen() error");


 while(1)
 {
  clnt_adr_sz=sizeof(clnt_adr);
  clnt_sock=accept(serv_sock ,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
  
  str_len=read(sock, id_in,sizeof(id_in)); //+ 
 //+
 printf("%s",id_in);
  lo(id_in[5],pw_in[5]);
  pthread_mutex_lock(&mutx);
  clnt_socks[clnt_cnt++]=clnt_sock;
  pthread_mutex_unlock(&mutx);

  pthread_create(&t_id, NULL, handle_clnt, (void*) &clnt_sock);
  pthread_detach(t_id);
  printf("connected client IP: %s \n, inet_ntoa(clnt_adr.sin_addr)");
 
 }
 close(serv_sock);
return 0;
} 

void * handle_clnt(void *arg)
{
 int clnt_sock=*((int*)arg);
 int str_len=0, i;
 char msg[BUF_SIZE];

 while((str_len=read(clnt_sock, msg,sizeof(msg)))!=0)
  send_msg(msg,str_len);
 
 pthread_mutex_lock(&mutx);
 for(i=0; i<clnt_cnt; i++)
 {
  if(clnt_sock==clnt_socks[i])
  {
    while(i++<clnt_cnt-1)
      clnt_socks[i]=clnt_socks[i+1];
    break;
  }
 }
 clnt_cnt--;
 pthread_mutex_unlock(&mutx);
 close(clnt_sock);
 return NULL;
}
void send_msg(char* msg,int len)
{
  int i;
  pthread_mutex_lock(&mutx);
  for(i=0;i<clnt_cnt;i++)
   write(clnt_socks[i],msg,len);
 pthread_mutex_unlock(&mutx);
}
void error_handling(char* message)
{
 fputs(message, stderr);
 fputc('\n',stderr);
 exit(1);
}
void lo(char id_in[5],char pw_in[5])
{
 struct
{
   char id[15];
   char pw[15];
   int state;//로그인 되지 않은 상태를 0으로 함
}typedef member;

   FILE *fp;
   int n=0;
   int i;
   char a[15];
   member *mem;

  
   fp = fopen("data.txt", "a");
   while (feof(fp) == 0)
   {
      fscanf(fp, "%s", a);
      n++;
   }//저장되어있는 정보 개수
   mem = (member*)malloc(sizeof(member)*n/3);
   fseek(fp, 0, SEEK_SET);
   for (i = 0; i < n / 3; i++)
   {
      fscanf(fp, "%s", mem[i].id);
      fscanf(fp, "%s", mem[i].pw);
      fscanf(fp, "%d", mem[i].state);
   }
   fclose(fp);
   //아이디 패스워드를 id_in, pw_in에 받고
   for (i = 0; i < n / 3; i++)
   {
      if (strcmp(mem[i].id,id_in))
         if (strcmp(mem[i].pw, pw_in))
         {
            mem[i].state = 1;
            //로그인 성공 메시지를 보냄
            break;
         }
   }
}

