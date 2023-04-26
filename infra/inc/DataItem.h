#ifndef INFRA_DATAITEM_HPP
#define INFRA_DATAITEM_HPP

#define MAX_DATA_ITEMS 100

#include <string>

extern "C"
{
#include "esc_coe.h"
}

struct Datagram
{
    int32_t value;
    int32_t reset;
    int32_t min;
    int32_t max;
    int32_t div;
    std::string name;
    _objd ethercat;
};

enum class DataItemId : int;
extern Datagram DataItems[];

class DataItem
{
public:
    DataItem(DataItemId id);
    DataItem(DataItemId id, bool writable);
    ~DataItem();

    int32_t get();
    void set(int32_t val);
    void reset();

    int32_t *getDataPtr()
    {
        return &data_.value;
    }

    std::string getName()
    {
        return data_.name;
    }

    static Datagram &getDatagram(DataItemId id) { return DataItem::s_integer[static_cast<uint32_t>(id)]; }

private:
    Datagram &data_;
    bool writable_{false};
    static const uint32_t length;

    static Datagram s_integer[MAX_DATA_ITEMS];

    Datagram &getDatagram();
    friend class DataItemTest_test_data_Test;
};

#endif
