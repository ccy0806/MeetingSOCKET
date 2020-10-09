//避免一些早期的遗留定义与后期重定义问题
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<windows.h>


//#pragma comment(lib,"ws2_32.lib")

int main()
{
	//启动windows socket 2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket启用
	WSAStartup(ver, &dat);

	//1.建立一个socket(,,协议)
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.bind 绑定网络端口
	//定义一个连接的数据
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_port = htons(4567);//host to net unsigned short
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in)))
	{
		std::cout << "ERROR,绑定失败" << std::endl;
	}
	else
	{
		std::cout << "绑定成功" << std::endl;
	}
	//3listen 监听网络端口.   listen(socket,最大等待数)
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		std::cout << "ERROR,监听网络端口失败" << std::endl;
	}
	else
	{
		std::cout << "监听网络端口成功" << std::endl;
	}
	//4等待接收客户端连接
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(clientAddr);
	SOCKET _cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _cSock)
	{
		std::cout << "接收到无效的客户端SOCKET" << std::endl;
	}
	//inet_ntoa:将地址数组转为字符串
	std::cout << "新客户端加入：IP:" << inet_ntoa(clientAddr.sin_addr) << std::endl;
	char _recvBuf[128] = {};
	while (true)
	{
		//接收客户端数据
		int nLen = recv(_cSock, _recvBuf, 128, 0);
		if (nLen <= 0)
		{
			printf("客户端已退出");
			break;
		}
		if (0 == strcmp(_recvBuf, "getName"))
		{
			char msgBuf[] = "xq";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge"))
		{
			char msgBuf[] = "18";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else
		{
			char msgBuf[] = "hello,i'm server.";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		//5 send  向客户端发送数据

	}

	//关闭 closesocket
	closesocket(_sock);


	WSACleanup();
	printf("已退出");
	getchar();
	return 0;
}