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

			gotResponseList;
			// Start own election algorithm
			for (node in  nodes) {
				// send proposal number
				node->proposalRequest();
				awaitingResponse.add(node);
			}
			
			while (gotResponse < clusterMajority()) {
				// wait for rpc response
			}	

			// if we did not get majority votes
			// adjust the term number according to response
			// wait for random time, go to start


			// if we got majority, send commit to majority nodes

			// update leader info


			// send new leader info to all nodes

		}

	}

	



}
