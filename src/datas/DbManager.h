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

    template <class T>
    void selectAll(std::vector<T>& ret);

    std::int64_t insert(std::shared_ptr<DbModel>);

private:
    std::shared_ptr<DbManagerImp> m_pImp;

};

template <class T>
bool DbManager::createTable()
{
    return m_pImp->createTable<T>();
}
template <class T>
void DbManager::selectAll(std::vector<T>& ret)
{
    m_pImp->selectAll<T>(ret);
}
