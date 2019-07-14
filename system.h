#ifdef __SYSTEM_H__
#define __SYSTEM_H__
namespace Paxos {
	class System {
		shared_ptr<Store> store;
		shared_ptr<Cluster> cluster;

		void RandomSleep(int n);
		int backoff_limit;

public:

		System(int nsecs, 
				 shared_ptr<Store> store,
				 shared_ptr<Cluster> cluster,
		{
			this->random_backoff = nsecs;
			this->store = store;
			this->cluster = cluster;
		}

		bool Shutdown();
		void Loop();
		

		// Directly called from rpc layer
		static void LeaderSetCallback();
		static void PingCallback();
	};

	// Method for accessing singleton system
	shared_ptr<System> GetSystem();
	void InitSystem(string cluster_file);

} // end of namespace Paxos
#endif
