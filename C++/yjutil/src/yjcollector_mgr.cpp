#include <algorithm>
#include "yjcollector_mgr.h"
#include "yjutil.h"
#include "yjcollector.h"

namespace yjutil {
CollectorMgr::CollectorMgr() {}

CollectorMgr::~CollectorMgr() {}

bool CollectorMgr::add(Collector *collector) {
    m_collectorVec.push_back(collector);
}

bool CollectorMgr::del(Collector *collector) {
    auto it = std::remove(m_collectorVec.begin(), m_collectorVec.end(), collector);
    if(it != m_collectorVec.end()) {
        m_collectorVec.erase(it, m_collectorVec.end());
        SAFE_DELETE(collector);
        return true;
    }
    return false;
}

bool CollectorMgr::collect() {
    std::for_each(m_collectorVec.begin(), m_collectorVec.end(), std::mem_fun(&Collector::doCollect));
    return true;
}

} // namespace yjutil
