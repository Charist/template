#pragma once

#include <gtest/gtest.h>
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
};
