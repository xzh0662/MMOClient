/*
 * TcpServerTest.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: root
 */

#include "TcpServerTest.h"


TcpServerTest::TcpServerTest(void)
{

}

TcpServerTest::~TcpServerTest(void)
{

}

void TcpServerTest::handleClosed(int fd)
{
	super::handleClosed(fd);

	printf("TcpServerTest::handleClosed fd = %d\n", fd);
}

int TcpServerTest::receive(int fd, Buffer* buffer)
{
	if (super::receive(fd, buffer) != 0)
	{
		return -1;
	}

	int x = 0;
	std::string str;

	*buffer >> x >> str;

	printf("x = %d str = %s\n", x, str.c_str());

	return 0;
}
