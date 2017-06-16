// socket.cpp : 定义控制台应用程序的入口点。
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
//创建新的套接字之前需要调用一个引入Ws2_32.dll库的函数,否则服务器和客户端连接不上
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
 WSADATA wsaData;                                    //指向WinSocket信息结构的指针
 SOCKET sockListener;                                //创建套接字
 SOCKADDR_IN saUdpServ;                              //指向通信对象的结构体指针                         
 BOOL fBroadcast = TRUE;                             //用于setsockopt(),表示允许
 char sendBuff[800];                                 //缓冲区存放发送的数据
 int ncount=0;                                       //用于显示消息数目
 //*************************** 第一步初始化Winsock   *****************************//
 if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)     //进行WinSocket的初始化
 {
  printf("Can't initiates windows socket!Program stop.\n");//初始化失败返回-1
  return -1;
 }
 //********************   第二步建立一个数据报类型的UDP套接字  ******************//
 sockListener=socket(PF_INET,SOCK_DGRAM,0);    
 //       setsockopt函数用于设置套接口选项
 //       采用广播形式须将第三个参数设置为SO_BROADCAST
 setsockopt ( sockListener,SOL_SOCKET,SO_BROADCAST, (CHAR *)&fBroadcast, sizeof (BOOL) );
 //  参数设置，注意要将IP地址设为INADDR_BROADCAST，表示发送广播UDP数据报
 saUdpServ.sin_family = AF_INET;
 saUdpServ.sin_addr.s_addr = htonl ( INADDR_BROADCAST );
 saUdpServ.sin_port = htons (UDP_PORT);               //发送用的端口，可以根据需要更改
 int i;
 cout<<"唐开宇为您服务"<<endl;
 cout<<"请输入发送次数:"<<endl;
 cin>>i;
 if(i>=0&&i<30000)
 for(int j=i;j>0;j--)                                  //循环发送数据
 {
  Sleep(1000);
  sprintf(sendBuff,"第 %d 次发送: 成功",ncount++);    //将ncount的值放入字符串senBuff中
  //**********************  第三步使用sendto函数进行通信    *************************//
  sendto ( sockListener,/*sendBuff*/pPack, lstrlenA (sendBuff)/*sizeof(udpPack)*/, 0, (SOCKADDR *) &saUdpServ, sizeof (SOCKADDR_IN));
  printf("%s\n",sendBuff); //将要广播的数据串输出

 }
 else
	while(1)                                 //循环发送数据
 {
  Sleep(1000);
  sprintf(sendBuff,"第 %d 次发送: 成功",ncount++);    //将ncount的值放入字符串senBuff中
  //**********************  第三步使用sendto函数进行通信    *************************//
  sendto ( sockListener,/*sendBuff*/pPack, lstrlenA (sendBuff)/*sizeof(udpPack)*/, 0, (SOCKADDR *) &saUdpServ, sizeof (SOCKADDR_IN));
  printf("%s\n",sendBuff); //将要广播的数据串输出

 }
 //*********************   第四步关闭socket  ***************************************//
 closesocket(sockListener);         //关闭监听socket
 WSACleanup();
 system("pause");
 return 0;
}
 
const static int    BUFFER_LENGTH = 12;
 