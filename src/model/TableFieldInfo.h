#pragma once
#include "soci/soci.h"

struct TableFieldInfo
{
    std::string filedName;
    soci::data_type fieldType = soci::dt_string;
    bool bIndex = false;      // 是否为数据库索引
    std::string arbitrarySql; // 任意字段附加信息

    TableFieldInfo() {}
    TableFieldInfo(const std::string fName, soci::data_type fType, bool index = false, std::string sql = "") :
        filedName(fName), fieldType(fType), bIndex(index), arbitrarySql(sql)
    {}

    bool operator == (const TableFieldInfo& other) const
    {
        return (filedName == other.filedName &&
            fieldType == other.fieldType &&
            bIndex == other.bIndex &&
            arbitrarySql == other.arbitrarySql);
    }
};

