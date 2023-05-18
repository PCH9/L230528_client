#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <Winsock2.h>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

#pragma pack(1)
typedef struct _Packet
{
	char Code;
	short Number1;
	short Number2;

} Packet;
#pragma pack(pop)

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSockAddr;
	ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = 9090;

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	srand((unsigned int)time(nullptr));

	while (1)
	{
		short Number1 = (rand() % 10000);
		short Number2 = (rand() % 10000);

		//char Packet[5];

		Packet MyPacket;
		MyPacket.Code = rand() % 4;
		MyPacket.Number1 = Number1;
		MyPacket.Number2 = Number2;


		//memcpy(&Packet[0], &Number1, 2);
		//Packet[0] = ((char*)&Number1)[0];
		//Packet[1] = ((char*)&Number1)[1];
		//Packet[2] = rand() % 4;
		//memcpy(&Packet[3], &Number2, 2);
		//Packet[3] = ((char*)&Number2)[0];
		//Packet[4] = ((char*)&Number2)[1];


		char Message[1024] = { 0, };
		char OperatorMark[4] = { '+', '-', '*', '/' };

		int SentLength = send(ServerSocket, (char*)&MyPacket, 5, 0);

		char Buffer[1024] = { 0, };
		int RecvLength = recv(ServerSocket, Buffer, 4, 0);

		int Result = 0;
		((char*)&Result)[0] = Buffer[0];
		((char*)&Result)[1] = Buffer[1];
		((char*)&Result)[2] = Buffer[2];
		((char*)&Result)[3] = Buffer[3];

		cout << Number1 << OperatorMark[MyPacket.Code] << Number2 << "=" << Result << endl;
	}


	closesocket(ServerSocket);


	WSACleanup();

	return 0;
}