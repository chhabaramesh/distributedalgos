#ifndef __PAXOS_STATE_H__
#define  __PAXOS_STATE_H__
// start of file

#include <mutex>
#include <condition_variable> 
#include <list> 

namespace paxos {

struct node_state {
	shared_ptr<Node> node;
	weak_ptr<PaxosState> algo_state;
	request_id_t rpc_handle;
	proposal_res_t res;

	node_state(shared_ptr<Node> node)
	{
		this->node = node;
		this->rpc_handle = -1;
	}

};

typedef std::condition_variable cv_t;

class PaxosState {
	std::mutex lock;
	cv_t rpc_wait_cv;
	int timeout_msesc;
	
	enum algo_state {
		INIT = 0,
		STARTED = 1,
		WAITING_PROPOSALS,
		PROPOSALS_PHASE_OVER,
		WAITING_COMMITS,
		DONE = 5
	} algo_state;

	list<shared_ptr<node_state_t>> initial_nodes;
	list<shared_ptr<node_state_t>> waiting_proposals;
	list<shared_ptr<node_state_t>> failed_rpc_nodes;
	list<shared_ptr<node_state_t>> accepted_proposals;;
	list<shared_ptr<node_state_t>> waiting_commits;
	list<shared_ptr<node_state_t>> committed;

public:
	PaxosState(time_t timeout);
	bool AddNode(shared_ptr<Node> node);
	bool SetMajority(int n);


	// do proposal rpc
	bool SendProposals(leader_info_t leader);

	// Wait for majrity of proposal rpcs to come back or timeout
	bool WaitMajorityAcceptedOrTimeout();

	// Get proposal winner info
	proposal_res_t WinnerMajorityProposal();

	// send commit rpcs
	bool SendCommits(leader_info_t leader);

	// wait for majority of commits to return or timeout
	bool WaitMajorityCommitOrTimeout();

	// Wait for any pending rpc to timeout or drain
	bool WaitDrainOutTimeout();

	// Async rpc response collectors, must hold lock before operations
	bool ProposalResponse();
	bool CommitResponse();
};

} // namespace end
//end of file
