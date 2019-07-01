#ifndef __ALGO_H__
#define __ALGO_H__

class Algo {
	shared_ptr<Store> store;
	shared_ptr<Leader> leader;
	
public:
	Algo(shared_ptr<Cluster> cluster, shared_ptr<Store> store)
	{
		this->cluster = cluster;
		this->store = store;
		this->leader.SetTerm(cluster->GetLeader().term + 1);
		this->leader.SetLeader(cluster->MyNodeID());
	}

	void IncrTerm();

	virtual DoElection();
	leader_info_t GetElectedLeader();
};

class Paxos: public Algo {
	shared_ptr<PaxosState> state;
public:
	bool DoElection();
};

#endif
