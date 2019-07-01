#include <rpc_c.h>
namespace Paxos {

leader_info_t
RPCChannel::PingRequest()
{
	return RPCPing(this->client_handle);
}

bool
RPCChannel::SetLeaderInfo(leader_info_t leader)
{
	return RPCSetLeaderInfo(leader, this->client_handle);
}

bool 
RPCChannel::ProposalRequest(leader_info_t info, shared_ptr<node_state_t> node_state)
{
	rpc_info_t rpc_info;
	rpc_info.callback = RPCChannel::ProposalResponse;
	rpc_info.callback_args = (void *) node_state().get();

	resuest_id_t req_id = rpc_info_register(rpc_info);
	node_state->rpc_handle = req_id;
	
	if (RPCProposalRequest(info, this->client_handle) != RPC_SUCCESS) {
		return false;
	}

	return true;
}

static void
RPCChannel::ProposalResponse(node_state_t *node_state)
{
	shared_ptr<node_state> node;
	shared_ptr<PaxosState> algo_state;

	node.reset(node_state);
	algo.state.reset(node->algo_state);

	algo_state->ProposalResponse(node);
}

bool 
RPCChannel::CommitRequest(leader_info_t info, shared_ptr<node_state_t> node_state)
{
	rpc_info_t rpc_info;
	rpc_info.callback = RPCChannel::CommitResponse;
	rpc_info.callback_args = (void *) node_state().get();
	resuest_id_t req_id = rpc_info_register(rpc_info);
	node_state->rpc_handle = req_id;
	
	if (RPCCommitRequest(info, this->client_handle) != RPC_SUCCESS) {
		return false;
	}

	return true;
}

static void 
RPCChannel::CommitResponse(node_state_t *node_state)
{
	shared_ptr<node_state> node;
	shared_ptr<PaxosState> algo_state;

	node.reset(node_state);
	algo.state.reset(node->algo_state);

	algo_state->CommitResponse(node);
}

bool
RPCChannel::CancelRPC(request_id_t req_id)
{
	rpc_info_cancel(req_id);
}

} // end of namespace Paxos
