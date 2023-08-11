#pragma once

#include <gtest/gtest.h>
class sqlite3;
class SqliteTest : public testing::Test
{
public:
    // �ڲ����׼��ĵ�һ������������ʼǰ
    static void SetUpTestSuite();
    // �ڲ����׼������һ����������ִ����
    static void TearDownTestSuite();
protected:
    // �������������¼�������ÿ����������֮ǰִ�С�
    virtual void SetUp() override;
    // �������������¼�������ÿ����������֮��ִ�С�
    virtual void TearDown() override;


    static void CheckResult(int result);
protected:
    static sqlite3* m_pDb;
};

