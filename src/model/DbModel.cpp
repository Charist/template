#include "DbModel.h"

DbModel::~DbModel()
{

}

std::int64_t DbModel::getId() const
{
    return m_id;
}

void DbModel::setId(std::int64_t id)
{
    m_id = id;
}
