namespace Paxos
void 
Cluster::AddNode(shared_ptr<Node> node)
{
	this->rw_lock.lock();

	// check unique
	this->nodes.push_back(node);

	this->rw_lock.unlock();
}

void 
Cluster::RemoveNode(shared_ptr<Node> node)
{
	this->rw_lock.lock();

	this->nodes.remove(node);
	this->rw_lock.unlock();
}

vector<shared_ptr<Node>> 
Cluster::GetNodeListLocked()
{
	this->rw_lock.shared_lock();
	return this->nodes;
}

void
Cluster::ReleaseNodeListLock()
{
	this->rw_lock.shared_unlock();
}

shared_ptr<Leader> 
Cluster::GetLeader()
{
	this->rw_lock.shared_lock();
	return this->leader;
}

void
Cluster::ReleaseLeader()
{
	this->rw_lock.shared_unlock();
}

void 
Cluster::SetLeader(shared_ptr<Leader> leader)
{
	this->rw_lock.lock();
	this->leader.reset(leader);
	this->rw_lock.unlock();
}

bool
Cluster::IsLeaderAlive()
{
	this->rw_lock.shared_lock();

	// find out leader Node ptr from leader id
	leader_info_t  info = this->leader->GetLeader();
	auto node = this->node_id_map[info.node_id];t
	auto rpc = node->GetRPCChannel();
	leader_info_t ping_info = rpc->PingRequest();

	// check if leader info recieved is correct

	// do required adjustment in status and return 
	// result

	this->rw_lock.shared_unlock();
}

} // end of paxos namespace
