/*
 * Message.h
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

struct message {
	char op;
	int a;
	int b;
};

struct message msg;

void setOp(char value);
void setA(int value);
void setB(int value);
char getOp();
int getA();
int getB();


#endif /* MESSAGE_H_ */
