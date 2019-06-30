typedef proposal_req {
	term_num_t term;
	node_id_t node;
} proposal_req_t;

typedef proposal_req_t commit_req_t;
typedef proposal_req_t proposal_res_t;
typedef proposal_req_t leader_info_t;
typedef leader_info_t ping_response_t;

typedef struct rpc_info {
	request_id_t req_id;
	callback_t callback;
	callback_args_t *callback_args;
} rpc_info_t;

tyepdef rpc_list {
	rpc_info_t *rpc_map;
	int count;
}

rpc_info_t *
rpc_info_lookup(request_id_t req_id)
{
	return &rpc_list[req_id];
}

request_id_t
rpc_info_register(rpc_indo_t *info);

// Sync rpc

// Ping a remote node
ping_response_t
RPC_ping(void);


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

/*
	Test cases
	----------

	1. All rpcs are working from two different process on same machine and different machines.
	2. If server or client are not rechable, rpc times out with proper error.
	3. If server connections fluctuates, rpc connection statys alive 

*/



