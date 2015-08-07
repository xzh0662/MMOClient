/*
 * TcpClientTest.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: root
 */

#include "TcpClientTest.h"

TcpClientTest::TcpClientTest(void)
{

}

TcpClientTest::~TcpClientTest(void)
{
	printf("~TcpClientTest\n");
}

int TcpClientTest::receive(int fd, Buffer *buffer)
{
	if (super::receive(fd, buffer) != 0)
	{
		return -1;
	}
//
//	int x = 0;
//	std::string str;
	printf("fd = %d len=%d\n", fd, buffer->Length());

//	*buffer >> x >> str;
//
//	printf("TcpClientTest::receive x = %d str = %s\n", x, str.c_str());
//
//	{
//		 Buffer *buffer = new Buffer();
//
//		 *buffer << x << str;
//
//		 this->send(fd, buffer);
//	}

	return 0;
}

void TcpClientTest::handleClosed(int fd)
{
	super::handleClosed(fd);

	printf("TcpClientTest::handleClosed fd = %d\n", fd);
}

