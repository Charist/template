#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

#include "DbManager.h"
#include "DbManagerImp.h"

#include "model/DbTestModel.h"

using namespace soci;

DbManager::DbManager()
{
    m_pImp = std::make_shared<DbManagerImp>();
}

DbManager::~DbManager()
{

}

std::int64_t DbManager::insert(std::shared_ptr<DbModel> pData)
{
    return m_pImp->insert(pData);
}

int main(int argc, char* argv[])
{    
    DbManager b;
    //b.createTable<DbTestModel>();

    std::shared_ptr<DbTestModel> a1 = std::make_shared<DbTestModel>(2, "wwwa1");
    b.insert(a1);

    std::vector<DbTestModel> ret;
    b.selectAll<DbTestModel>(ret);
    return 0;
}
