# template
环境：VS2019, cmake 3.24.0, Qt 5.14.2 

# 工程构建
```
    cmake . -G "Visual Studio 16 2019" -B build
```

# 3rdparty 说明
## 1. sqlite3

### 1.1 库编译
编译sqlite3, 下载融合版本进行编译，camke编译出 __静态库__


    
[参考](https://www.cnblogs.com/nuoforever/p/14846453.html#:~:text=SQLITE_ENABLE_FTS3%203%29.C%2FC%2B%2B-%3E%E4%BB%A3%E7%A0%81%E7%94%9F%E6%88%90-%3E%E8%BF%90%E8%A1%8C%E5%BA%93%3A%E5%A4%9A%E7%BA%BF%E7%A8%8B%2FMDd%204%29.%E9%93%BE%E6%8E%A5%E5%99%A8-%3E%E8%BE%93%E5%85%A5-%3E%E6%A8%A1%E5%9D%97%E5%AE%9A%E4%B9%89%E6%96%87%E4%BB%B6%3Asqlite3.def,5%29.%E9%93%BE%E6%8E%A5%E5%99%A8-%3E%E9%AB%98%E7%BA%A7-%3E%E5%AF%BC%E5%85%A5%E5%BA%93%EF%BC%9A%24%20%28OutDir%29%24%20%28ProjectName%29.lib%206%29.%E6%89%93%E5%BC%80def%E6%96%87%E4%BB%B6%EF%BC%8C%E5%A2%9E%E5%8A%A0sqlite3_unlock_notify)

### 1.2 引用库的 cmake 配置
    3rdparty 的cmake中，对gtest相关库进行配置：
```
add_library(sqlite3 STATIC IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/sqlite3" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/sqlite3.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/sqlite3.lib"
)

```
### 1.3 sqlite3 库使用
   test工程中引入了sqlite3，cmake 文件中添加连接引用即可

```
    target_link_libraries(unit_tests
        sqlite3)
```

## 2. googletest
### 2.1 库编译
   可通过直接使用源码形式把googletest引入到使用工程中, 但这样构建的工程会有gtest工程。所以还是选择单独编译gtest,然后引用静态库方式使用。
编译直接进入googletest 目录，执行`cmake . -G "Visual Studio 16 2019" -B build` 即可生产。然后把生产的lib文件放入lib文件夹下, 默认构建出来的为**静态库**。

### 2.2 引用库的 cmake 配置
    3rdparty 的cmake中，对gtest相关库进行配置：
```
    add_library(gtest STATIC IMPORTED GLOBAL)
    set_target_properties(gtest PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTEST_PATH}/googletest/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/gtestd.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/gtest.lib")

```
   引入gtest,cmake 构建提示警告 `Policy CMP0111 is not set: An imported target missing its location property`,
   可通过设置 `cmake_policy(SET CMP0111 OLD)` 解决
### 2.3 gtest 库使用
    test工程中进行了gtest使用，cmake 文件中添加连接引用即可

```
    target_link_libraries(unit_tests
        gtest 
        gtest_main)
```

### 2.4 gtest 帮助
[googltest help](https://google.github.io/googletest/primer.html)

## 3. rttr
### 3.1 库编译
### 3.2 引用库的 cmake 配置
### 3.2 rttr 库使用

## 4. soci
### 4.1 库编译
参考 `soci\docs\installation.md`、 `soci\scripts\build.bat`相关信息，编译出支持sqlite3 的版本：

```
cmake . -G "Visual Studio 16 2019" -B build -DWITH_SQLITE3=ON -DSQLITE3_INCLUDE_DIR="../sqlite3" -DSQLITE3_LIBRARY="../../lib/x64/release/sqlite3.lib"

```
编译出来的lib库 debug、release 是一样的；dll 库debug、release不一样。默认构建出来的为**动态库**。将`soci_core_4_1.lib`、`soci_sqlite3_4_1.lib` 库拷贝至主目录lib文件夹下；将dll拷贝至主目录bin目录下。
拷贝`soci\build\include\soci\soci-config.h` 文件到 `soci\include\soci\soci-config.h`，此文件会在头文件中被引用到。

扩展：

### 4.2 引用库的 cmake 配置
3rdparty 的cmake中，添加相关进行配置：
扩展下：
`add_library`库的类型是STATIC(静态库)/SHARED(动态库)/MODULE(模块库)之一。

1. 添加静态库方式：
```
add_library(soci_core STATIC  IMPORTED GLOBAL)
set_target_properties(soci_core PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/soci/include" 
    IMPORTED_LOCATION_DEBUG "${3RDPARTY_LIB_PATH}/debug/soci_core_4_1.lib"
    IMPORTED_LOCATION_RELEASE "${3RDPARTY_LIB_PATH}/release/soci_core_4_1.lib"
)

```
2. 添加动态库方式：
```
add_library(soci_core SHARED  IMPORTED GLOBAL)
set_property(TARGET soci_core PROPERTY IMPORTED_LOCATION "${PROJECT_ROOT_PATH}/bin/x64/Debug/soci_core_4_1.dll")
set_property(TARGET soci_core PROPERTY IMPORTED_IMPLIB "${3RDPARTY_LIB_PATH}/release/soci_core_4_1.lib") 
```
发现虽然soci是动态库，但两种引入库的方式对vs生成的工程没有啥差异，使用对应动态库，windows平台下 cmake引入的话都可以静态库方式添加(`add_library`),linux下貌似也无差异(FA软件中common组件linux也是编译过的)

### 4.2 soci 库使用
```
target_link_libraries(${PROJECT} 
    soci_core 
    soci_sqlite3)
```


## 3. rttr
### 3.1 库编译
### 3.2 引用库的 cmake 配置
### 3.2 rttr 库使用