// socket_r.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "winsock.h"
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#pragma comment(lib,"ws2_32.lib")
int main(int argc, char* argv[])
{
 WSADATA wsaData;                                   //指向WinSocket信息结构的指针
 SOCKET sockListener;
 SOCKADDR_IN sin,saClient;                          //设置两个地址，sin用来绑定
                                                    //saClient用来从广播地址接收消息
 char cRecvBuff[800];                               //定义接收缓冲区
 int nSize,nbSize;
 int iAddrLen=sizeof(saClient);
 if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)           //进行WinSocket的初始化
 {
         printf("Can't initiates windows socket!Program stop.\n");//初始化失败返回-1
         return -1;
 }
 sockListener=socket(AF_INET, SOCK_DGRAM,0);
 sin.sin_family = AF_INET;
 sin.sin_port = htons(7001);             //发送端使用的发送端口，可以根据需要更改
 sin.sin_addr.s_addr = htonl(INADDR_ANY);
 if(bind( sockListener, (SOCKADDR FAR *)&sin, sizeof(sin))!=0)
 {
  printf("Can't bind socket to local port!Program stop.\n");//初始化失败返回-1
  return -1;
 }
 while(1)
 { 
  nSize = sizeof ( SOCKADDR_IN );
  if((nbSize=recvfrom (sockListener,cRecvBuff,800,0,
   (SOCKADDR FAR *) &saClient,&nSize))==SOCKET_ERROR) //若接收失败则提示错误
  {
   printf("Recive Error");
   break;
  }
  cRecvBuff[nbSize] = '\0';                              //字符串终止
  printf("%s\n",cRecvBuff);                              //显示所接收到的字符串
 
 
 }
 return 0;
}
