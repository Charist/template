#pragma once
#include <string>
#include <vector>
#include "soci/soci.h"

#include "DbModelDefine.h"

class DbModelUtils
{
public:
    /**
     * @brief 通过类名称反射获得数据库属性列表
     *
     * @param class name. typeid(X).name()
     * @return: columns of table
     */
    static std::vector<TableFieldInfo> getTableFiledInfo(const std::string &className);

    /**
     *brief: 通过类名称反射获取数据表名字
     *
     *param: class name. typeid(X).name()
     *return: table name
     */
    static std::string getTableName(const std::string &className);
};

