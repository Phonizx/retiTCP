
#include "Network.h"
#include "Message.h"
#include "Operations.h"

void clearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}

int serverSetup(int users, char* IPaddr) // -1 errore | 1 server in ascolto
{
	int socketListener = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketListener < 0) {
		printf("Socket creation error\n");
		clearWinSock();
		return -1;
	} else {
		struct sockaddr_in socketAddress;
		socketAddress.sin_family = AF_INET;
		socketAddress.sin_addr.s_addr = inet_addr(IPaddr);
		socketAddress.sin_port = htons(4444);
		if (bind(socketListener, (struct sockaddr*) &socketAddress, sizeof(socketAddress)) < 0) // bind ritorna 0 o -1
		{
			printf("Server Error\n");
			closesocket(socketListener);
			return -1;
		}
		if (listen(socketListener, users) < 0) {
			printf("Server Error.\n");
			closesocket(socketListener);
			return -1;
		} else {
			printf("Listening on port: %d ...\n", htons(socketAddress.sin_port));
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
			printf("Error in establishing a connection with: %s:%d\n",
					inet_ntoa(clientAddress.sin_addr),ntohs(clientAddress.sin_port));
		} else {
			printf("Connection established with %s:%d\n",
					inet_ntoa(clientAddress.sin_addr),ntohs(clientAddress.sin_port));
			handleClientConnection(clientSock);
		}
	}

}

int handleClientConnection(int client) {
	int result = 0;
	int exit = 0;
	while(1)
	{
		int msgTmp = recv(client,&msg,sizeof(msg),0);
		if(msgTmp > 0)
		{
			setOp((msg.op));
			setA(ntohl(msg.a));
			setB(ntohl(msg.b));
			int a = getA();
			int b = getB();
			switch(msg.op)
			{
				case 'A':
					printf("Required operation: %d + %d\n",a,b);
					result = add(a,b);
					break;
				case 'S':
					printf("Required operation: %d - %d\n",a,b);
					result = sub(a,b);
					break;
				case 'M':
					printf("Required operation: %d * %d\n",a,b);
					result = mult(a,b);
					break;
				case 'D':
					printf("Required operation: %d / %d\n",a,b);
					result = dive(a,b);
					break;
				case '$':
					printf("Client Disconnection...\n");
					exit = 1;
					break;
			}

			if(result > 0)
			{
				result = htons(result);
				send(client, &result, sizeof(result), 0 );
				printf("Result sent: %d\n",htons(result)); // warning
				result = 0;
			}
			if(exit == 1)
			{
				closesocket(client);
				break;
			}
		}
	}
	return 1;
}

