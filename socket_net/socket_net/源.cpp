//����һЩ���ڵ���������������ض�������
#define WIN32_LEAN_AND_MEAN

#include<WinSock2.h>

#include<windows.h>


//#pragma comment(lib,"ws2_32.lib")

int main()
{
	//����windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket����
	WSAStartup(ver, &dat);



	WSACleanup();

	return 0;
}