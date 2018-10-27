/*
 * Messsage.c
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */
#include "Message.h"

struct Message createMsg(char op, int x, int y)
{
	setOp(op);
	setA(x);
	setB(y);
	return msg;
}
void setOp(char value)
{
	msg.op = value;
}

void setA(int value)
{
	msg.a = value;
}

void setB(int value)
{
	msg.b = value;
}

char getOp()
{
	return msg.op;
}

int getA()
{
	return msg.a;
}

int getB()
{
	return msg.b;
}
