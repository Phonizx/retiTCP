
#include "Message.h"

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
