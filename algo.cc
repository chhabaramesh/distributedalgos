Also::doElection()
{
	for (node in this->cluster->nodes) {
		state->AddNode(shared_ptr<Node>);
	}

	state->SendProposals(leader_info);

	if (!state->WaitMajorityAcceptedOrTimeout()) {
		// accept failed to reach nodes
	}

	accepted = state->WinnerMajorityProposal();

	// Check for term
	if (our term much lesser than accepted) {
		// we need to break algo, our term much lesser
		return false;
	}

	state->SendCommits(accepted);

	if (!state->WaitMajorityCommitOrTimeout()) {
		// accept failed to reach nodes
	}

	this->leader = accepted;
	return true;
}
