namespace Paxos {

leader_info_t
Algo::GetElectedLeader()
{
	this->leader_info;
}

void
Algo:IncrTerm()
{
	this->leader_info.term++;
}

Paxos::DoElection()
{
	// cluster read lock
	for (auto node : this->cluster->GetNodesList()) {
		state->AddNode(shared_ptr<Node>);
	}

	state->SendProposals(leader_info);

	if (!state->WaitMajorityAcceptedOrTimeout()) {
		// accept failed to reach nodes
		state->WaitDrainOutOrTimeout();
		return false;
	}

	accepted = state->WinnerMajorityProposal();

	// Check for winner term, clusing our own 
	if (accepted.term >= leader_info.term) {
		// if we got accept response with equal or higher term
		// There is another candidate, try to help him
		this->leader.node_id = accepted.node_id;		
	}

	state->SendCommits(accepted);

	if (!state->WaitMajorityCommitOrTimeout()) {
		state->WaitDrainOutOrTimeout();
		return false;
	}

	this->leader_info = accepted;
	state->WaitDrainOutOrTimeout();

	return true;
}

} // end of namespace paxos
