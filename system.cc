#include <system.h>

namespace Paxos {
void
System::Init(bool init);
{
	if (init) {
		// formart store
		store->Reinit();
	}

	store->Open();
	cluster->Init(store, node_list);
}

void
System::random_sleep()
{
	sleep(std::srand() % this->random_backoff);
}

void 
System::Loop() 
{
	while (!this->Shutdown()) {
		// If there is leader and it is alive
		if (this->cluster->IsLeaderAlive()) {
			continue;
		}

		Algo algo(this->cluster, this->store);;
		algo.IncrTerm();

		if (algo.DoElection()) {
			// Election was over and successful
			// Set global leader
			auto leader = algo.GetElectedLeader();
			cluster->SetLeader(make_shared<Leader>(leader));
		}

		RandomSleep();
		// by this time either somebody would have been
		// selected or we will get better chance now
	}

}

static void
System::LeaderSetCallback(leader_info_t leader_info)
{
	// take cluster reader lock
	shared_ptr<System> sys = GetSystem();
	sys->cluster->rw_lock.lock_shared();

	// Do set leader process
	this->rw_lock.unlock_shared();
}


static void 
System::PingCallback()
{
	shared_ptr<System> sys = GetSystem();
	sys->cluster->rw_lock.lock_shared();

	// Do ping related things
	this->rw_lock.unlock_shared();

}

shared_ptr<System> 
GetSystem()
{
	return global_system;
}

void
InitSystem(string cluster_file, string store_file, bool reinit)
{
	// init cluster state from cluster file
	auto cluster = make_share<Cluster> ();
	cluster->Init()


	// init store from store file
	auto store = make_shared<Store>();
	if (reinit) {
		store->Reinit(store_file);
	}
	
	store->Open(store_file);
	
	// init global system state 
	shared_ptr<System> sys = make_shared<System>(nsecs, cluster, store);
	glogal_system = sys;
}

} // end of namespace Paxos


// Global state for this system
Paxos::shared_ptr<System> global_system; 

