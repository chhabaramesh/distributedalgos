// All communication is async, every request response broken in to two RPCS, request and response

// State machine during leader election
// A global list of nodes and thier respective states with a unique id is store in global list
// the main code that initiates RPC for leader election will add nodes to this list
// If this is not leader election stage, only one node in the list, the current leader to get ping response
// If in leader election, all nodes to which RPC has been sent are part of this list
// The response to RPCs or intial RPC triggered by another node is async and when response comes it can be:
// a. A ping from another machine, we simply return the response.
// b. A leader info from other node, we simply accept it, as it is already elected
// c. Voting request or commit request
// to all these rpcs, we try to send response asap from same thread context.
// when we are expecting an async response to rpc we sent earlier, there will be a entry in out global list to 
// change state for that node in our state machine.


// Threading model
// a. One main thread who is running the loop
// b. one or multiple threads who are waiting for RPC and process rpcs when those come
// c. A thread who is dealing with timeout of the RPC response




class System {

	void init(bool init)
	{
		if (init) {
			// formart store
			store->reinit();
		}

		store->open();
		cluster->init(store, node_list);
	}

	void loop() 
	{
		Algo algo;
		while (!shutdown) {
			// If there is leader and it is alive
			if (algo->pingNode(cluster->pingLeader()) {
				continue;
			}

			algo.incr_term();
			algo.init(cluster);
			if (algo.doElection()) {
				// Election was over and successful
				// Set global leader
				Leader leader = algo.GetElectedLeader();
			}

			random_backoff(0 to n msecs);
			// by this time either somebody would have been
			// selected or we will get better chance now
		}

	}
}
