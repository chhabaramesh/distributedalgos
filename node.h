#ifndef __NODE_H__
#define __NODE_H__

namespace Paxos {

class Node {
	string name;
	string ip;
	string port;

	shared_ptr<RPCChannel> channel;

public:
	Node(string name, string ip, int port);
	string getName();
	string getIP();
	string getPort();

	shared_ptr<RPCChannel> getRPCChannel();
};

} // end of namespace paxos
#endif //__NODE_H__
