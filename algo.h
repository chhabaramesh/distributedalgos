#ifndef __ALGO_H__
#define __ALGO_H__
namespace Paxos {

class Algo {
	shared_ptr<Store> store;
	leader_info_t leader;
	
public:
	Algo(shared_ptr<Cluster> cluster, shared_ptr<Store> store)
	{
		this->cluster = cluster;
		this->store = store;

		// Set leader state as not elected
		this->leader.term = cluster->GetLeader().term + 1;
		this->leader.node_id = cluster->MyNodeID();
	}

	void IncrTerm();

	virtual bool DoElection();
	leader_info_t GetElectedLeader();
};

class Paxos: public Algo {
	shared_ptr<PaxosState> state;
public:
	bool DoElection();
};

} // end of namespace Paxos

#endif
