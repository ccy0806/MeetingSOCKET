//����һЩ���ڵ���������������ض�������
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<windows.h>

int main()
{
	//����windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket����
	WSAStartup(ver, &dat);

	//1.����socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		std::cout << "����socketʧ��" << std::endl;
	}
	else
	{
		std::cout << "����socket�ɹ�" << std::endl;
	}
	//2���ӷ����� connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int result = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == result)
	{
		std::cout << "���ӷ�����ʧ��" << std::endl;
	}
	else
	{
		std::cout << "���ӷ������ɹ�" << std::endl;


	}
	//3���շ�������Ϣrecv
	char recvBuf[256] = {};
	//���ؽ��յ��ĳ���
	int nlen = recv(_sock, recvBuf, 256, 0);
	if (nlen > 0)
	{
		std::cout << "���յ���������ݣ�" << recvBuf << std::endl;
	}
	//4�ر�socket,closesocket
	closesocket(_sock);
	//���windows socket����
	WSACleanup();
	getchar();
	return 0;
}