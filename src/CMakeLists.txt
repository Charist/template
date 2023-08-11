

option(BUILD_DATAS "enable build for datas" ON)
# option(BUILD_SERVER "enable build for io server" OFF)


# include_directories(
#     "${SCADA_RAPIDXML_INCLUDE_PATH}"
# )


if (BUILD_DATAS)
    add_subdirectory(datas)
endif()
