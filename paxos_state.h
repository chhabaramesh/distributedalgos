class PaxosState {
	mutex_t lock;
	cv_t rpc_wait_cv;
	time_t timeout_msesc;
	
	typedef enum algo_state {
		UINIT = 0,
		STARTED = 1,
		WAITING_PROPOSALS = 2,
		WAITING_COMMITS = 3,
		DONE = 4
	} algo_state_t;

	struc node_state {
		shared_ptr<Node> node;
		weak_ptr<PaxosState> algo_state;
		proposal_res_t res;
	} node_state_t;

	vector<shared_ptr<node_state_t>> initial_nodes;
	vector<shared_ptr<node_state_t>> waiting_proposals;
	vector<shared_ptr<node_state_t>> failed_proposals;
	vector<shared_ptr<node_state_t>> accepted_proposals;;
	vector<shared_ptr<node_state_t>> waiting_commits;
	vector<shared_ptr<node_state_t>> committed;

public:
	PaxosState(time_t timeout);
	AddNode(shared_ptr<Node> node);
	SetMajority(int n);


	// do proposal rpc
	bool SendProposals(leader_info_t leader);

	// Wait for majrity of proposal rpcs to come back or timeout
	bool WaitMajorityAcceptedOrTimeout();

	// Get proposal winner info
	leader_info_t WinnerMajorityProposal();

	// send commit rpcs
	bool SendCommits(leader_info_t leader);

	// wait for majority of commits to return or timeout
	bool WaitMajorityCommitOrTimeout();

	// Wait for any pending rpc to timeout or drain
	bool WaitDrainOutTimeout();

	// Async rpc response collectors, must hold lock before operations
	bool proposalResponse();
	bool commitResponse();
};
