// socket_r.cpp : �������̨Ӧ�ó������ڵ㡣
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
 WSADATA wsaData;                                   //ָ��WinSocket��Ϣ�ṹ��ָ��
 SOCKET sockListener;
 SOCKADDR_IN sin,saClient;                          //����������ַ��sin������
                                                    //saClient�����ӹ㲥��ַ������Ϣ
 char cRecvBuff[800];                               //������ջ�����
 int nSize,nbSize;
 int iAddrLen=sizeof(saClient);
 if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)           //����WinSocket�ĳ�ʼ��
 {
         printf("Can't initiates windows socket!Program stop.\n");//��ʼ��ʧ�ܷ���-1
         return -1;
 }
 sockListener=socket(AF_INET, SOCK_DGRAM,0);
 sin.sin_family = AF_INET;
 sin.sin_port = htons(7001);             //���Ͷ�ʹ�õķ��Ͷ˿ڣ����Ը�����Ҫ����
 sin.sin_addr.s_addr = htonl(INADDR_ANY);
 if(bind( sockListener, (SOCKADDR FAR *)&sin, sizeof(sin))!=0)
 {
  printf("Can't bind socket to local port!Program stop.\n");//��ʼ��ʧ�ܷ���-1
  return -1;
 }
 while(1)
 { 
  nSize = sizeof ( SOCKADDR_IN );
  if((nbSize=recvfrom (sockListener,cRecvBuff,800,0,
   (SOCKADDR FAR *) &saClient,&nSize))==SOCKET_ERROR) //������ʧ������ʾ����
  {
   printf("Recive Error");
   break;
  }
  cRecvBuff[nbSize] = '\0';                              //�ַ�����ֹ
  printf("%s\n",cRecvBuff);                              //��ʾ�����յ����ַ���
 
 
 }
 return 0;
}
