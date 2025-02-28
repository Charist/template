#pragma once
#include "soci/soci.h"
#include "TableFieldInfo.h"

constexpr const char *MODEL_TABLE_COLUMNS = "columns";
constexpr const char *MODEL_TABLE_NAME_STR = "table_name";
constexpr const char *MODEL_DATABASE_PATH_STR = "db_path";

constexpr const bool Indexed = true;
constexpr const bool None_Indexed = false;


template <class T>
constexpr soci::data_type SQLITE_TYPE_TRAIT()
{
    if (std::is_integral<T>::value)
    {
        return soci::data_type::dt_integer;
    }

    if (std::is_floating_point<T>::value)
    {
        return soci::data_type::dt_string;
    }

    if (std::is_same<T, std::string>::value)
    {
        return soci::data_type::dt_string;
    }

    return soci::data_type::dt_blob;
}

#define BEGIN_REGISTER_MODEL(Model) \
    rttr::registration::class_<Model> class_(typeid(Model).name());

#define END_REGISTER_MODEL

#define MODEL_TABLE_NAME(name) \
    class_.property_readonly(MODEL_TABLE_NAME_STR, []() -> std::string { return name; });

#define MODEL_DATABASE_PATH(path) \
    class_.property_readonly(MODEL_DATABASE_PATH_STR, []() -> std::string { return path; });

#define MODEL_FIELD_REGISTER(key)                               \
    rttr::registration::class_<key> class_(typeid(key).name()); \
    class_.property_readonly(MODEL_TABLE_COLUMNS, []() {                                                                           \
        return std::vector<TableFieldInfo> {

#define MODEL_FIELD_END_REGISTER \
    }                            \
    ;                            \
    });

#define MODEL_CLASS_NAME(type) \
    virtual std::string getClassName() const override { return typeid(type).name(); }

#define FIELD_REGISTER(key, type, ...) {#key, SQLITE_TYPE_TRAIT<type>(), ##__VA_ARGS__},

