//����һЩ���ڵ���������������ض�������
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<windows.h>


//#pragma comment(lib,"ws2_32.lib")

int main()
{
	//����windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket����
	WSAStartup(ver, &dat);

	//1.����һ��socket(,,Э��)
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.bind ������˿�
	//����һ�����ӵ�����
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_port = htons(4567);//host to net unsigned short
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in)))
	{
		std::cout << "ERROR,��ʧ��" << std::endl;
	}
	else
	{
		std::cout << "�󶨳ɹ�" << std::endl;
	}
	//3listen ��������˿�.   listen(socket,���ȴ���)
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		std::cout << "ERROR,��������˿�ʧ��" << std::endl;
	}
	else
	{
		std::cout << "��������˿ڳɹ�" << std::endl;
	}
	//4�ȴ����տͻ�������
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(clientAddr);
	SOCKET _cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _cSock)
	{
		std::cout << "���յ���Ч�Ŀͻ���SOCKET" << std::endl;
	}
	//inet_ntoa:����ַ����תΪ�ַ���
	std::cout << "�¿ͻ��˼��룺IP:" << inet_ntoa(clientAddr.sin_addr) << std::endl;
	char _recvBuf[128] = {};
	while (true)
	{
		//���տͻ�������
		int nLen = recv(_cSock, _recvBuf, 128, 0);
		if (nLen <= 0)
		{
			printf("�ͻ������˳�");
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
		//5 send  ��ͻ��˷�������

	}

	//�ر� closesocket
	closesocket(_sock);


	WSACleanup();
	printf("���˳�");
	getchar();
	return 0;
}