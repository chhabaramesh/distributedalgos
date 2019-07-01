
// Global information about the leader in cluster
// this is only state as seen by acceptors.
// Proposars acts as proposer and acceptor same time and only its state
// as an acceptor is stored persistenly

class Leader {
	// State of leader info at any node in cluster
	typedef enum {
		NOT_ELECTED = 0,
		ELECTION_PHASE_ACCEPTED = 1,
		ELECTION_PHASE_ELECTED = 2,
	} leader_state;	

	leader_state state;
	int term;
	node_id_t leader;

	// reader writer lock

public:
	static string serialize();
	static Leader deserialize();

	GetState();
	SetTerm(int term);
	GetState();
	SetLeader();
	GetLeader(node_id_t node);
};


class cluster {
	vector<shared_ptr<Node>> nodes;
	shared_ptr<Node> current;
	shared_ptr<LeaderInfo> leader;

public:
	void AddNode(shared_ptr<Node> node)
	void RemoveNode(shared_ptr<Node> node);
	vector<shared_ptr<Node>> GetNodeList();
	shared_ptr<Leader> GetLeader();
};

