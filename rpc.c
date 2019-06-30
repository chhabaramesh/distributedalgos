
bool 
RPCChannel::proposalRequest(leader_info_t info, node_state_t *n_state)
{
	// create req, req id and callback and call C RPC
	// callback = RPCChannel::proposalResponse
	// callback_args = n_state
	// rpc_info_register();
	// RPCProposalRequest();
}

static 
RPCChannel::proposalResponse(node_state_t *n_state)
{
	// from node state, build PAXOS algo state and register this response
}
