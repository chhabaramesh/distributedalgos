namespace paxos {

PaxosState::PaxosState(int timeout)
{
	this->timeout = timeout;
	this->algo_state = INIT;
	this->majority = -1;
}

void
PaxosState::AddNode(shared_ptr<Node> node)
{
	std::lock_guard<std::mutex> lk(&this->lock);
	if (this->algo_state != INIT) {
		return false;
	}

	this->initial_nodes.push_back(new node_state(node, this))
	return true;
}

bool
PaxosState::SetMajority(int n)
{
	std::lock_guard<std::mutex> lk(&this->lock);
	if (this->algo_state != INIT) {
		return false;
	}

	this->majority = n;
	return true;
}

void
PaxosState::Init()
{
	// init phase over
	std::lock_guard<std::mutex> lk(&this->lock);
	this->algo_state = STARTED;
}

// Once this step is done the majority and nodes list becomes immutable
bool
PaxosState::SendProposals(leader_info_t info)
{
	std::lock_guard<std::mutex> lk(&this->lock);
	for (auto n: this->initial_nodes) {
		RPCChannel channel = n->node->GetRPCChannel();	
		if (channel->proposalRequest(info, n) == false) {
			this->failed_rpc_nodes.push_back(n);
		} else {
			this->waiting_proposals.push_back(n);
		}
	}

	this->initial_nodes.clear();
	this->algo_state = WAITING_PROPOSALS; 
}

bool
PaxosState::WaitMajorityAcceptedOrTimeout()
{
	std::lock_guard<std::mutex> lk(&this->lock);
	bool timedout = false;

	while (!timedout ||
			 this->accepted_proposals.size() < this->majority) {
		if (this->rpc_wait_cv.wait_until(&this->lock, this->timeout) == 
										std::cv_status::timeout) {
			timedout = true;
		}
	}

	this->algo_state = PROPOSALS_PHASE_OVER;; 
	if (this->accepted_proposals..size() < this->majority) {
		return false;	
	}

	return true;
}

proposal_res_t
PaxosState::WinnerMajorityProposal()
{
	leader_info_t leader;
	std::lock_guard<std::mutex> lk(&this->lock);

	proposal_res_t res(0); // least term number
	for (auto n: this->accepted_proposals) {
		if (n->res > res) {
			res = n->res;
		}	
	}

	return res;
}

bool
PaxosState::SendCommits(leader_info_t leader)
{
	std::lock_guard<std::mutex> lk(&this->lock);
	for (auto n: this->accepted_proposals) {
		RPCChannel channel = n->node->GetRPCChannel();	
		if (channel->commitRequest(leader, n) == false) {
			this->failed_rpc_nodes.push_back(n);
		} else {
			this->waiting_commits.push_back(n);
		}
	}

	this->accepted_proposals.clear();
	this->algo_state = WAITING_COMMITS;
}

bool
PaxosState::WaitMajorityCommitOrTimeout()
{
	std::lock_guard<std::mutex> lk(&this->lock);
	bool timedout = false;

	while (!timedout ||
			 this->committed.size() < this->majority) {
		if (this->rpc_wait_cv.wait_until(&this->lock, this->timeout) == 
										std::cv_status::timeout) {
			timedout = true;
		}
	}

	this->algo_state = DONE;; 
	if (this->committed.size() < this->majority) {
		return false;	
	}

	return true;
}

bool
PaxosState::WaitDrainoutOrTimeout()
{
	std::lock_guard<std::mutex> lk(&this->lock);
	this->rpc_wait_cv.wait_until(&this->lock, this->timeout);

	// Cancel all remaining rpcs
	for (auto n: this->waiting_proposals) {
		RPCChannel channel = n->node->GetRPCChannel();	
		channel->CancelRPC(n->rpc_handle);
	}

	for (auto n: this->waiting_commits) {
		RPCChannel channel = n->node->GetRPCChannel();	
		channel->CancelRPC(n->rpc_handle);
	}
}

bool 
PaxosState::ProposalResponse(shared_ptr<node_state_t> node_state)
{
	std::lock_guard<std::mutex> lk(&this->lock);

	this->waiting_proposals.remove(node_state);
	this->accepted_proposals.push_back(node_state);
	this->rpc_wait_cv.notify_all();
}

bool
PaxosState::CommitResponse(node_state_t *node_state)
{
	std::lock_guard<std::mutex> lk(&this->lock);
	this->waiting_commits.remove(node_state);
	this->committed.push_back(node_state);
	this->rpc_wait_cv.notify_all();
}

} // end namespace paxos
