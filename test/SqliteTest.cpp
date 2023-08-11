#include "SqliteTest.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

sqlite3 *SqliteTest::m_pDb = nullptr;

void SqliteTest::SetUpTestSuite()
{
    std::cout << "SqliteTest::SetUpTestSuite" << std::endl;

    char *errmsg = NULL;

    const char *database_name = "./sqlite3-demo.db";
    const char *sql_drop_table = "drop table if exists student";
    const char *sql_create_table = "create table IF NOT EXISTS student(id int primary key,name varchar(128))";

    // create or open database
    int ret = sqlite3_open(database_name, &m_pDb);
    CheckResult(ret);

    ret = sqlite3_exec(m_pDb, sql_create_table, NULL, NULL, &errmsg);
    CheckResult(ret);
    sqlite3_free(errmsg);
}

void SqliteTest::TearDownTestSuite()
{
    std::cout << "SqliteTest::TearDownTestSuite" << std::endl;

    char *errmsg = NULL;
    // const char* database_name = ":memory:";
    const char *sql_drop_table = "drop table if exists student";

    int ret = sqlite3_exec(m_pDb, sql_drop_table, NULL, NULL, &errmsg);

    sqlite3_free(errmsg);
    sqlite3_close(m_pDb);
    CheckResult(ret);
}

void SqliteTest::CheckResult(int result)
{
    if (result != SQLITE_OK)
    {
        std::cout << "sqlite error: " << sqlite3_errmsg(m_pDb) << std::endl;
    }
}

void SqliteTest::SetUp()
{
    std::cout << "SqliteTest::SetUp" << std::endl;
}

void SqliteTest::TearDown()
{
    std::cout << "SqliteTest::TearDown" << std::endl;
}

TEST_F(SqliteTest, insert)
{
    char *errmsg = NULL;
    const char *sql_str1 = "INSERT INTO student(id, name) VALUES(1001, 'Ady Liu'),(1002, 'ivan'),(1003, '���»�');";
    int ret = sqlite3_exec(m_pDb, sql_str1, NULL, NULL, &errmsg);
    EXPECT_EQ(ret, 0);
    CheckResult(ret);

    sqlite3_free(errmsg);
}

TEST_F(SqliteTest, select)
{
    char *errmsg = NULL;
    char **dbresult = nullptr;
    int nrow = 0;
    int ncolumn = 0;
    const char *sql_str8 = "SELECT * FROM student;";
    int ret = sqlite3_get_table(m_pDb, sql_str8, &dbresult, &nrow, &ncolumn, &errmsg);
    EXPECT_EQ(ret, 0);

    if (ret == SQLITE_OK)
    {
        std::cout << "query " << nrow << "records" << std::endl;
        int index = ncolumn;
        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncolumn; j++)
            {
                char format_str[128] = {0};
                snprintf(format_str, sizeof(format_str) - 1, "(%d,%d): %s ", i, j, dbresult[index]);
                std::cout << format_str;
                index++;
            }
            std::cout << std::endl;
        }
    }
    sqlite3_free_table(dbresult);
}