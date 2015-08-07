/*
 * TcpClientTest.h
 *
 *  Created on: Dec 15, 2014
 *      Author: root
 */

#ifndef TCPCLIENTTEST_H_
#define TCPCLIENTTEST_H_

#include "TcpClient.h"
#include "TcpConnectionTest.h"

class TcpClientTest: public TcpClient<TcpConnectionTest>
{
	typedef TcpClient<TcpConnectionTest> super;

public:

	TcpClientTest(void);

	~TcpClientTest(void);

	virtual int receive(int fd, Buffer *buffer);
	virtual void handleClosed(int fd);

};



#endif /* TCPCLIENTTEST_H_ */
