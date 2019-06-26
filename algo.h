class Algo {
	shared_ptr<Store> store;
	shared_ptr<Leader> leader_info;
	
public:
	Algo(shared_ptr<Cluster> cluster);
	getLeader();
	pingNode();
	pingLeader();
	virtual doElection();
	shared_ptr<Leader> GetElectedLeader();
};

class Paxos: public Algo {
	shared_ptr<PaxosState> state;
public:
	bool doElection();
};
