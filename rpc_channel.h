#ifndef __RPC_CHANNEL_H__
#define __RPC_CHANNEL_H__
#include <rpc_c.h>

// RPC channel to one node
class RPCChannel {
	weak_ptr<Node> node;
	rpc_client_handle_t client_handle;

public:

	// RPC initiated from this node
	leader_info_t PingRequest();
	bool SetLeaderInfo(leader_info_t);
	bool ProposalRequest(leader_info_t info, shared_ptr<node_state_t> node_state);
	bool CommitRequest(leader_info_t info, shared_ptr<node_state_t> node_state);
	bool CancelRPC(request_id_t);

	// static rpc handlers
	static void ProposalResponse(node_state_t *n_state);
	static void CommitResponse(node_state_t *n_state);
};

// end of file
#endif
