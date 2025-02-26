#pragma once
#include "model/DbModel.h"

#include "soci/soci.h"
#include <string>
class DbTestModel : public DbModel
{
public:
    DbTestModel(int age = -1, std::string name = "");
    virtual ~DbTestModel();

    virtual void insert(std::shared_ptr<soci::session> pSession) override;

    /*fields*/
    int getAge() const { return m_age; }
    void setAge(int val) { m_age = val; }
    std::string getName() const { return m_name; }
    void setName(std::string val) { m_name = val; }
private:
    int m_age = 0;
    std::string m_name;
};

