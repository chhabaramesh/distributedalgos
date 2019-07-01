#include <rpc_c.h>

/// RPC State related functionality

rpc_info_t *
rpc_info_lookup(request_id_t req_id)
{
	return &rpc_list[req_id];
}

request_id_t
rpc_info_register(rpc_indo_t *info)
{
	request_it_t req_id = -1;
	// add this as one of the entries and return the index

	return res_id
}

void
rpc_info_cancel(request_id_t id)
{
	// erase entry for this id
	rpc_info[id] = NULL;
}


// Ping a remote node
ping_response_t
RPCPing(void)
{
	// Do rpc and return response
}

// Get current leader info from remote node
leader_info_t
RPCSetLeaderInfo(leader_info_t leader_info)
{
	// Do rpc and return response
}


// Proposal request and response
// Matched with unique request id parameter
bool
RPCProposalRequest(request_id_t req_id, proposal_req_t proposal)
{
	// Do rpc and return response
}

bool
RPCProposalResponse(request_id_t req_id, proposal_res_t res)
{
	// lock up request id
	// do required callback
	rpc_info_t &info = rpc_info_lookup[req_id];
	(info->callback)(rpc_info.callback_args);
}

// Commit request and response
// Matched with unique request id parameter
bool
RPCCommitRequest(request_id_t req_id, commit_req_t commit)
{
	// Do rpc and return response
}

bool
RPCCommitResponse(request_id_t req_id)
{
	// lock up request id
	// do required callback
	rpc_info_t &info = rpc_info_lookup[req_id];
	(info->callback)(rpc_info.callback_args);
}
