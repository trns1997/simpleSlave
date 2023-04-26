#include "gtest/gtest.h"

#include "DataModel.h"

class DataItemTest: public testing::Test
{
    virtual void SetUp() {};
    virtual void TearDown() {};
};

TEST_F(DataItemTest, test_data)
{
    DataItemId id = DataItemId::TEST_DATA_ID;

    DataItem data_RO(id);
    ASSERT_EQ(0, data_RO.get());
    data_RO.reset();
    ASSERT_EQ(0, data_RO.get());

    Datagram& data = data_RO.getDatagram();

    DataItem data_RW(id, true);
    ASSERT_EQ(data.value, data_RW.get());
    ASSERT_EQ(data.value, data_RO.get());

    data_RW.set(data.max);
    ASSERT_EQ(data.max, data_RW.get());
    ASSERT_EQ(data.max, data_RO.get());
    data_RW.set(data.max + 1);
    ASSERT_EQ(data.max, data_RW.get());
    ASSERT_EQ(data.max, data_RO.get());

    data_RW.set(data.min);
    ASSERT_EQ(data.min, data_RW.get());
    ASSERT_EQ(data.min, data_RO.get());
    data_RW.set(data.min - 1);
    ASSERT_EQ(data.min, data_RW.get());
    ASSERT_EQ(data.min, data_RO.get());

    data_RW.reset();
    ASSERT_EQ(data.reset, data_RW.get());
    ASSERT_EQ(data.reset, data_RO.get());
}

