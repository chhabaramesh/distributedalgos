class Node {
	string name;
	string ip;
	string port;

	shared_ptr<RPCChannel> channel;

public:
	Node(string name, string ip, int port)
	string getName();
	string getIP();
	string getPort();

	string getRPCChannel();
};
