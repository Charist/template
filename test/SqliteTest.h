#pragma once

#include <gtest/gtest.h>
class sqlite3;
class SqliteTest : public testing::Test
{
public:
    // 在测试套件的第一个测试用例开始前
    static void SetUpTestSuite();
    // 在测试套件的最后一个测试用例执行完
    static void TearDownTestSuite();
protected:
    // 测试用例层面事件：运行每个测试用例之前执行。
    virtual void SetUp() override;
    // 测试用例层面事件：运行每个测试用例之后执行。
    virtual void TearDown() override;


    static void CheckResult(int result);
protected:
    static sqlite3* m_pDb;
};

