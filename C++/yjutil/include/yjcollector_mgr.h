#ifndef YJCOLLECTOR_MGR_H
#define YJCOLLECTOR_MGR_H

#include <vector>

namespace yjutil {
class CollectorMgr;
class Collector;

class CollectorMgr {
  public:
	CollectorMgr();
	~CollectorMgr();
    bool add(Collector* collector);
    bool del(Collector* collector);
    bool collect();
  public:
	std::vector<Collector*> m_collectorVec;
};  // class CollectorMgr
}  // namespace yjutil

#endif