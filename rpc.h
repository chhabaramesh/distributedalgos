
// RPC channel to one node
class RPCChannel {
	weak_ptr<Node> node;
	rpc_client_handle_t cl;

public:

	// RPC initiated from this node
	leader_info_t pingNodeRequest();
	bool proposalRequest(leader_info_t info, node_state_t *n_state);
	bool commitRequest(leader_info_t, node_state_t *n_state);
	bool setLeaderInfo(leader_info_t, node_state_t *n_state);

	// static rpc handlers
	static proposalResponse(node_state_t *n_state);
	static commitResponse(node_state_t *n_state);
};
