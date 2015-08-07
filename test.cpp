/*
 * test.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: root
 */

#include <event2/event.h>
#include "TcpClientTest.h"
#include "InetAddr.h"
#include "BaseTimer.h"
#include "TcpServerTest.h"
#include <pthread.h>
#include <event2/thread.h>
#include "BlockingQueue.h"
#include <string>
#include "GlobalInfo.h"
#include "ThreadMonitor.h"
#include "Buffer.h"
#include "LogClient.h"
#include "SSTNetProtocol.h"


void eventCallback(int fd, short which, void *arg)
{
	event_base *base = (event_base*)arg;
	event_base_loopexit(base, NULL);

	printf("stop eventCallback\n");
}

int main()
{
	GlobalInfo::useThreads();

	GlobalInfo::print();

	struct event_base *base = event_base_new();

	event *ev = evsignal_new(base, 2, eventCallback, (void* )base);
	if (!ev || event_add(ev, NULL) < 0)
	{
		event_del(ev);
		return false;
	}

	InetAddr serverAddr(5000);
//	InetAddr serverAddr("192.168.0.153", 5000);

	TcpClientTest client;
	//client.eventBase(base);
//	clinet
	client.init(0, 0, 1);
	client.start();

//	BaseTimer timer;
//	timer.event_base(client.eventBase());
//	timer.scheduleTimer(1, 0);

	client.connect(serverAddr);

	Buffer *buf, *tmp;
	BUFFER_NEW_RETURN(buf, BUFFER_NORMAL_SIZE, -1);
	BUFFER_NEW_RETURN(tmp, BUFFER_NORMAL_SIZE, -1);

//	struct NetPacketHeader
//	{
//	public:
//		static const unsigned int NetPacketHeaderIdent = 0xAA8899BB;
//		static const unsigned int NetLPacketHeaderIdent = 0xAA8899DD;
//
//		unsigned int  dwIdent;//数据包包头标志，固定为NetPacketHeaderIdent
//		unsigned short wPacketSize;//数据包长度（不含此包头）
//		unsigned short wVerification;//数据效验值，仅客户端向服务器发送的数据包包头中包含对数据段的效验。
//
//	};
//	struct ClientNetPacketHeader : public NetPacketHeader
//	{
//		static const unsigned long ClientNetPacketHeaderIdent = 0xAA8899BC;
//
//		unsigned int dwPacketIndex;//累积数据包索引，客户端每次发送数据包后必须增加此值，服务器检测到此值不比上一次的值大则做丢弃
//	};

	char data[6] = {0};
	unsigned int idnt = (unsigned int)0xAA8899BC;

	unsigned int index = tdzm::encrpytPacketIndex(1, 0, 6);
	//unsigned int dindex = tdzm::encrpytPacketIndex(index, 0, 6);
	unsigned short wVerification = tdzm::calcPacketDataVerify(data, 6, 0);
	*buf << (unsigned int)idnt  << (short)6 << (short)wVerification << (unsigned int)index ;



	tdzm::encryptClientPacket(data, 6, 1);
	//tdzm::decryptClientPacket(data, 6, 0);

	buf->addData(data, 6);

	client.send(-1, buf);

	event_base_dispatch(base);

	event_base_free(base);

	client.stop();
	client.final();

	printf("end of client\n");

	return 0;
}

