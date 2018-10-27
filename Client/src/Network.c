/*
 * Network.c
 *
 *  Created on: 27 ott 2018
 *      Author: curci
 */


#include "Network.h"

void clearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}

int setup(char* ip, int port)
{
	int socketServ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketServ < 0)	{
//		printf("Errore nella creazione del socket.\n");
		clearWinSock();
		return -1;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

	if(connect(socketServ, (struct sockaddr *) &serverAddr,	sizeof(serverAddr)) < 0)
	{
		printf("Errore connessione.\n");
		clearWinSock();
		return -1;
	}
	return socketServ;
}


