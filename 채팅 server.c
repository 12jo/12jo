jqtdmsl 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
  
#define BUFSIZE 1024 
  
void ErrorHandling(char *message);  
  
int main(int argc, char **argv) {
      
    WSADATA wsaData;
    SOCKET servSock, clntSock;   //SOCKET은 사실 UINT_PTR 형이다.
    SOCKADDR_IN servAddr, clntAddr;
          
    char message[BUFSIZE]; //Message Buffer
    int strLen;
    int fromLen, nRcv;
      
    if(argc!=2) {
        printf("Please, Insert Port Number\n");
        exit(1);
    }
     /*라이브러리 초기화*/     
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)        
        ErrorHandling("Load WinSock 2.2 DLL Error");  
    /*socket 생성*/
    servSock = socket(PF_INET, SOCK_STREAM, 0);
    if(servSock == INVALID_SOCKET) 
        ErrorHandling("Socket Error");
               
   /*주소정보 초기화*/
    memset(&servAddr, 0, sizeof(SOCKADDR_IN));
    servAddr.sin_family = AF_INET;  // 주소체계지정
    servAddr.sin_port = htons(atoi(argv[1]));  //문자열 기반의 port번호 초기화
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //문자열 기반의 ip주소 초기화 
      
	/*주소 정보 할당*/
    if(bind(servSock, (void *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("Bind Error");
	
	/*연결 요청 대기*/      
    if(listen(servSock, 2) == SOCKET_ERROR) 
        ErrorHandling("Listen Error");        
  
    fromLen = sizeof(clntAddr);
     /*연결 요청 대기 큐에서 대기중인 클라이언트의 연결요청을 수락*/
    clntSock = accept(servSock, (void *)&clntAddr, &fromLen); 
    if(clntSock == INVALID_SOCKET) {
        ErrorHandling("Accept Error");
    } else {
        printf("%s Connection Complete!\n", inet_ntoa(clntAddr.sin_addr));
        printf("Start ...\n");
    }
      
    closesocket(servSock); //소켓 닫음
      
    while(1) {
        printf("Message Receives ...\n");
        nRcv = recv(clntSock, message, sizeof(message) - 1, 0);
          
        if(nRcv == SOCKET_ERROR) {
            printf("Receive Error..\n");
            break;
        }
        message[nRcv] = '\0';
          
        if(strcmp(message, "exit") == 0) {
            printf("Close Clinet Connection..\n");
            break;
        }
          
        printf("Receive Message : %s", message);      
        printf("\nSend Message : ");
        gets(message);
        if(strcmp(message, "exit") == 0) {
            send(clntSock, message, (int)strlen(message), 0);
            break;
        }
        /*메시지 전송*/
        send(clntSock, message, (int)strlen(message), 0); 
    }
      
    closesocket(clntSock);
    WSACleanup();
      
    printf("Close Connection..\n");
    _getch();
      
    return 0;    
}
  
void ErrorHandling(char *message) {
    WSACleanup();
    fputs(message, stderr);
    fputc('\n', stderr);
    _getch();
    exit(1);
}
