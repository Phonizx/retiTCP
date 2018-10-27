/*
 * Operations.c
 *
 *  Created on: 27 ott 2018
 *      Author: phinkie
 */


#include "Operations.h"
#include "Message.h"


int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mult(int a, int b)
{
	return a * b;
}

int dive(int a,int b)
{
	if(b != 0)
		return a/b;
	return -1;
}














