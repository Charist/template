#include "DbManager.h"
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

using namespace soci;

DbManager::DbManager()
{

}

DbManager::~DbManager()
{

}

std::int64_t DbManager::insert(DbModel *pData)
{
    soci::backend_factory const &backEnd = *soci::factory_sqlite3();
    soci::session sql(backEnd, "1.db");

    sql << "create table test1 ("
           "    id integer,"
           "    name varchar(100)"
           ")";

    sql << "insert into test1(id, name) values(7, \'John\')";

    rowid rid(sql);
    sql << "select oid from test1 where id = 7", into(rid);

    int id;
    std::string name;

    sql << "select id, name from test1 where oid = :rid",
        into(id), into(name), use(rid);

    sql << "drop table test1";
    return 0;
}


int main(int argc, char* argv[])
{    
    DbManager b;
    b.insert(nullptr);
    return 0;
}