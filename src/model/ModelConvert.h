#pragma once

#include "model/DbTestModel.h"

namespace soci
{
    template<> struct type_conversion<DbTestModel>
    {
        typedef soci::values base_type;

        static void from_base(const base_type& in, indicator ind, DbTestModel& out)
        {
            out.setId(in.get<int>("id"));//若转int64_t console cout "bad cast",表结构中字段为int, 
            out.setName(in.get<std::string>("name"));
            out.setAge(in.get<int>("age"));
        }

        static void to_base(const DbTestModel& in, base_type& out, indicator& ind)
        {
            out.set("id", (int)in.getId());
            out.set("name", in.getName());
            out.set("age", in.getAge());
            ind = i_ok;
        }
    };
}
