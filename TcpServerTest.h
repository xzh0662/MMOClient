/*
 * TcpServerTest.h
 *
 *  Created on: Dec 17, 2014
 *      Author: root
 */

#ifndef TCPSERVERTEST_H_
#define TCPSERVERTEST_H_

#include "TcpServer.h"
#include "TcpConnectionTest.h"

class TcpServerTest : public TcpServer<TcpConnectionTest>
{
public:
	typedef TcpServer<TcpConnectionTest> super;

	TcpServerTest(void);

	virtual ~TcpServerTest(void);

	virtual void handleClosed(int fd);

	virtual int receive(int fd, Buffer* buffer);

};



#endif /* TCPSERVERTEST_H_ */
