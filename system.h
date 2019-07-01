#ifdef __SYSTEM_H__
#define __SYSTEM_H__
namespace Paxos {
	class System {
		shared_ptr<Store> store;
		shared_ptr<Cluster> cluster;

		void init(bool init);
		void loop();
	};
} // end of namespace Paxos
#endif
