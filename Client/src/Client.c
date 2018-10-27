///*
// * client.c
// *
// *  Created on: 27 ott 2018
// *      Author: curci
// */
//
///*
// *	Progettare ed implementare un’applicazione TCP client/server, conforme al seguente protocollo applicativo:
//

#include <stdio.h>
#include <stdlib.h>
#if defined WIN32
#include <winsock.h>
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif

#include "Network.h"
#include "Message.h"

#define ADD 'A'
#define SOT 'S'
#define MOL 'M'
#define DIV 'D'
#define EQUI '='
#define EQU '$'

struct Message sceltautente() {
	char operazione = ' ';
	int x = 0, y = 0;
	do {
		fflush(stdin);
		printf(
				"Inserire l'operazione da eseguire usando i caratteri %c, %c, %c, %c,\n"
						"rispettivamente per Addizione, Moltiplicazione, Sottrazione e Divisione\n"
						"oppure il carattere %c per terminare: ", ADD, SOT, MOL, DIV, EQUI);
		scanf("%c", &operazione);
	} while (!(operazione == ADD || operazione == SOT || operazione == MOL
			|| operazione == DIV || operazione == EQUI));

	if (operazione != EQUI) {
		printf("Inserire il primo numero: ");
		scanf("%i", &x);
		int flag = 0;
		do {
			printf("Inserire il secondo numero: ");
			scanf("%i", &y);
			if (operazione == DIV && y == 0) {
				printf("Impossibile dividere per zero.\n");
				flag = 1;
			}
		} while (flag);
	}
	else
		operazione = EQU;
	return createMsg(operazione, htonl(x), htonl(y));
}

int main(int argc, char *argv[]) {

#if defined WIN32
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		printf("Error at WSAStartup()\n");
		return 0;
	}
#endif
	char ip[] = "192.168.3.199";
	int port = 4444;
	int descrSocket;
	// SETUP + CONNECTION
	descrSocket = setup(ip, port);

	while (1) {
		if (descrSocket > 0) {
			struct Message msgx = sceltautente();
			// COMMUNICATION
			int sizemsg = sizeof(msgx);
			if (send(descrSocket, &msgx, sizemsg, 0) != sizemsg) {
				printf("Errore qualcosa sulla stringa.\n");
				break;
			}
			printf("Messaggio inviato.\n");

			if (getOp() == EQU)
				break;
			int risultato;
			if (recv(descrSocket, &risultato, sizeof(risultato), 0) > 0)
				printf("Totale %i\n", ntohs(risultato));
			else
				printf("Errore nel buffer.(%i)\n", risultato);
		}
	}
	closesocket(descrSocket);
	clearWinSock();
	system("pause");
	return 0;
}
