#include "SqliteTest.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

void SqliteTest::SetUpTestSuite()
{

}

void SqliteTest::TearDownTestSuite()
{

}

void SqliteTest::SetUp()
{   
    sqlite3* db = NULL;
    char* errmsg = NULL;

    const char* database_name = "./sqlite3-demo.db";
    //const char* database_name = ":memory:";
    const char* sql_drop_table = "drop table if exists student";
    const char* sql_create_table = "create table IF NOT EXISTS student(id int primary key,name varchar(128))";

    // create or open database
    int ret = sqlite3_open(database_name, &db);
    if (ret != SQLITE_OK) 
    {
        std::cout << "Cannot open database " << sqlite3_errmsg(db) << std::endl;
    }
    ret = sqlite3_exec(db, sql_create_table, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK) 
    {
        std::cout << "create table failure " << sqlite3_errmsg(db) << std::endl;
    }

}

void SqliteTest::TearDown()
{
    sqlite3* db = NULL;
    char* errmsg = NULL;

    const char* database_name = "./sqlite3-demo.db";
    //const char* database_name = ":memory:";
    const char* sql_drop_table = "drop table if exists student";

    // create or open database
    int ret = sqlite3_open(database_name, &db);
    if (ret != SQLITE_OK) 
    {
        std::cout << "Cannot open database "<<sqlite3_errmsg(db)<<std::endl;
    }
    ret = sqlite3_exec(db, sql_drop_table, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK) {
        std::cout << "drop table failure " << sqlite3_errmsg(db) << std::endl;
    }
}

