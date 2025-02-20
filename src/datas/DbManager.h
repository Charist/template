#pragma once
#include "DBManagerGlobal.h"
#include <cstdint>
#include <memory>

class DbModel;
class DbManagerImp;

class DBMANAGER_EXPORT DbManager
{
public:
    DbManager();
    ~DbManager();

    template <class T> 
    bool createTable();

    std::int64_t insert(DbModel* pData);

private:
    std::shared_ptr<DbManagerImp> m_pImp;

};

template <class T>
bool DbManager::createTable()
{
    m_pImp->createTable<T>();
    return false;
}
