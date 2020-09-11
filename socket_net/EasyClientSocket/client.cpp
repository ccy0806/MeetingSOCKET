//避免一些早期的遗留定义与后期重定义问题
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<windows.h>

int main()
{
	//启动windows socket 2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket启用
	WSAStartup(ver, &dat);

	//1.建立socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		std::cout << "建立socket失败" << std::endl;
	}
	else
	{
		std::cout << "建立socket成功" << std::endl;
	}
	//2连接服务器 connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int result = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == result)
	{
		std::cout << "连接服务器失败" << std::endl;
	}
	else
	{
		std::cout << "连接服务器成功" << std::endl;


	}
	//3接收服务器信息recv
	char recvBuf[256] = {};
	//返回接收到的长度
	int nlen = recv(_sock, recvBuf, 256, 0);
	if (nlen > 0)
	{
		std::cout << "接收到服务端数据：" << recvBuf << std::endl;
	}
	//4关闭socket,closesocket
	closesocket(_sock);
	//清除windows socket环境
	WSACleanup();
	getchar();
	return 0;
}