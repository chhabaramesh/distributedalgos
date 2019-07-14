
// Global information about the leader in cluster
// this is only state as seen by acceptors.
// Proposars acts as proposer and acceptor same time and only its state
// as an acceptor is stored persistenly
#include <shared_mutex>
#include <node.h>
#include <leader.h>

namespace Paxos {
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
	std::mutex lock;

public:
	static string serialize();
	static Leader deserialize();

	GetState();
	SetState();
	leader_info_t GetLeader();
	SetLeader(leader_info_t leader);
	SetTerm(int term);
	int GetTerm();
};

class cluster {
	std::vector<shared_ptr<Node>> nodes;
	std::map<node_id_t, shared_ptr<Node>> node_id_map;
	shared_ptr<Node> current;
	std::mutex leader_lock;
	shared_ptr<LeaderInfo> leader;
	shared_mutex rw_lock;

public:
	void AddNode(shared_ptr<Node> node)
	void RemoveNode(shared_ptr<Node> node);
	vector<shared_ptr<Node>> GetNodeListLocked();
	void ReleaseNodeListLock();
	shared_ptr<Leader> GetLeader();
	void ReleaseLeader();
	shared_ptr<Leader> GetLeader();
	void SetLeader(shared_ptr<Leader> leader);
	bool IsLeaderAlive();
};

} // end of namespace paxos

