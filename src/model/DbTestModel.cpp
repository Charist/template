#include "model/DbTestModel.h"
#include <rttr/registration>

#include "DbModelDefine.h"
#include "model/DbModelUtils.h"
#include "model/ModelConvert.h"

RTTR_REGISTRATION
{
     BEGIN_REGISTER_MODEL(DbTestModel)
     MODEL_DATABASE_PATH("test2.db")
     MODEL_TABLE_NAME("labels")
     END_REGISTER_MODEL
}

DbTestModel::DbTestModel(int age, std::string name) : m_age(age), m_name(name)
{

}

DbTestModel::~DbTestModel()
{

}

void DbTestModel::insert(std::shared_ptr<soci::session> pSession)
{
    *pSession << "insert into labels(name, age) values(:name, :age)", soci::use(*this);

    DbTestModel person;
    *pSession << "select * from labels", soci::into(person);
}


