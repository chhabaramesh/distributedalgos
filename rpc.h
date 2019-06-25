
// RPC channel to one node
class RPCChannel {
	weak_ptr<Node> node;

public:

	// RPC initiated from this node
	pingNodeRequest();
	proposalRequest();
	commitRequest();
	leaderInfo();


	// RPC received from node on other side
	proposalResponse();
	commitResponse();
	leaderInfoResponse();
};


