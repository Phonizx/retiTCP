/*
 * Network.c
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */

#include "Network.h"

void clearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}

int serverSetup(int users, char* IPaddr) // -1 errore | 1 server in ascolto
{
	int socketListener = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketListener < 0) {
		printf("Errore nella creazione del socket.\n");
		clearWinSock();
		return -1;
	} else {
		struct sockaddr_in socketAddress;
		socketAddress.sin_family = AF_INET;
		socketAddress.sin_addr.s_addr = inet_addr(IPaddr);
		socketAddress.sin_port = htons(4444);
		if (bind(socketListener, (struct sockaddr*) &socketAddress,
				sizeof(socketAddress)) < 0) // bind ritorna 0 o -1
				{
			printf("Errore nel bind.\n");
			closesocket(socketListener);
			return -1;
		}
		if (listen(socketListener, users) < 0) {
			printf("Errore nel set listen.\n");
			closesocket(socketListener);
			return -1;
		} else {
			start(socketListener);
			return 1;
		}
	}
}

int start(int sock) {
	struct sockaddr_in clientAddress;
	int clientSock;
	int clientLen;
	while (1) {
		clientLen = sizeof(clientAddress);
		if ((clientSock = accept(sock, (struct sockaddr*) &clientAddress,
				&clientLen)) < 0) {
			printf("Errore nell'accettazione del client\n");
		} else {
			printf("Client connesso IP:%s\n",
					inet_ntoa(clientAddress.sin_addr));
			handleClientConnection(clientSock);
		}
	}

}

int handleClientConnection(int client) {
	printf("Gestendo Client connesso\n");
	return 1;
}

