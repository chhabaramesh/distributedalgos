voidi
System::Init(bool init);
{
	if (init) {
		// formart store
		store->reinit();
	}

	store->open();
	cluster->init(store, node_list);
}

void 
System::Loop() 
{
	Algo algo;
	while (!shutdown) {
		// If there is leader and it is alive
		if (algo->pingNode(cluster->GetLeader()) {
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
