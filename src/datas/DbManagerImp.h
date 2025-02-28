#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include "model/DbModelUtils.h"
#include "model/ModelConvert.h"

class DbModel;
class soci::session;

class DbManagerImp
{
public:
    DbManagerImp();
    virtual ~DbManagerImp();

    template <class T>
    bool createTable();


    template <class T>
    bool selectAll(std::vector<T>& ret);

    std::int64_t insert(std::shared_ptr<DbModel> pData);
    
private:
    bool doCreateTable(const std::string& className);
    bool createTableWithColumns(const std::string& tabName, std::vector<TableFieldInfo>& cols);
    bool createIndex(const std::string& tabName, std::vector<TableFieldInfo>& cols);

    bool alterTable(const std::string &className);

    bool isTableExist(const std::string &name);


    bool getTableFields(const std::string &tabName, std::map<std::string, TableFieldInfo>& ret);

private:
    std::shared_ptr<soci::session> m_pSession;
};


template <class T>
bool DbManagerImp::createTable()
{
    std::string class_name = typeid(T).name();
    doCreateTable(class_name);

    alterTable(class_name);
    return true;
}

template <class T>
bool DbManagerImp::selectAll(std::vector<T>& ret)
{
    ret.clear();
    try
    {
        std::string class_name = typeid(T).name();
        std::string table = DbModelUtils::getTableName(class_name);
        soci::rowset<T> rs = (m_pSession->prepare << "select * from " + table);
        for (soci::rowset<T>::iterator it = rs.begin(); it != rs.end(); ++it)
        {
            ret.emplace_back(*it);
        }
    }
    catch (soci::sqlite3_soci_error& e)
    {

        std::cout << e.what();//log
        return false;
    }
    return true;
}
