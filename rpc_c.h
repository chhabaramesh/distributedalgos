#ifndef __RPC_C_H__
#define __RPC_C_H__

typedef proposal_req {
	term_num_t term;
	node_id_t node;
} proposal_req_t;

typedef proposal_req_t commit_req_t;
typedef proposal_req_t proposal_res_t;
typedef proposal_req_t leader_info_t;
typedef leader_info_t ping_response_t;

typedef struct rpc_info {
	callback_t callback;
	callback_args_t *callback_args;
} rpc_info_t;

tyepdef rpc_list {
	rpc_info_t *rpc_map;
	int count;
}

// find rpc_info for req id
rpc_info_t *
rpc_info_lookup(request_id_t req_id);

// register a new async rpc response handler
request_id_t
rpc_info_register(rpc_indo_t *info);


// Cancel a pending rpc
void
rpc_info_cancel(request_id_t id);

// Sync rpc

// Ping a remote node
ping_response_t
RPCPing(void);

// Get current leader info from remote node
leader_info_t
RPCSetLeaderInfo(leader_info_t leader_info);

// Proposal request and response
// Matched with unique request id parameter
bool
RPCProposalRequest(request_id_t req_id, proposal_req_t proposal);

bool
RPCProposalResponse(request_id_t req_id, proposal_res_t res); 

// Commit request and response
// Matched with unique request id parameter
bool
RPCCommitRequest(request_id_t req_id, commit_req_t commit);

bool
RPCCommitResponse(request_id_t req_id);

// end of file
#endif




