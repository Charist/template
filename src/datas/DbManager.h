#pragma once
#include "DBManagerGlobal.h"
#include <cstdint>

class DbModel;
class DBMANAGER_EXPORT DbManager
{
public:
    DbManager();
    ~DbManager();

    template <class T> 
    bool createTable();

    std::int64_t insert(DbModel* pData);


};

template <class T>
bool DbManager::createTable()
{
    return false;
}
