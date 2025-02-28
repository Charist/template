#include <rttr/registration>
#include "DbModelDefine.h"
#include "DbTestModel.h"

RTTR_REGISTRATION
{
    MODEL_FIELD_REGISTER(DbTestModel)

    FIELD_REGISTER(name, std::string, Indexed, "NOT NULL")
    FIELD_REGISTER(age, int)

    MODEL_FIELD_END_REGISTER
}
    

