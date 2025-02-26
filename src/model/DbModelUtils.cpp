#include "DbModelUtils.h"
#include "rttr/type.h"
#include "rttr/instance.h"
#include "DbModelDefine.h"

std::vector<TableFieldInfo> DbModelUtils::getTableFiledInfo(const std::string& className)
{
    auto type = rttr::type::get_by_name(className);

    if (!type.is_valid())
    {
        //IDE_LOG_ERROR("No registered model class {}", className);
        return std::vector<TableFieldInfo>();
    }

    auto var = type.get_property_value(MODEL_TABLE_NAME_STR, rttr::instance(nullptr));
    auto theMap = type.get_property_value(MODEL_TABLE_COLUMNS, rttr::instance(nullptr));

    std::string tableName;

    if (!var.convert(tableName))
    {
        //IDE_LOG_ERROR("Unable to get data table name for model {}", className);
        return std::vector<TableFieldInfo>();
    }

    if (!theMap.is_sequential_container())
    {
        //IDE_LOG_ERROR("Unable to get columns for model {}", className);
        return std::vector<TableFieldInfo>();
    }

    auto view = theMap.create_sequential_view();
    std::vector<TableFieldInfo> result;

    for (auto& info : view) 
    {
        result.push_back(info.convert<TableFieldInfo>());
    }

    return result;

}

std::string DbModelUtils::getTableName(const std::string& className)
{
    auto type = rttr::type::get_by_name(className);
    if (!type.is_valid())
    {
        //log
        return "";
    }
    std::string tableName;
    auto var = type.get_property_value(MODEL_TABLE_NAME_STR, rttr::instance(nullptr));//must have seconde parm.
    if (!var.convert(tableName))
    {
        //log error
    }
    return tableName;
}

