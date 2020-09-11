//避免一些早期的遗留定义与后期重定义问题
#define WIN32_LEAN_AND_MEAN

#include<WinSock2.h>

#include<windows.h>


//#pragma comment(lib,"ws2_32.lib")

int main()
{
	//启动windows socket 2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	//windows socket启用
	WSAStartup(ver, &dat);



	WSACleanup();

	return 0;
}