// socket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <string>

#include <iostream>
#include "winsock.h"
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>

#include <fcntl.h>
using namespace std;
//�����µ��׽���֮ǰ��Ҫ����һ������Ws2_32.dll��ĺ���,����������Ϳͻ������Ӳ���
#pragma comment(lib,"ws2_32.lib")
struct test {
 string str;
};
struct UdpHeartPack {
    char UDPData[16] ;
};
int main(int argc, char* argv[])
{
 struct UdpHeartPack udpPack;
 static int UDP_PORT = 7001;
 udpPack.UDPData[0] = 'h';
 udpPack.UDPData[1] = 'e';
 udpPack.UDPData[2] = 'l';
 udpPack.UDPData[3] = 'l';
 udpPack.UDPData[4] = 'o';
 udpPack.UDPData[5] = ' ';
 udpPack.UDPData[6] = 'w';
 udpPack.UDPData[7] = 'o';
 udpPack.UDPData[8] = 'r';
 udpPack.UDPData[9] = 'l';
 udpPack.UDPData[10] = 'd';
 udpPack.UDPData[11] = '\0';
 char *pPack = (char *) &udpPack;
 WSADATA wsaData;                                    //ָ��WinSocket��Ϣ�ṹ��ָ��
 SOCKET sockListener;                                //�����׽���
 SOCKADDR_IN saUdpServ;                              //ָ��ͨ�Ŷ���Ľṹ��ָ��                         
 BOOL fBroadcast = TRUE;                             //����setsockopt(),��ʾ����
 char sendBuff[800];                                 //��������ŷ��͵�����
 int ncount=0;                                       //������ʾ��Ϣ��Ŀ
 //*************************** ��һ����ʼ��Winsock   *****************************//
 if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)     //����WinSocket�ĳ�ʼ��
 {
  printf("Can't initiates windows socket!Program stop.\n");//��ʼ��ʧ�ܷ���-1
  return -1;
 }
 //********************   �ڶ�������һ�����ݱ����͵�UDP�׽���  ******************//
 sockListener=socket(PF_INET,SOCK_DGRAM,0);    
 //       setsockopt�������������׽ӿ�ѡ��
 //       ���ù㲥��ʽ�뽫��������������ΪSO_BROADCAST
 setsockopt ( sockListener,SOL_SOCKET,SO_BROADCAST, (CHAR *)&fBroadcast, sizeof (BOOL) );
 //  �������ã�ע��Ҫ��IP��ַ��ΪINADDR_BROADCAST����ʾ���͹㲥UDP���ݱ�
 saUdpServ.sin_family = AF_INET;
 saUdpServ.sin_addr.s_addr = htonl ( INADDR_BROADCAST );
 saUdpServ.sin_port = htons (UDP_PORT);               //�����õĶ˿ڣ����Ը�����Ҫ����
 int i;
 cout<<"�ƿ���Ϊ������"<<endl;
 cout<<"�����뷢�ʹ���:"<<endl;
 cin>>i;
 if(i>=0&&i<30000)
 for(int j=i;j>0;j--)                                  //ѭ����������
 {
  Sleep(1000);
  sprintf(sendBuff,"�� %d �η���: �ɹ�",ncount++);    //��ncount��ֵ�����ַ���senBuff��
  //**********************  ������ʹ��sendto��������ͨ��    *************************//
  sendto ( sockListener,/*sendBuff*/pPack, lstrlenA (sendBuff)/*sizeof(udpPack)*/, 0, (SOCKADDR *) &saUdpServ, sizeof (SOCKADDR_IN));
  printf("%s\n",sendBuff); //��Ҫ�㲥�����ݴ����

 }
 else
	while(1)                                 //ѭ����������
 {
  Sleep(1000);
  sprintf(sendBuff,"�� %d �η���: �ɹ�",ncount++);    //��ncount��ֵ�����ַ���senBuff��
  //**********************  ������ʹ��sendto��������ͨ��    *************************//
  sendto ( sockListener,/*sendBuff*/pPack, lstrlenA (sendBuff)/*sizeof(udpPack)*/, 0, (SOCKADDR *) &saUdpServ, sizeof (SOCKADDR_IN));
  printf("%s\n",sendBuff); //��Ҫ�㲥�����ݴ����

 }
 //*********************   ���Ĳ��ر�socket  ***************************************//
 closesocket(sockListener);         //�رռ���socket
 WSACleanup();
 system("pause");
 return 0;
}
 
const static int    BUFFER_LENGTH = 12;
 