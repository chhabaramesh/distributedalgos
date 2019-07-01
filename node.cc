namespace Paxos {

Node::Node(string name, string ip, int port)
{
	this->name = name;
	this->ip = ip;
	this->port = port;
}

string
Node::GetName()
{
	return this->name;
}

string
Node::GetIP()
{
	return this->ip;
}

int
Node::GetPort()
{
	return this->port;
}


shared_ptr<RPCChannel> 
Node::getRPCChannel()
{
	// check and initialize if neeeded and then return
	return this->channel;
}


} // end of namespace Paxos
