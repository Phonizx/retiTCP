/*
 * Network.c
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */

#include "Network.h"


void clearWinSock()
{
#if defined WIN32
	WSACleanup();
#endif
}


int serverListen(int users) // -1 errore | 1 server in ascolto
{
	int socketListener = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socketListener < 0)
	{
		printf("Errore nella creazione del socket");
		clearWinSock();
		return -1;
	}
	else
	{
		struct sockaddr_in socketAddress;
		socketAddress.sin_family = AF_INET;
		socketAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
		socketAddress.sin_port = htons(4444);
		if(bind(socketListener,(struct sockaddr*) &socketAddress, sizeof(socketAddress)<0)) // bind ritorna 0 o -1
		{
			printf("Errore");
			closesocket(socketListener);
			return -1;
		}
		if(listen(socketListener,users) < 0)
		{
			closesocket(socketListener);
			return -1;
		}
		else
			return 1;
	}
}

