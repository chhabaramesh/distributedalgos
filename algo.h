class Algo {
	shared_ptr<Store> store;
	
public:
	Algo(shared_ptr<Cluster> cluster);
	getLeader();
	pingNode();
	pingLeader();
	virtual doElection();
};

class Paxos: public Algo {
public:
	doElection();
};
