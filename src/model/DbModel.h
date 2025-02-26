#pragma once
#include <cstdint>
#include "soci/soci.h"
#include "DBManagerGlobal.h"

class DBMANAGER_EXPORT DbModel
{
public:
    DbModel() {}
    virtual ~DbModel() = 0;
    virtual void insert(std::shared_ptr<soci::session> pSession) = 0;

    std::int64_t getId() const;
    void setId(std::int64_t id);

protected:
    std::int64_t m_id = -1;
};
