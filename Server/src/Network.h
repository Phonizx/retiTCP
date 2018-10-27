/*
 * Network.h
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */

#ifndef NETWORK_H_
#define NETWORK_H_

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

#include <stdio.h>
#include <stdlib.h>


void clearWinSock();
int serverListen(int);


#endif /* NETWORK_H_ */
