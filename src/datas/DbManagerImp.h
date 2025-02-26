#include "DbManagerImp.h"
#include <iostream>
#include <algorithm>

#include "spdlog/fmt/fmt.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"
#include "model/DbModelDefine.h"
#include "model/DbModelUtils.h"

#include "model/DbModel.h"
#include "model/DbTestModel.h"
//#include "model/TableFieldInfo.h"

DbManagerImp::DbManagerImp()
{
    m_pSession = std::make_shared<soci::session>(*soci::factory_sqlite3(), "test1.db");

	try
    {
        *m_pSession.get() << "PRAGMA journal_mode=WAL;";
	}
	catch (soci::sqlite3_soci_error const& e)
	{
        std::cout << e.what();
	}
    /* std::string s;
     *m_pSession.get() << "PRAGMA journal_mode;", soci::into(s);*/
}

DbManagerImp::~DbManagerImp()
{
    m_pSession->close();
}

std::int64_t DbManagerImp::insert(std::shared_ptr<DbModel> pData)
{
    long long iLastId = -1;
    try
    {
        // 尝试转换为子类 shared_ptr
        std::shared_ptr<DbTestModel> derived_ptr =
            std::dynamic_pointer_cast<DbTestModel>(pData);

        pData->insert(m_pSession);
        std::string class_name = typeid(*pData).name();
        std::string tableName = DbModelUtils::getTableName(class_name);
        m_pSession->get_last_insert_id(tableName, iLastId);

        pData->setId(iLastId);//update id
        std::cout << "row inserted in " + tableName + ", iLastId:" << iLastId << std::endl;//log
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();//log
    }
  
    return iLastId;
}

bool DbManagerImp::doCreateTable(const std::string& className)
{
    try
    {
        std::string table = DbModelUtils::getTableName(className);
        if (!isTableExist(table))
        {
            TableFieldInfo stInfo = { "id", soci::data_type::dt_integer, false, "PRIMARY KEY AUTOINCREMENT" };          

            std::vector<TableFieldInfo> columnInfos = DbModelUtils::getTableFiledInfo(className);
            columnInfos.insert(columnInfos.begin(), stInfo);

            return createTableWithColumns(table, columnInfos);
        }
        
    }
    catch (soci::sqlite3_soci_error& e)
    {
        std::cout << e.what();//log
        return false;
    }
    return true;
}

bool DbManagerImp::createTableWithColumns(const std::string& tabName, std::vector<TableFieldInfo>& cols)
{
    try
    {     
        {
            soci::ddl_type ddl = m_pSession->create_table(tabName);
            for (const TableFieldInfo& item : cols)
            {
                ddl.column(item.filedName, item.fieldType)(item.arbitrarySql);
            }
        } //作用域保证表创建完成，否则createIndex会有问题
        return createIndex(tabName, cols);
    }
    catch (soci::sqlite3_soci_error& e)
    {
        std::cout << e.what();//log
        return false;
    }
}


bool DbManagerImp::createIndex(const std::string& tabName, std::vector<TableFieldInfo>& cols)
{
    for (const TableFieldInfo& item : cols)
    {
        if (item.bIndex)
        {
            std::string sql;
            std::string indexName = fmt::format("index_{}_{}", tabName, item.filedName);
            sql = fmt::format("CREATE INDEX IF NOT EXISTS {0} ON {2}({1});", indexName, item.filedName, tabName);
            soci::statement stmt = m_pSession->prepare << sql;
            stmt.execute(true);
        }
    }
    return true;
}

bool DbManagerImp::alterTable(const std::string& className)
{
    try
    {
        std::string table = DbModelUtils::getTableName(className);
        std::vector<TableFieldInfo> columnInfos = DbModelUtils::getTableFiledInfo(className);

        std::map<std::string, TableFieldInfo> tableColMap;
        getTableFields(table, tableColMap);

        for (const TableFieldInfo& tInfo : columnInfos)
        {
            auto tmapItor = tableColMap.find(tInfo.filedName);
            if (tmapItor == tableColMap.end()) //field not exist
            {
                m_pSession->add_column(table, tInfo.filedName, tInfo.fieldType);
            }
            else
            {
                if (tmapItor->second.fieldType != tInfo.fieldType) //filed exist but type modified
                {
                    m_pSession->alter_column(table, tInfo.filedName, tInfo.fieldType);
                }
            }
        }
    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cout << e.what();//log
        return false;
    }
    return true;
}

bool DbManagerImp::isTableExist(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }
    std::vector<std::string> vecNames(100);
    std::vector<std::string>::iterator iter;

    m_pSession->get_table_names(), soci::into(vecNames);
    iter = std::find(vecNames.begin(), vecNames.end(), name);

    return iter != vecNames.end();
}

bool DbManagerImp::getTableFields(const std::string& tabName, std::map<std::string, TableFieldInfo>& ret)
{
    try
    {
        std::string sql = "select * from " + tabName + " limit 1";
        soci::statement st = m_pSession->prepare << sql;
        st.execute();
        soci::sqlite3_statement_backend* sqlite3statement = dynamic_cast<soci::sqlite3_statement_backend*>(st.get_backend());
        if (sqlite3statement != nullptr)
        {
            soci::sqlite3_column_info_list columns = sqlite3statement->columns_;
            std::for_each(columns.begin(), columns.end(), [&ret](const soci::sqlite3_column_info& item) {
                ret.emplace(std::make_pair(item.name_, TableFieldInfo(item.name_, item.type_)));
                });

        }

    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cout << e.what();//log
        return false;
    }
    return true;
}
